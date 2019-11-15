#pragma once

/* Reasoning for this class:

When enemies are spawned, there is a chance a stationary enemy can say, end up looking south while it's already at the bottom of the grid. If grid has
a y maximum of 9 (0-9 since arrays of course in C++ are indexed from 0), AND the enemy is looking SOUTH, it can't possibly detect the player. So this
class helps adjust the direction of the enemy when it's not in an ideal position to be effective. This does NOT apply to stationary rotation nor to
two point. Those enemies move around so even if they're placed "too south" they can still be effective.


																				Class member variables:

1) Reasoning for m_gridWidth & m_gridHeight:

We can't detect if a stationary enemy is too close south without first knowing the grid dimensions.


2) Reasoning for m_pX & m_pY:

Enemy position, must have it's actual position to even detect if it's too close south, east, etc. 


3) Reasoning for m_pEnemyChar:

Get the enemy char to change it if need be.

																				Class functions:

1) Reasoning for UpdateDimensions:

Be able to properly detect when the enemy has gotten too close to an edge on the grid.


																				Class functions (private):

1) Reasoning for EdgeCheck:

Be able to determine whether an enemy is too close to any edges, north, west, east or south. If so, then we further check if adjustment is necessary.


*/

class AdjustDirection
{
private:
	int m_gridWidth;
	int m_gridHeight;
	int * m_pX;
	int * m_pY;
	char * m_pEnemyChar;

	void EdgeCheck();
public:
	AdjustDirection(const int& width, const int& height, int * pX, int *pY, char * pEnemyChar);
	void UpdateDimensions(const int& width, const int& height);
};

