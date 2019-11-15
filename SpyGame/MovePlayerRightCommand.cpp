#include "MovePlayerRightCommand.h"
#include "Player.h"

// Save the receiver, the player, in the constructor.
MovePlayerRightCommand::MovePlayerRightCommand(Player * pPlayer)
{
	m_pPlayer = pPlayer;
}

void MovePlayerRightCommand::Execute()
{
	m_pPlayer->MoveRight();
}
