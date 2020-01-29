#include "TwoPoint.h"
#include "DirectionalSystem.h"
#include "LineOfSight.h"
#include "Point.h"
#include "AStar.h"
#include "World.h"
#include "FindVacantPosition.h"
#include "AStar.h"
#include "Node.h"
#include <iostream>
#include <list>

TwoPoint::TwoPoint(FindVacantPosition * pFindVacantPosition, class GameUpdatesMediator * pGameUpdatesMediator)
{
	// Save the find vacant position pointer.
	m_pFindVacantPosition = pFindVacantPosition;

	// Get a start point.
	m_pFindVacantPosition->GetPositionOnGrid(&m_x, &m_y);

	// Get end point. 
	m_pFindVacantPosition->GetPositionOnGrid(&m_endPointX, &m_endPointY);

	// Also needs the directional system.
	m_pDirectionalSystem = new DirectionalSystem(&m_x, &m_y);

	// Allocate for line of sight so player can get caught.
	m_pLineOfSight = new LineOfSight(m_pDirectionalSystem->GetChar(), &m_x, &m_y, k_sightDistance, pGameUpdatesMediator);

	// Allocate for A star.
	m_pAStar = new AStar(m_endPointX, m_endPointY, &m_x, &m_y, m_pFindVacantPosition->GetGameUpdatesMediator());
}

bool TwoPoint::Draw(const int & x, const int & y)
{
	if (m_x == x && m_y == y)
	{
		std::cout << m_pDirectionalSystem->Update();

		return true;
	}

	return false;
}

bool TwoPoint::Update(const int & playerX, const int & playerY)
{
	// Must also update the line of sight.
	if (m_pLineOfSight->Update(playerX, playerY))
	{
		// Return true! We found the player!
		return true;
	}
	
	// If we didn't find the player let's just move this enemy.
	m_pAStar->Update();

	return false;
}

void TwoPoint::ResetEnemyData()
{
	// Get a start point.
	m_pFindVacantPosition->GetPositionOnGrid(&m_x, &m_y);

	// Get end point.
	m_pFindVacantPosition->GetPositionOnGrid(&m_endPointX, &m_endPointY);

	// Update line of sight.
	m_pLineOfSight->UpdateDimensions();

	// Reset to the start of the path in A star.
	m_pAStar->ResetPath(m_endPointX, m_endPointY);
}

void TwoPoint::BackToStartingPosition()
{
	m_pAStar->SetBackToStartingPosition();
}

TwoPoint::~TwoPoint()
{
	delete m_pAStar;
	m_pAStar = nullptr;

	delete m_pLineOfSight;
	m_pLineOfSight = nullptr;

	delete m_pDirectionalSystem;
	m_pDirectionalSystem = nullptr;
}
