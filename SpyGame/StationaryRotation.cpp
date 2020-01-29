#include "StationaryRotation.h"
#include "DirectionalSystem.h"
#include "LineOfSight.h"
#include "FindVacantPosition.h"
#include "World.h"
#include <iostream>

StationaryRotation::StationaryRotation(FindVacantPosition * pFindVacantPosition, class GameUpdatesMediator * pGameUpdatesMediator)
{
	// Save the find vacant position pointer.
	m_pFindVacantPosition = pFindVacantPosition;

	// Get a point.
	m_pFindVacantPosition->GetPositionOnGrid(&m_x, &m_y);

	// Also needs the directional system.
	m_pDirectionalSystem = new DirectionalSystem(&m_x, &m_y);

	// Allocate for line of sight so player can get caught.
	m_pLineOfSight = new LineOfSight(m_pDirectionalSystem->GetChar(), &m_x, &m_y, k_sightDistance, pGameUpdatesMediator);
}

bool StationaryRotation::Draw(const int & x, const int & y)
{
	if (m_x == x && m_y == y)
	{
		std::cout << m_pDirectionalSystem->Update();

		return true;
	}

	return false;
}

void StationaryRotation::ResetEnemyData()
{
	// Get a point.
	m_pFindVacantPosition->GetPositionOnGrid(&m_x, &m_y);

	// Allocate for line of sight so player can get caught.
	m_pLineOfSight->UpdateDimensions();
}

bool StationaryRotation::Update(const int& playerX, const int& playerY)
{
	// Must also update the line of sight.
	if (m_pLineOfSight->Update(playerX, playerY))
	{
		// Return true! We found the player!
		return true;
	}

	// Changes direction.
	m_pDirectionalSystem->UpdateDirection();

	return false;
}

StationaryRotation::~StationaryRotation()
{
	delete m_pLineOfSight;
	m_pLineOfSight = nullptr;

	delete m_pDirectionalSystem;
	m_pDirectionalSystem = nullptr;
}
