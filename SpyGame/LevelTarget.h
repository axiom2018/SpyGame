#pragma once
#include "Colleague.h"

/* Reasoning for this class:

Each level needs a goal for the player to get to in order to advance to the next level.


																				Class member variables:

1) Reasoning for k_symbol:

The symbol the player will see so they know what to go to.


2) Reasoning for m_x & m_y:

The position of the symbol.



																				Class functions:

1) Reasoning for constructor:

Initialize variables and register with the mediator.


2) Reasoning for ConflictingCoordinates:

Other entities cannot share a position or draw over eachother, this function helps that.


3) Reasoning for Draw:

Draw the level target.


4) Reasoning for GetLevelTarget:

Be able to display it in World.cpp.


5) Reasoning for Update:

Check if player has made it to the target.


																				Class functions (private):

1)


*/

class LevelTarget : public Colleague
{
private:
	static const char k_symbol = '@';
	int m_x;
	int m_y;
public:
	LevelTarget(class GameUpdatesMediator * pGameUpdatesMediator);
	bool ConflictingCoordinates(const int& x, const int& y) const;
	bool Draw(const int& x, const int& y);
	char GetLevelTarget() const;
	bool Update();
};

