#include "ControlsInvoker.h"
#include "MovePlayerUpCommand.h"
#include "MovePlayerDownCommand.h"
#include "MovePlayerLeftCommand.h"
#include "MovePlayerRightCommand.h"
#include <conio.h>

ControlsInvoker::ControlsInvoker(Player * pPlayer)
{
	// Initialize all the concrete commands in the constructor for ease of setting up.
	m_pPlayerUp = new MovePlayerUpCommand(pPlayer);
	m_pPlayerDown = new MovePlayerDownCommand(pPlayer);
	m_pPlayerLeft = new MovePlayerLeftCommand(pPlayer);
	m_pPlayerRight = new MovePlayerRightCommand(pPlayer);
}

void ControlsInvoker::SetUpCommand(Command * pUpCommand)
{
	// Check to see if there's already a valid pointer, if so, delete it before setting the new one provided in the argument.
	if (m_pPlayerUp)
	{
		delete m_pPlayerUp;
		m_pPlayerUp = nullptr;
	}

	m_pPlayerUp = pUpCommand;
}

void ControlsInvoker::SetDownCommand(Command * pDownCommand)
{
	// Check to see if there's already a valid pointer, if so, delete it before setting the new one provided in the argument.
	if (m_pPlayerDown)
	{
		delete m_pPlayerDown;
		m_pPlayerDown = nullptr;
	}

	m_pPlayerDown = pDownCommand;
}

void ControlsInvoker::SetLeftCommand(Command * pLeftCommand)
{
	// Check to see if there's already a valid pointer, if so, delete it before setting the new one provided in the argument.
	if (m_pPlayerLeft)
	{
		delete m_pPlayerLeft;
		m_pPlayerLeft = nullptr;
	}

	m_pPlayerLeft = pLeftCommand;
}

void ControlsInvoker::SetRightCommand(Command * pRightCommand)
{
	// Check to see if there's already a valid pointer, if so, delete it before setting the new one provided in the argument.
	if (m_pPlayerRight)
	{
		delete m_pPlayerRight;
		m_pPlayerRight = nullptr;
	}

	m_pPlayerRight = pRightCommand;
}

void ControlsInvoker::ExecuteUp() const
{
	m_pPlayerUp->Execute();
}

void ControlsInvoker::ExecuteDown() const
{
	m_pPlayerDown->Execute();
}

void ControlsInvoker::ExecuteLeft() const
{
	m_pPlayerLeft->Execute();
}

void ControlsInvoker::ExecuteRight() const
{
	m_pPlayerRight->Execute();
}

bool ControlsInvoker::GetInput() const
{
	while (true)
	{
		// Get the input from player.
		char input = _getch();

		// Process input.
		switch (input)
		{
		case k_up:
			m_pPlayerUp->Execute();
			return false;
		case k_down:
			m_pPlayerDown->Execute();
			return false;
		case k_left:
			m_pPlayerLeft->Execute();
			return false;
		case k_right:
			m_pPlayerRight->Execute();
			return false;
		case k_quit:
			return true;
		default:
			break;
		}
	}

	return false;
}

ControlsInvoker::~ControlsInvoker()
{
	delete m_pPlayerUp;
	m_pPlayerUp = nullptr;

	delete m_pPlayerDown;
	m_pPlayerDown = nullptr;

	delete m_pPlayerLeft;
	m_pPlayerLeft = nullptr;

	delete m_pPlayerRight;
	m_pPlayerRight = nullptr;
}
