#pragma once
#include "Colleague.h"
#include "Node.h"

/* Reasoning for class:

The controller of the game. 


																				Class member variables:

1) Reasoning for m_pWorld:

Part of the singleton design pattern.


2) Reasoning for m_pNode:

The 2d array that will represent the board in the game.


3) Reasoning for m_pPlayer:

Set up the player character.


4) Reasoning for m_pBlockManager:

Create the blocks, or the areas neither player or AI can walk over.


5) Reasoning for EnemyManager:

Manage all enemies.


6) Reasoning for k_minGridX/k_maxGridX/k_minGridY/k_maxGridY:

The ranges needed to make a dynamically sized grid.


7) Reasoning for k_obstacle:

The border that no entity can get through or past.


8) Reasoning for m_gridX & m_gridY:

The dynamic/random size of the grid generated.


9) Reasoning for GameUpdatesMediator:

Handles communications between player and Enemy Manager to give proper player position to all the enemies for the line of sight system.


10) Reasoning for LevelTarget:

It's the goal for the player to get to in order to advance the level.


11) Reasoning for m_pFindVacantPosition:

Find an empty position on the grid.


12) Reasoning for m_pMaxLevels:

Keep track of how many levels we go through before player wins.


13) Reasoning for m_pDetected:

Be able to tell when player has been caught too many times and end the game!


																				Class functions:

1) Reasoning for GetInstance:

Part of the singleton design pattern.


2) Reasoning for PrintGrid:

Display the 2d grid with std::cout.


3) Reasoning for Update:

Update game to proceed.


4) Reasoning for PlaceWallAtPosition:

For the block manager to put a wall here.


5) Reasoning for IsWallAtPosition:

Check if wall is located here, do not assign this position to enemy if so.


6) Reasoning for IsLevelTargetAtPosition:

Check if the level target is here so no enemy gets assigned to it's position.


7) Reasoning for ResetWallAtPosition:

When a certain wall set up won't actually work, undo it with this function.


8) Reasoning for Get2DGrid:

Allow specifically for the Astar algorithm to get the grid since it needs to have the proper starting node and ending node.


9) Reasoning for Delete:

Clean memory with a singleton with this slightly different way.


																				Class functions (private):

1) Reasoning for constructor:

Part of the singleton design pattern.


2) Reasoning for GenerateRandomSizedGrid:

Use random numbers to get the size of the grid.


3) Reasoning for BuildGrid:

Initialize memory for 2d array.


4) Reasoning for GenerateNewLevel:

When the player gets to the point across the screen, make a new level.


5) Reasoning for RestartLevel:

If player gets caught, restart the level.


6) Reasoning for Instructions:

Simple instructions for the gamer to play the game.


*/

class World : public Colleague
{
private:
	static World * m_pWorld;
	Node * m_pGrid;
	class Player * m_pPlayer;
	class BlockManager * m_pBlockManager; 
	class EnemyManager * m_pEnemyManager;
	static const int k_minGridX = 25;
	static const int k_maxGridX = 40;
	static const int k_minGridY = 10;
	static const int k_maxGridY = 15;
	const char k_obstacle = '#';
	int m_gridX;
	int m_gridY;
	class GameUpdatesMediator * m_pGameUpdatesMediator;
	class LevelTarget * m_pLevelTarget;
	class FindVacantPosition * m_pFindVacantPosition;
	class MaxLevels * m_pMaxLevels;
	class Detected * m_pDetected;

	void Instructions() const;
	void ClearScreenAndShowCurrentGrid() const; // Delete later.
	void RestartLevel();
	void GenerateNewLevel();
	void BuildGrid();
	void GenerateRandomSizedGrid();
	World();
public:
	static World * GetInstance();
	void PrintGrid() const;
	void Update();
	virtual bool PlaceWallAtPosition(const int& x, const int& y) const override;
	virtual bool IsWallAtPosition(const int& x, const int& y) const override;
	virtual bool IsLevelTargetAtPosition(const int& x, const int& y) const override;
	virtual bool ResetWallAtPosition(const int& x, const int& y) const override;
	virtual Node * Get2DGrid() const override;
	void Delete();
};

