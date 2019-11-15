#pragma once

/* Reasoning for this class:

Will manage when the game is actually over.

																				Class member variables:

1) Reasoning for m_totalLevels:

Variable for determining the last level. When our current level surpassses that, game over.


2) Reasoning for m_currentLevel:

The current level the player is on.


																				Class functions:

1) Reasoning for constructor:

Initialize variables.


2) Reasoning for IncreaseLevel:

Bump up the level by 1 when the player reaches the end of that level.


3) Reasoning for GetCurrentLevel & GetFinalLevel:

In World.cpp we let the user know which level they're playing on until they win.


																				Class functions (private):

1) 

*/

class MaxLevels
{
private:
	int m_totalLevels;
	int m_currentLevel;
public:
	MaxLevels(const int& totalLevels);
	bool IncreaseLevel();
	int GetCurrentLevel() const;
	int GetFinalLevel() const;
};

