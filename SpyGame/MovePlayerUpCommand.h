#pragma once
#include "Command.h"

class MovePlayerUpCommand : public Command
{
private:
	class Player * m_pPlayer;
public:
	MovePlayerUpCommand(class Player * pPlayer);
	virtual void Execute() override;
};

