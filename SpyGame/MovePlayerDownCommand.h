#pragma once
#include "Command.h"

class MovePlayerDownCommand : public Command
{
private:
	class Player * m_pPlayer;
public:
	MovePlayerDownCommand(class Player * pPlayer);
	virtual void Execute() override;
};

