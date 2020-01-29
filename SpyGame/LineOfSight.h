#pragma once
#include "Colleague.h"

/* Reasoning for this class: 

The enemy will detect the player based on if they're able to see them. 

																				Class member variables:
																				
1) Reasoning for m_enemyChar:

Save the enemy character, so we know which direction it's facing due to helper functions.


2) Reasoning for m_worldWidth & m_worldHeight:

Save dimensions to not go over bounds.


3) Reasoning for m_pEnemyX & m_pEnemyY:

We'll need to know where the enemy IS in order to begin calculations.


4) Reasoning for m_currentChar:

Let's keep hold of the current direction it's facing, this is the "start" of the algorithm.


5) Reasoning for m_sightDistance:

This is the maximum the enemy can see to possibly see the player and make them lose due to being detected.


6) Reasoning for m_travelX & m_travelY:

This will be assigned the STARTING position where we'll look. If enemy is facing left at x 5 and y 5, travel x and y will be 4, 5.


7) Reasoning for m_travelCounter:

See how much space is left we're allowed to check before the algorithm ends.



																				Class functions:
																				
1) Reasoning for constructor:

Initialize the algorithm.


2) Reasoning for Update:

Determine if the player was found or not.


3) Reasoning for UpdateDimensions:

Update the width and height to keep enemies properly looking for player.


																				Class functions (private):
																				
1) Reasoning for UpdateDirection:

We'll take in the first char in the constructor, m_pEnemyChar and decide what direction we're looking at, so we know where to begin the algorithm.


2) Reasoning for IsInBounds:

Determine if the next step to check is in the bounds of the dynamic grid.


3) Reasoning for DecrementTravel:

Decrease to the next spot the line of sight must look to see if player is there.


4) Reasoning for CheckForWall:

It would be stupid if an enemy saw through a wall, this helps prevent that.

*/

class LineOfSight : public Colleague
{
private:
	const char * m_pEnemyChar;
	int m_worldWidth;
	int m_worldHeight;
	int * m_pEnemyX;
	int * m_pEnemyY;
	char m_currentChar;
	int m_sightDistance;
	int m_travelX;
	int m_travelY;
	int m_travelCounter;

	bool CheckForWall() const;
	void DecrementTravel();
	bool IsInBounds();
	void UpdateDirection();
public:
	LineOfSight(char * pEnemyChar, int * pEnemyX, int * pEnemyY, const int& sightDistance, class GameUpdatesMediator * pGameUpdatesMediator);
	bool Update(const int& playerX, const int& playerY);
	void UpdateDimensions();
};

