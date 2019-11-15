#include "MovePlayerLeftCommand.h"
#include "Player.h"

// Save the receiver, the player, in the constructor.
MovePlayerLeftCommand::MovePlayerLeftCommand(Player * pPlayer)
{
	m_pPlayer = pPlayer;
}

void MovePlayerLeftCommand::Execute()
{
	m_pPlayer->MoveLeft();
}

