#pragma once
#include "Command.h"

class MovePlayerRightCommand : public Command
{
private:
	class Player * m_pPlayer;
public:
	MovePlayerRightCommand(class Player * pPlayer);
	virtual void Execute() override;
};

