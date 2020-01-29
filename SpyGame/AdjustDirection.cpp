#include "AdjustDirection.h"
#include "Constants.h"
#include "GameUpdatesMediator.h"
#include <iostream>

AdjustDirection::AdjustDirection(class GameUpdatesMediator * pGameUpdatesMediator, int * pX, int *pY, char * pEnemyChar)
{
	// Save the mediator.
	m_pGameUpdatesMediator = pGameUpdatesMediator;

	// Register with it.
	m_pGameUpdatesMediator->Register(this);

	// Set enemy position.
	m_pX = pX;
	m_pY = pY;

	// Save the char.
	m_pEnemyChar = pEnemyChar;

	// Begin setting width and height.
	SetDimensionsAndEdgeCheck();
}

void AdjustDirection::EdgeCheck()
{
	// Check west. Positions too close west are 0, and 1.
	if (*m_pX <= 2)
	{
		// If too close west, switch to east.
		*m_pEnemyChar = k_eastSymbol;
	}

	// Check east. Example, if grid is sized 31 in x, it's 2 positions to be "too close" are 29, and 30.
	else if (*m_pX >= (m_gridWidth - 3))
	{
		// If too close east, switch to west.
		*m_pEnemyChar = k_westSymbol;
	}

	// Check north. Positions too close north are 0, and 1.
	else if (*m_pY <= 2)
	{
		// If too close north, switch to south.
		*m_pEnemyChar = k_southSymbol;
	}

	// Check south. Example, if grid is sized 10 in y, it's 2 positions to be "too close" are 8, and 9.
	else if (*m_pY >= (m_gridHeight - 3))
	{
		// If too close south, switch to north.
		*m_pEnemyChar = k_northSymbol;
	}
}

void AdjustDirection::SetDimensionsAndEdgeCheck()
{
	// Set the width and height through mediator.
	std::pair<int, int> size = m_pGameUpdatesMediator->GetWidthAndHeightOfGrid();
	m_gridWidth = size.first;
	m_gridHeight = size.second;

	// Begin edge check.
	EdgeCheck();
}