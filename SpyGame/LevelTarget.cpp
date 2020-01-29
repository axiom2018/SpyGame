#include "LevelTarget.h"
#include "GameUpdatesMediator.h"
#include <iostream>

LevelTarget::LevelTarget(GameUpdatesMediator * pGameUpdatesMediator)
{
	// The position for the target is always opposite of the player, so it'll be 0,0.
	m_x = 0;
	m_y = 0;

	// Set mediator.
	m_pGameUpdatesMediator = pGameUpdatesMediator;

	// Register with mediator.
	m_pGameUpdatesMediator->Register(this);
}

bool LevelTarget::ConflictingCoordinates(const int & x, const int & y) const
{
	// If position matches return true, indicating other entity must choose a different position.
	if (m_x == x && m_y == y)
	{
		return true;
	}

	return false;
}

bool LevelTarget::Draw(const int & x, const int & y)
{
	// Check if coordinates match players position. If so, print it and return true, this was players position.
	if (x == m_x && y == m_y)
	{
		std::cout << k_symbol;
		return true;
	}

	return false;
}

char LevelTarget::GetLevelTarget() const
{
	return k_symbol;
}

bool LevelTarget::Update()
{
	// First get the player coordinates.
	std::pair<int, int> coords = m_pGameUpdatesMediator->ReceiveCoordinates();

	// Check if they match the level target coordinates, if so, return true.
	if (m_x == coords.first && m_y == coords.second)
	{
		return true;
	}

	return false;
}