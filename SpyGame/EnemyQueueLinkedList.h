#pragma once
#include "Colleague.h"

/* Reasoning for this class:

We can add, at most, n enemies into the level due to the limitations of the width and height of the board. This technically allows us to freely add as much enemies as
we see fit.

																				Class member variables:

1) Reasoning for m_pFront & m_pBack:

The nodes for the queue.


2) Reasoning for m_size:

Keep the size of the linked list.


																				Class functions:

1) Reasoning for constructor:

Initialize variables.


2) Reasoning for Enqueue:

Add an enemy.


3) Reasoning for Dequeue:

Remove an enemy.


4) Reasoning for DrawEnemy:

Draw to the screen.


5) Reasoning for GetSize:

Assistance in the EnemyManager.cpp to return objects to the pool.


6) Reasoning for Update:

Allow enemy to update its internal system.


7) Reasoning for ResetEnemies:

When this function is called we reset enemy positions if they stray away from it.


) Reasoning for destructor:

Clean memory.


																				Class functions (private):
																				
1) Reasoning for CreateNode:

Create a node to add to the list.


2) Reasoning for IsEmpty:

If list is empty, we'll add the first node properly.
																				
*/

class EnemyQueueLinkedList : public Colleague
{
private:
	struct EnemyNode * m_pFront;
	struct EnemyNode * m_pBack;
	int m_size;

	struct EnemyNode * CreateNode(class Enemy * pEnemy);
	bool IsEmpty() const;
public:
	EnemyQueueLinkedList(class GameUpdatesMediator * pGameUpdatesMediator);
	void Enqueue(class Enemy * pEnemy);
	class Enemy * Dequeue();
	bool DrawEnemy(const int& x, const int& y) const;
	int GetSize() const;
	bool Update();
	void ResetEnemyData();
	void SetEnemiesToStartingPositions();
	~EnemyQueueLinkedList();
};

