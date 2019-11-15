#pragma once
#include <vector>

/* Reasoning for this class:

One central object to hold all enemy positions for cross checking. 


																				Class member variables:

1) Reasoning for m_positions:

The vector of pairs of ints, which represent the x and y positions of the enemies.


																				Class functions:

1) Reasoning for AddPosition:

Self explanatory.


2) Reasoning for IsPositionOccupied:

Check for matching position.


3) Reasoning for ClearPositions:

If we've beat the level, the new level begins, the old one resets, so we must get rid of the old positions.



																				Class functions (private):

*/

class Positions
{
private:
	std::vector<std::pair<int, int>> m_positions;
public:
	void AddPosition(const int& x, const int& y);
	bool IsPositionOccupied(const int& x, const int& y);
	void ClearPositions();
};

