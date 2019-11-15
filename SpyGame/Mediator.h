#pragma once
#include <utility>
#include "Node.h"

/* Reasoning for this class:

This communication is between the player and the enemy manager, because the line of sight system needs the players coordinates in order to work. 
This mediator ensures the enemies get that data.


																				Class member variables:

1)


																				Class functions:

1) Reasoning for Register:

Allow colleague to register for communication system.


2) Reasoning for Unregister: 

Allow colleague to unregister for communication system.


3) Reasoning for ReceiverCoordinates:

The enemies must know where the player is while their line of sight checks for them, this function gets the player coordinates to the enemies.


4) Reasoning for PlaceWall:

Begin painting the 2d grid with the walls to block player and enemies.


5) Reasoning for IsWallHere:

Allow colleagues to check if there is a wall there so they can avoid it.


6) Reasoning for IsLevelTargetHere:

Neither the player or the enemies can share the targets position. 


7) Reasoning for ResetWallCoordinate:

Must reset when the block manager thinks it can place a wall somewhere but it ends up being blocked.


																				Class functions (private):

1)


*/

class Mediator
{
public:
	virtual void Register(class Colleague * pColleague) = 0;
	virtual void Unregister(class Colleague * pColleague) = 0;
	virtual std::pair<int, int> ReceiveCoordinates(class Colleague * pColleague) = 0;
	virtual bool PlaceWall(const int& x, const int& y) const = 0;
	virtual bool IsWallHere(const int& x, const int& y) const = 0;
	virtual bool IsLevelTargetHere(const int& x, const int& y) const = 0;
	virtual bool ResetWallCoordinate(const int& x, const int& y) const = 0;
	virtual Node * GetGrid() const = 0;
};