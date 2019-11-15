#include "World.h"
#include "Constants.h"
#include "Player.h"
#include "BlockManager.h"
#include "EnemyManager.h"
#include "GameUpdatesMediator.h"
#include "LevelTarget.h"
#include "FindVacantPosition.h"
#include "MaxLevels.h"
#include "Detected.h"
#include <Windows.h>
#include <conio.h>
#include <iostream>

// Initialize the static variable or singleton to nullptr.
World * World::m_pWorld = nullptr;

World::World()
{
	// Calculate the grids size with randomness.
	GenerateRandomSizedGrid();

	// Actually build the grid.
	BuildGrid();

	// Allocate mediator.
	m_pGameUpdatesMediator = new GameUpdatesMediator;

	// Register this.
	m_pGameUpdatesMediator->Register(this);

	// Allocate level target.
	m_pLevelTarget = new LevelTarget(m_pGameUpdatesMediator);

	// Allocate player.
	m_pPlayer = new Player(m_gridX, m_gridY, m_pGameUpdatesMediator);

	// Allocate find vacant position.
	m_pFindVacantPosition = new FindVacantPosition(m_gridX, m_gridY, m_pGameUpdatesMediator);

	// Allocate max levels and pass in however many levels desired before the game ends.
	m_pMaxLevels = new MaxLevels(3);

	// Allocate detected pointer.
	m_pDetected = new Detected;
}

void World::GenerateRandomSizedGrid()
{
	// Calculate a random x.
	m_gridX = (rand() % (k_maxGridX + 1 - k_minGridX)) + k_minGridX;

	// Calculate a random y.
	m_gridY = (rand() % (k_maxGridY + 1 - k_minGridY)) + k_minGridY;
}

void World::BuildGrid()
{
	// Initialize the memory.
	m_pGrid = new Node[m_gridY * m_gridX];

	// Initialize every part of it.
	for (int x = 0; x < m_gridY; ++x)
	{
		for (int y = 0; y < m_gridX; ++y)
		{
			m_pGrid[y * m_gridY + x].m_displayCharacter = '.';
			m_pGrid[y * m_gridY + x].m_colorValue = 7;
			m_pGrid[y * m_gridY + x].m_x = x;
			m_pGrid[y * m_gridY + x].m_y = y;
			m_pGrid[y * m_gridY + x].m_obstacle = false;
			m_pGrid[y * m_gridY + x].m_pParent = nullptr;
			m_pGrid[y * m_gridY + x].m_visited = false;
		}
	}

	// Connect the graph nodes together.
	for (int x = 0; x < m_gridY; ++x)
	{
		for (int y = 0; y < m_gridX; ++y)
		{
			if (y > 0)
			{
				m_pGrid[y * m_gridY + x].m_neighbors.push_back(&m_pGrid[(y - 1) * m_gridY + (x + 0)]);
			}

			if (y < m_gridX - 1)
			{
				m_pGrid[y * m_gridY + x].m_neighbors.push_back(&m_pGrid[(y + 1) * m_gridY + (x + 0)]);
			}

			if (x > 0)
			{
				m_pGrid[y * m_gridY + x].m_neighbors.push_back(&m_pGrid[(y + 0) * m_gridY + (x - 1)]);
			}

			if (x < m_gridY - 1)
			{
				m_pGrid[y * m_gridY + x].m_neighbors.push_back(&m_pGrid[(y + 0) * m_gridY + (x + 1)]);
			}
		}
	}
}

void World::GenerateNewLevel()
{
	// Send enemies to the object pool.
	m_pEnemyManager->SendEnemiesToPool();

	// Delete the entire grid now. (This WAS in a function.)
	delete[] m_pGrid;

	// Make a new one by first getting a new random size.
	GenerateRandomSizedGrid();

	// Then build it.
	BuildGrid();

	// Reset the dimensions in find vacant position.
	m_pFindVacantPosition->ResetGridDimensions(m_gridX, m_gridY);

	// Set up some new blocks.
	m_pBlockManager->CreateNewBlocks(m_gridX, m_gridY);

	// Reset the position of the player.
	m_pPlayer->ResetPosition(m_gridX, m_gridY);

	// Clear the enemy positions.
	m_pEnemyManager->ClearEnemyPositions();

	// Increment enemies.
	m_pEnemyManager->IncreaseTotalEnemies();

	// Re use enemies.
	m_pEnemyManager->GetEnemiesFromPool(m_gridX, m_gridY);

	// Wipe screen.
	system("cls");
}

void World::RestartLevel()
{
	// Reset the position of the player.
	m_pPlayer->ResetPosition(m_gridX, m_gridY);

	// Reset the enemies as well.
	m_pEnemyManager->ResetEnemyPositions();

	// Wipe screen.
	system("cls");
}

void World::ClearScreenAndShowCurrentGrid() const
{
	system("cls");

	int pX = -1;
	int pY = -1;

	for (int x = 0; x < m_gridY; ++x)
	{
		for (int y = 0; y < m_gridX; ++y)
		{
			// Change color to specific color in the nodes.
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), m_pGrid[y * m_gridY + x].m_colorValue);

			// Check if player positon. If it was, continue and don't worry about drawing anything else.
			if (m_pPlayer->Draw(y, x))
			{
				pX = x;
				pY = y;
				continue;
			}

			// Check for the level target
			else if (m_pLevelTarget->Draw(y, x))
			{
				continue;
			}

			// Draw the grid.
			std::cout << m_pGrid[y * m_gridY + x].m_displayCharacter;

			// Also set back to normal here.
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}

		std::cout << "\n";
	}

	std::cout << "\nCurrent level: " << m_pMaxLevels->GetCurrentLevel() << ". Total levels: " << m_pMaxLevels->GetFinalLevel() << "\n";
	std::cout << "Detection limit: " << m_pDetected->GetDetectionLimit() << ". Current times detected: " << m_pDetected->GetCurrentTimesDetected() << "\n";
	Instructions();
}

void World::Instructions() const
{
	std::cout << "\n---INSTRUCTIONS: Use w/a/s/d keys to move around to the goal: " << m_pLevelTarget->GetLevelTarget() << "\n";
	std::cout << "Press q to quit.\n";
	std::cout << "Avoid geting caught by staying OUT of the enemies line of sight!---\n";
}

World * World::GetInstance()
{
	// If m_pWorld is nullptr, which it will be thanks to the initialization at top of this file, initialize with new World.
	if (!m_pWorld)
	{
		m_pWorld = new World;
	}

	// Then return it to requesting client.
	return m_pWorld;
}

void World::PrintGrid() const
{
	int pX = -1;
	int pY = -1;

	for (int x = 0; x < m_gridY; ++x)
	{
		for (int y = 0; y < m_gridX; ++y)
		{
			// Change color to specific color in the nodes.
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), m_pGrid[y * m_gridY + x].m_colorValue);

			// Check if player positon. If it was, continue and don't worry about drawing anything else.
			if (m_pPlayer->Draw(y, x))
			{
				pX = x;
				pY = y;
				continue;
			}

			// Check for enemies.
			else if (m_pEnemyManager->Draw(y, x))
			{
				continue;
			}

			// Check for the level target
			else if (m_pLevelTarget->Draw(y, x))
			{
				continue;
			}

			// Draw the grid.
			std::cout << m_pGrid[y * m_gridY + x].m_displayCharacter;

			// Also set back to normal here.
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}

		std::cout << "\n";
	}

	std::cout << "\nCurrent level: " << m_pMaxLevels->GetCurrentLevel() << ". Total levels: " << m_pMaxLevels->GetFinalLevel() << "\n";
	std::cout << "Detection limit: " << m_pDetected->GetDetectionLimit() << ". Current times detected: " << m_pDetected->GetCurrentTimesDetected() << "\n";
	Instructions();
}

void World::Update()
{
	// Allocate block manager.
	m_pBlockManager = new BlockManager(m_gridX, m_gridY, m_pGameUpdatesMediator);

	// Allocate enemy manager.
	m_pEnemyManager = new EnemyManager(m_gridX, m_gridY, m_pMaxLevels->GetFinalLevel(), m_pGameUpdatesMediator, m_pFindVacantPosition);

	// Loop.
	while (true)
	{
		// Print the screen first.
		PrintGrid();

		// Check if player new position is equal to the level target.
		if (m_pLevelTarget->Update())
		{
			// Check if the last level was just beaten.
			if (m_pMaxLevels->IncreaseLevel())
			{
				// Display winning message.
				std::cout << "\n\nYou have stayed hidden long enough to escape! Congratulations!\n";

				// Get input before the game ends.
				_getch();

				// If so, break. 
				break;
			}

			// We must do certain tasks to advance to the new level, the following function handles those.
			GenerateNewLevel();

			// Then continue the game.
			continue;
		}

		// Update enemies here.
		else if (m_pEnemyManager->Update())
		{
			// Increment times caught with detected.
			m_pDetected->IncrementTimesDetected();

			// Been caught too many times? End game!
			if (m_pDetected->IsGameOver())
			{
				// Display losing message.
				std::cout << "Caught yet again! Game over!\n";

				// Get input before the game ends.
				_getch();

				// If so, break.
				break;
			}

			// If not, restart the level.
			RestartLevel();

			continue;
		}

		// Get player input. If function is true, break from loop.
		if (m_pPlayer->GetInput())
		{
			break;
		}

		system("cls");
	}
}

bool World::PlaceWallAtPosition(const int & x, const int & y) const
{
	m_pGrid[y * m_gridY + x].m_displayCharacter = k_obstacle;
	m_pGrid[y * m_gridY + x].m_obstacle = true;

	// ClearScreenAndShowCurrentGrid();

	return true;
}

bool World::IsWallAtPosition(const int & x, const int & y) const
{
	if (m_pGrid[y * m_gridY + x].m_displayCharacter == k_obstacle)
	{
		return true;
	}

	return false;
}

bool World::IsLevelTargetAtPosition(const int & x, const int & y) const
{
	if (m_pLevelTarget->ConflictingCoordinates(x, y))
	{
		return true;
	}

	return false;
}

bool World::ResetWallAtPosition(const int & x, const int & y) const
{
	m_pGrid[y * m_gridY + x].m_displayCharacter = '.';
	// ClearScreenAndShowCurrentGrid();

	return true;
}

Node * World::Get2DGrid() const
{
	return m_pGrid;
}

void World::Delete()
{
	delete[] m_pGrid;

	delete m_pLevelTarget;
	m_pLevelTarget = nullptr;

	delete m_pFindVacantPosition;
	m_pFindVacantPosition = nullptr;

	delete m_pMaxLevels;
	m_pMaxLevels = nullptr;

	delete m_pDetected;
	m_pDetected = nullptr;

	delete m_pGameUpdatesMediator;
	m_pGameUpdatesMediator = nullptr;

	delete m_pEnemyManager;
	m_pEnemyManager = nullptr;

	delete m_pBlockManager;
	m_pBlockManager = nullptr;

	delete m_pPlayer;
	m_pPlayer = nullptr;

	delete m_pWorld;
	m_pWorld = nullptr;
}
