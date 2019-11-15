#include "MovePlayerDownCommand.h"
#include "Player.h"

// Save the receiver, the player, in the constructor.
MovePlayerDownCommand::MovePlayerDownCommand(Player * pPlayer)
{
	m_pPlayer = pPlayer;
}

void MovePlayerDownCommand::Execute()
{
	m_pPlayer->MoveDown();
}
