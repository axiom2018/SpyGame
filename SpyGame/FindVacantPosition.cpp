#include "FindVacantPosition.h"
#include "GameUpdatesMediator.h"
#include "Positions.h"

FindVacantPosition::FindVacantPosition(const int& gridWidth, const int& gridHeight, GameUpdatesMediator * pGameUpdatesMediator)
{
	// Initialize the width and height variables.
	m_gridWidth = gridWidth;
	m_gridHeight = gridHeight;

	// Set mediator.
	m_pGameUpdatesMediator = pGameUpdatesMediator;

	// Register with mediator.
	m_pGameUpdatesMediator->Register(this);

	// Allocate positions.
	m_pPositions = new Positions;
}

bool FindVacantPosition::IsInRange(const int & x, const int & y) const
{
	if (x >= m_gridWidth)
	{
		return true;
	}

	else if (y >= m_gridHeight)
	{
		return true;
	}

	return false;
}

void FindVacantPosition::ResetGridDimensions(const int & gridWidth, const int & gridHeight)
{
	// Reset the width and height variables.
	m_gridWidth = gridWidth;
	m_gridHeight = gridHeight;
}

// Get a random point on the current grid.
void FindVacantPosition::GetPositionOnGrid(int * pX, int * pY)
{
	// Ready the variables to an inital default value.
	std::pair<int, int> position;

	/* The outer do while is there because the first one will find an initial in BOUNDS position. Afterwards, we must make sure that position doesn't
	overlap a wall. */
	do {

		do {
			// Get random point on the grid.
			position.first = (rand() % (m_gridWidth + 1 - 0)) + 0;
			position.second = (rand() % (m_gridHeight + 1 - 0)) + 0;

		} while (IsInRange(position.first, position.second)); // Make sure the x and y are in bounds.

		// Also check if this position matches player position.
		std::pair<int, int> playerPos = m_pGameUpdatesMediator->ReceiveCoordinates(this);

		if (playerPos.first == position.first && playerPos.second == position.second)
		{
			// If the enemy does have the player pos, reassign it.
			continue;
		}

	} while (m_pGameUpdatesMediator->IsWallHere(position.second, position.first) || m_pGameUpdatesMediator->IsLevelTargetHere(position.second, position.first) ||
		m_pPositions->IsPositionOccupied(position.first, position.second));


	// When it's done we've successfully found a position, so apply it to the pointers.
	*pX = position.first;
	*pY = position.second;

	// Once the position is found, add it to the positions class.
	m_pPositions->AddPosition(position.first, position.second);
}

void FindVacantPosition::EmptyPositions() const
{
	m_pPositions->ClearPositions();
}

GameUpdatesMediator * FindVacantPosition::GetGameUpdatesMediator() const
{
	return m_pGameUpdatesMediator;
}

int FindVacantPosition::GetWidth() const
{
	return m_gridWidth;
}

int FindVacantPosition::GetHeight() const
{
	return m_gridHeight;
}

FindVacantPosition::~FindVacantPosition()
{
	delete m_pPositions;
	m_pPositions = nullptr;
}