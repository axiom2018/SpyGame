#include "Player.h"
#include "ControlsInvoker.h"
#include "Constants.h"
#include "GameUpdatesMediator.h"
#include "World.h"
#include <iostream>

// Initialize the player position at the beginning. As well as the maximum grid width and height to insure we get the proper boundaries for movement.
Player::Player(const int& gridWidth, const int& gridHeight, GameUpdatesMediator * pGameUpdatesMediator) :
	m_x(gridWidth - 1),
	m_y(gridHeight - 1),
	m_gridWidth(gridWidth),
	m_gridHeight(gridHeight)
{
	// Initialize the controls system.
	m_pControlsInvoker = new ControlsInvoker(this);

	// Set mediator.
	m_pGameUpdatesMediator = pGameUpdatesMediator;

	// Register with mediator.
	m_pGameUpdatesMediator->Register(this);
}

void Player::MoveUp()
{
	// Get the next spot above us.
	int nextY = m_y - 1;

	if(nextY < 0 || m_pGameUpdatesMediator->IsWallHere(nextY, m_x))
	{
		return;
	}

	// Set the position if above hasn't forced an early return.
	m_y -= 1;
}

void Player::MoveDown()
{
	if ((m_y + 1) == m_gridHeight || m_pGameUpdatesMediator->IsWallHere(m_y + 1, m_x))
	{
		return;
	}

	// Set the position if above hasn't forced an early return.
	m_y += 1;
}

void Player::MoveLeft()
{
	// Get the next spot to the left.
	int nextX = m_x - 1;

	if (nextX < 0 || m_pGameUpdatesMediator->IsWallHere(m_y, nextX))
	{
		return;
	}

	// Set the position if above hasn't forced an early return.
	m_x -= 1;
}

void Player::MoveRight()
{
	if ((m_x + 1) == m_gridWidth || m_pGameUpdatesMediator->IsWallHere(m_y, m_x + 1))
	{
		return;
	}

	// Set the position if above hasn't forced an early return.
	m_x += 1;
}

bool Player::GetInput() const
{
	// If true, player has requested to quit game.
	if (m_pControlsInvoker->GetInput())
	{
		return true;
	}

	return false;
}

bool Player::Draw(const int & x, const int & y)
{
	// Check if coordinates match players position. If so, print it and return true, this was players position.
	if (x == m_x && y == m_y)
	{
		std::cout << k_char;
		return true;
	}

	return false;
}

void Player::ResetPosition(const int& gridWidth, const int& gridHeight)
{
	// Save the new width and height.
	m_gridWidth = gridWidth;
	m_gridHeight = gridHeight;

	// Get new x and y.
	m_x = m_gridWidth - 1;
	m_y = m_gridHeight - 1;
}

std::pair<int, int> Player::ReturnRequestedCoordinates()
{
	return std::make_pair(m_x, m_y);
}

Player::~Player()
{
	delete m_pControlsInvoker;
	m_pControlsInvoker = nullptr;
}
