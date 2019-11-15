#pragma once
#include "Command.h"

class MovePlayerLeftCommand : public Command
{
private:
	class Player * m_pPlayer;
public:
	MovePlayerLeftCommand(class Player * pPlayer);
	virtual void Execute() override;
};

