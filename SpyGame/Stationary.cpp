#include "Stationary.h"
#include "DirectionalSystem.h"
#include "LineOfSight.h"
#include "FindVacantPosition.h"
#include "AdjustDirection.h"
#include "Node.h"
#include <iostream>

Stationary::Stationary(FindVacantPosition * pFindVacantPosition, class GameUpdatesMediator * pGameUpdatesMediator)
{
	// Save the find vacant position pointer.
	m_pFindVacantPosition = pFindVacantPosition;

	// Get a point.
	m_pFindVacantPosition->GetPositionOnGrid(&m_x, &m_y);

	// Also needs the directional system.
	m_pDirectionalSystem = new DirectionalSystem(&m_x, &m_y);

	// Allocate for adjusting direction.
	m_pAdjustDirection = new AdjustDirection(pGameUpdatesMediator, &m_x, &m_y, m_pDirectionalSystem->GetChar());

	// Allocate for line of sight so player can get caught.
	m_pLineOfSight = new LineOfSight(m_pDirectionalSystem->GetChar(), &m_x, &m_y, k_sightDistance, pGameUpdatesMediator);
}

bool Stationary::Draw(const int & x, const int & y)
{
	if (m_x == x && m_y == y)
	{
		std::cout << m_pDirectionalSystem->Update();

		return true;
	}

	return false;
}

void Stationary::ResetEnemyData()
{
	// Get a point.
	m_pFindVacantPosition->GetPositionOnGrid(&m_x, &m_y);

	// Update adjustment direction.
	m_pAdjustDirection->SetDimensionsAndEdgeCheck();

	// Update line of sight so player can get caught.
	m_pLineOfSight->UpdateDimensions();

	// Update the directional system.
	m_pDirectionalSystem->UpdateCurrentXAndY();
}

bool Stationary::Update(const int& playerX, const int& playerY)
{
	// Must also update the line of sight.
	if (m_pLineOfSight->Update(playerX, playerY))
	{
		// Return true! We found the player!
		return true;
	}

	return false;
}

Stationary::~Stationary()
{
	delete m_pAdjustDirection;
	m_pAdjustDirection = nullptr;

	delete m_pLineOfSight;
	m_pLineOfSight = nullptr;

	delete m_pDirectionalSystem;
	m_pDirectionalSystem = nullptr;
}
