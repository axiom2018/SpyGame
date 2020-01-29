#include "LineOfSight.h"
#include "Constants.h"
#include "GameUpdatesMediator.h"
#include <iostream>
#include <conio.h>

LineOfSight::LineOfSight(char * pEnemyChar, int * pEnemyX, int * pEnemyY, const int& sightDistance, GameUpdatesMediator * pGameUpdatesMediator)
{
	// Save the char to know it's direction later.
	m_pEnemyChar = pEnemyChar;

	// Set mediator.
	m_pGameUpdatesMediator = pGameUpdatesMediator;

	// Register with mediator.
	m_pGameUpdatesMediator->Register(this);

	// Get the width and height of the grid we're working with.
	std::pair<int, int> size = m_pGameUpdatesMediator->GetWidthAndHeightOfGrid();
	m_worldWidth = size.first;
	m_worldHeight = size.second;

	// Save the enemy position.
	m_pEnemyX = pEnemyX;
	m_pEnemyY = pEnemyY;

	// Set the sight distance.
	m_sightDistance = sightDistance;

	// Set the counter to the sight distance.
	m_travelCounter = m_sightDistance;
}

void LineOfSight::UpdateDirection()
{
	// Use a simple switch and based on the enemy character, that's the current direction we're facing.
	switch (*m_pEnemyChar)
	{
	case k_northSymbol:
		// Assign the new symbol.
		m_currentChar = k_northSymbol;

		// Also, set an x and y because we'll begin checking the north direction soon.
		m_travelX = *m_pEnemyX;
		m_travelY = *m_pEnemyY - 1;
		break;
	case k_southSymbol:
		m_currentChar = k_southSymbol; 
		m_travelX = *m_pEnemyX;
		m_travelY = *m_pEnemyY + 1;
		break;
	case k_westSymbol:
		m_currentChar = k_westSymbol; 
		m_travelX = *m_pEnemyX - 1;
		m_travelY = *m_pEnemyY;
		break;
	case k_eastSymbol:
		m_currentChar = k_eastSymbol; 
		m_travelX = *m_pEnemyX + 1;
		m_travelY = *m_pEnemyY;
		break;
	default:
		break;
	}
}

bool LineOfSight::IsInBounds()
{
	// Check top side.
	if (m_travelX < 0)
	{
		return true;
	}

	// Check bottom side.
	else if (m_travelX >= m_worldWidth)
	{
		return true;
	}

	// Check left side.
	else if (m_travelY < 0)
	{
		return true;
	}

	// Check right side.
	else if (m_travelY >= m_worldHeight)
	{
		return true;
	}

	return false;
}

void LineOfSight::DecrementTravel()
{
	// Use a simple switch and based on the enemy character, that's the current direction we're facing.
	switch (m_currentChar)
	{
	case k_northSymbol:
		--m_travelY;
		break;
	case k_southSymbol:
		++m_travelY;
		break;
	case k_westSymbol:
		--m_travelX;
		break;
	case k_eastSymbol:
		++m_travelX;
		break;
	default:
		break;
	}
}

bool LineOfSight::CheckForWall() const
{
	// Check for a wall with the travel x and travel y coordinate, if there is one, return true, enemy can't see through a wall of course.
	if (m_pGameUpdatesMediator->IsWallHere(m_travelY, m_travelX))
	{
		return true;
	}

	return false;
}

bool LineOfSight::Update(const int& playerX, const int& playerY)
{
	// Now we begin the real meat of the algorithm. First update the direction and be able to get the coordinates we need to start at.
	UpdateDirection();

	// Keep going until we're out of bounds, reached the end, or hit a wall.
	while (!IsInBounds() && m_travelCounter != 0)
	{
		// Check for a wall, if hit, don't continue, we can't see through a wall, just exit.
		if (CheckForWall())
		{
			// Reset the travel counter to sight distance.
			m_travelCounter = m_sightDistance;

			return false;
		}

		// Check to see if the player is here.
		else if (playerX == m_travelX && playerY == m_travelY)
		{
			// Simple message to display after player is caught.
			std::cout << "You've been caught!\n";

			// Reset the sight counter.
			m_travelCounter = m_sightDistance;

			return true;
		}

		// Check to see if player was dumb enough to think standing ON the enemy would be fine.
		else if (playerX == *m_pEnemyX && playerY == *m_pEnemyY)
		{
			// Simple message to display after player is caught.
			std::cout << "Running directly into the enemy was not a good idea! You've been caught mate!\n";

			// Reset the sight counter.
			m_travelCounter = m_sightDistance;

			_getch();

			return true;
		}

		// Must decrement the x or y. Ex: If we're traveling SOUTH, leave the x alone, must decide based on m_currentChar.
		DecrementTravel();

		// Decrement travel counter.
		--m_travelCounter;
	}

	// Reset the travel counter to sight distance.
	m_travelCounter = m_sightDistance;

	return false;
}

void LineOfSight::UpdateDimensions()
{
	std::pair<int, int> size = m_pGameUpdatesMediator->GetWidthAndHeightOfGrid();
	m_worldWidth = size.first;
	m_worldHeight = size.second;
}
