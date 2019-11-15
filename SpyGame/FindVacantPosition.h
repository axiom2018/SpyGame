#pragma once
#include "Colleague.h"
#include <iostream>
#include <vector>

/* Reasoning for this class:

The old implementation had some redudant copied code in TwoPoint.cpp and Enemy.cpp. Enemy.cpp needed to find a single point to place an enemy. And TwoPoint.cpp 
needed to find ANOTHER point to go to that was clear. Also, The enemy.cpp and TwoPoint.cpp were directly referencing the world.cpp class instead of properly 
using the mediator. With this new class, we solve two issues. 2 birds, 1 stone, 1 happy programmer.

																				Class member variables:

1) Reasoning for m_gridWidth & m_gridHeight:

Make sure we do this algorithm properly by getting the width and height saved.


2) Reasoning for m_occupiedPositions:

See if the position desired is occupied and if so, find another.


																				Class functions:

1) Reasoning for constructor:

Initialize the necessary variables to get the point.


2) Reasoning for ResetGridDimensions:

When the level changes, we'll have a new grid width and height of course. We'll need to get some more enemies and re-use old ones, and assign
them proper positions. This function helps to apply new width and height so that can take place.


3) Reasoning for GetPositionOnGrid:

Find random point on the current grid.


4) Rasoning for EmptyPositions:

Clear the positions for next level.


5) Reasoning for GetGameUpdatesMediator:

Some entities, specifically the TwoPoint enemy, will need to contact the world, so this function provides it and other potential entities the mediator.


6) Reasoning for GetWidth & GetHeight:

Return to width and height for clients that are using the class.


) Reasoning for destructor:

Wipe memory.


																				Class functions (private):

1) Reasoning for IsInRange:

Check if the point the algorithm is looking at, is in range of the grid.

*/

class FindVacantPosition : public Colleague
{
private:
	int m_gridWidth;
	int m_gridHeight;
	class Positions * m_pPositions;

	bool IsInRange(const int& x, const int& y) const;
public:
	FindVacantPosition(const int& gridWidth, const int& gridHeight, class GameUpdatesMediator * pGameUpdatesMediator);
	void ResetGridDimensions(const int& gridWidth, const int& gridHeight);
	void GetPositionOnGrid(int * pX, int * pY);
	void EmptyPositions() const;
	class GameUpdatesMediator * GetGameUpdatesMediator() const;
	int GetWidth() const;
	int GetHeight() const;
	~FindVacantPosition();
};

