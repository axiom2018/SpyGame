#include "EnemyManager.h"
#include "EnemyQueueLinkedList.h"
#include "EnemyObjectPool.h"
#include "Positions.h"
#include "Enemy.h"
#include "EnemyFactory.h"
#include "FindVacantPosition.h"
#include "Node.h"

EnemyManager::EnemyManager(const int& totalLevels, class GameUpdatesMediator * pGameUpdatesMediator, FindVacantPosition * pFindVacantPosition)
{
	// Save the width and the height so we can successfully pass to enemies so they can pick a random board position.
	// m_gridWidth = gridWidth;
	// m_gridHeight = gridHeight;

	// Set the minimum to a constant value. We'll say 2.
	m_minStartingEnemies = 2;

	// Initialize the linked list with the mediator argument passed since it will be the one in communication through the mediator.
	m_pEnemyQueueLinkedList = new EnemyQueueLinkedList(pGameUpdatesMediator);

	// Save the vacant position pointer.
	m_pFindVacantPosition = pFindVacantPosition;

	// Initialize the object pool.
	m_pEnemyObjectPool = new EnemyObjectPool;

	// Save total levels to help with object pool.
	m_totalLevels = totalLevels;

	/* We'll now create enemies and immediately throw them into the object pool. Why? Let's say we have 4 levels to play. then that means we'll have 5 enemies
	to use in total. Level 1 will start with 2 enemies, player beats level 1 and we send the 2 enemies back into the pool (back to 5). For level 2, we'll get
	one plus the last amount, so 3. We pick at random any 3 enemies and put them in the level and player beats it again, 3 enemies back into the pool. Now
	we're on level 3. So we'll ask for 4 random enemies, get them, put them on the grid, player beats the level, send them back into the pool. Now it's level
	4, we get all 5 and place them on the grid. This makes use of the object pool in an efficient manner and allows us to recycle objects and technically
	still have new ones there we didn't initially have. That's why the following for loop works so well, if the total level for the game is 2, we'll have 3 
	enemies (2 enemies for level 1, then use all 3 for the final level). Same concept if we had 3 levels to play, 4, 5, etc. */
	for (int i = 0; i < m_totalLevels + 1; ++i)
	{
		// Get a random value between how many enemies we have in the Enemy.cpp, right now just 3, so 0-2.
		int randVal = 0 + (rand() % 3);

		// Add an enemy, from the factory, to the object pool.
		m_pEnemyObjectPool->ReturnEnemy(EnemyFactory::CreateEnemy(randVal,  m_pFindVacantPosition, pGameUpdatesMediator));
	}

	// Push the default beginning value of enemies (2) into the queue.
	for (int i = 0; i < 2; ++i)
	{
		/* Getting an enemy will never result in nullptr being returned because even if we're only doing ONE level, it'll produce the minimum 2 enemies
		for the one and only level. If we're doing 2 levels. 2 + 1 = 3, we'll have 3 enemies in total and still only take 2 out in this point in the code. */
		m_pEnemyQueueLinkedList->Enqueue(m_pEnemyObjectPool->GetEnemy());
	}
}

bool EnemyManager::Draw(const int & x, const int & y)
{
	// Draw an enemy at x and y if one has that position.
	if (m_pEnemyQueueLinkedList->DrawEnemy(x, y))
	{
		return true;
	}
	
	return false;
}

void EnemyManager::SendEnemiesToPool()
{
	// While we still have enemies in the queue linked list, do these actions.
	while (m_pEnemyQueueLinkedList->GetSize() > 0)
	{
		// Get the enemy that's available.
		Enemy * pEnemy = m_pEnemyQueueLinkedList->Dequeue();

		// Give it to the pool.
		m_pEnemyObjectPool->ReturnEnemy(pEnemy);
	}
}

void EnemyManager::GetEnemiesFromPool()
{
	// Loop, get the maximum enemies for a level, that's 3.
	for (int i = 0; i < m_minStartingEnemies; ++i)
	{
		// Get the enemy.
		Enemy * pEnemy = m_pEnemyObjectPool->GetEnemy();

		if (!pEnemy)
		{
			break;
		}

		pEnemy->ResetEnemyData();

		// If valid, push to the queue.
		m_pEnemyQueueLinkedList->Enqueue(pEnemy);
	}
}

void EnemyManager::ClearEnemyPositions()
{
	// Using the singleton object wipe all enemy positions.
	m_pFindVacantPosition->EmptyPositions();
}

void EnemyManager::IncreaseTotalEnemies()
{
	// Increment enemies to get.
	++m_minStartingEnemies;
}

bool EnemyManager::Update()
{
	// Update through the queue.
	if (m_pEnemyQueueLinkedList->Update())
	{
		return true;
	}

	return false;
}

void EnemyManager::ResetEnemyPositions()
{
	m_pEnemyQueueLinkedList->SetEnemiesToStartingPositions();
}

EnemyManager::~EnemyManager()
{
	delete m_pEnemyObjectPool;
	m_pEnemyObjectPool = nullptr;

	delete m_pEnemyQueueLinkedList;
	m_pEnemyQueueLinkedList = nullptr;
}
