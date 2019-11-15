#pragma once

/* Reasoning for this class:

Manage all the enemies in the game.


																				Class member variables:

1) Reasoning for m_pEnemyQueueLinkedList:

Keep the portion of enemies in the linked list while they're not in the pool.


2) Reasoning for m_pEnemyObjectPool:

Keep the pool to grab enemies that were most likely used on a previous level and use them again instead of deleting them. Recycling is good!


3) Reasoning for m_pFindVacantPosition:

Passed to all enemies created to find a vacant position on the grid and stored here to clear the class of positions when a new level comes up.


4) Reasoning for m_gridWidth & m_gridHeight:

Keep note of the width and height of the grid and pass to the enemies.


5) Reasoning for m_minStartingEnemies:

When we first start the game, we'll have 2 enemies, player then beats the level, send the enemies to the pool, increase the enemies total to 3. We'll get the 2 enemies from
the pool, plus create one.


6) Reasoning for m_totalLevels:

Save the total levels we'll play in the game, this is needed to create a certain amount of enemies we'll definitely need so the pool won't have any unused resources.


																				Class functions:

1) Reasoning for constructor:

Initialize variables.


2) Reasoning for Draw:

Draw enemies.


3) Reasoning for SendEnemiesToPool:

After the player has reached a level, we want to recycle the enemies that are currently being used, we do that by sending them all to the pool.


4) Reasoning for GetEnemiesFromPool:

Recycle old enemies from the pool and put them back into the queue with the NEW grids width and height applied so they can choose a potentially new position.


5) Reasoning for ClearEnemyPositions:

Reset the singleton that contains the vector of all enemy positions.


6) Reasoning for IncreaseTotalEnemies:

Bump this value up so the next time we


6) Reasoning for Update:

Update the enemies.


7) Reasoning for ResetEnemyPositions:

Reset all enemies to starting positions, IF they moved.


) Reasoning for destructor:

Clean memory.


																				Class functions (private):

1)

*/

class EnemyManager
{
private:
	class EnemyQueueLinkedList * m_pEnemyQueueLinkedList;
	class EnemyObjectPool * m_pEnemyObjectPool;
	class FindVacantPosition * m_pFindVacantPosition;

	int m_gridWidth;
	int m_gridHeight;
	int m_minStartingEnemies;
	int m_totalLevels;
public:
	EnemyManager(const int& gridWidth, const int& gridHeight, int totalLevels, class GameUpdatesMediator * pGameUpdatesMediator, class FindVacantPosition * pFindVacantPosition);
	bool Draw(const int& x, const int& y);
	void SendEnemiesToPool();
	void GetEnemiesFromPool(const int& gridWidth, const int& gridHeight);
	void ClearEnemyPositions();
	void IncreaseTotalEnemies();
	bool Update();
	void ResetEnemyPositions();
	~EnemyManager();
};

