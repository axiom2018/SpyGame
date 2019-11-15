#pragma once
#include <vector>

/* Reasoning for this class:

Makes no sense to keep allocating memory for a new enemy when an enemy could be recycled. That's basically what the object pool is, a giant recycling system!


																				Class member variables:

1) Reasoning for m_pResources:

The list to hold all of the enemies.


																				Class functions:

1) Reasoning for Getenemy:

Return an enemy based on the id provided in the argument.


2) Reasoning for ReturnEnemy:

When we're done with an enemy in the grid and it's time to advance to the next level, pass all enemies to the pool by this function.


) Reasoning for destructor:

Wipe memory.


																				Class functions (private):

1)


*/

class EnemyObjectPool
{
private:
	std::vector<class Enemy*> m_pResources;
public:
	class Enemy * GetEnemy();
	void ReturnEnemy(class Enemy * pEnemy);
	~EnemyObjectPool();
};

