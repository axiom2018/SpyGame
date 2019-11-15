#include "MovePlayerUpCommand.h"
#include "Player.h"

// Save the receiver, the player, in the constructor.
MovePlayerUpCommand::MovePlayerUpCommand(Player * pPlayer)
{
	m_pPlayer = pPlayer;
}

void MovePlayerUpCommand::Execute()
{
	m_pPlayer->MoveUp();
}
