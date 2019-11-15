#pragma once
#include "Colleague.h"

/* Reasoning for this class: 

Base class for the enemy system. Also a factory pattern.


																				Class member variables:

1) Reasoning for m_pDirectionalSystem:

Depending on where the enemy moves, they'll change characters.


2) Reasoning for m_pLineOfSight:

All of them will have to SEE the player in order for the player to get caught. This class handles that.


3) Reasoning for m_pFindVacantPosition:

Get a position that's empty for all of the enemies.


4) Reasoning for m_x & m_y:

The position for the enemy.


5) Reasoning for m_gridWidth & m_gridHeight:

Keep the size of the grid in over to make proper calculations regarding movement and line of sight.



																				Class functions:


1) Reasoning for Draw:

Draw the enemy.


2) Reasoning for ResetEnemyData:

When the player has reached a new level we must assign new values for the enemy.


3) Reasoning for Update:

Update the enemy.


4) Reasoning for BackToStartingPosition:

Only for the TwoPoint enemy, when the player is caught in a level and we're "restarting it", it's back to the first position the A * algorithm found.



																				Class functions (private/protected):


*/

class Enemy : public Colleague
{
protected:
	class DirectionalSystem * m_pDirectionalSystem;
	class LineOfSight * m_pLineOfSight;
	class FindVacantPosition * m_pFindVacantPosition;
	int m_x;
	int m_y;
	int m_gridWidth;
	int m_gridHeight;
public:
	virtual bool Draw(const int& x, const int& y) = 0;
	virtual void ResetEnemyData() = 0;
	virtual bool Update(const int& playerX, const int& playerY) = 0;
	virtual void BackToStartingPosition() {}
	virtual ~Enemy() {};
};
