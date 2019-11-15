#include "EnemyObjectPool.h"
#include "Enemy.h"

Enemy * EnemyObjectPool::GetEnemy()
{
	// Declare enemy pointer to return.
	Enemy * pEnemy = nullptr;
	
	// In order to get a random enemy, we must make sure there's more than ONE. If not, just return the one.
	if (m_pResources.size() == 1)
	{
		// Since we do have things in the pool, get the first one.
		pEnemy = m_pResources.front();

		// Remove the front from the list.
		m_pResources.erase(m_pResources.begin());

		// Return the one enemy.
		return pEnemy;
	}

	else if (m_pResources.size() > 1)
	{
		// Get the size.
		int size = m_pResources.size();

		// Get the random value according to the size. Ex: If we have 2 in the vector, we'll either get 0 or 1 for an index position.
		int randomValue = 0 + (rand() % size);

		// Save the enemy according to the randomValue.
		pEnemy = m_pResources.at(randomValue);

		// Erase that random value entry.
		m_pResources.erase(m_pResources.begin() + randomValue);
	}

	// Return the enemy. MIGHT return nullptr if the id of the enemy requested was not found, we MUST check for nullptr when this function is used!
	return pEnemy;
}

void EnemyObjectPool::ReturnEnemy(Enemy * pEnemy)
{
	m_pResources.push_back(pEnemy);
}

EnemyObjectPool::~EnemyObjectPool()
{
	// Clear out the enemies if we have any here.
	for (std::vector<Enemy*>::iterator i = m_pResources.begin(); i != m_pResources.end(); ++i)
	{
		if ((*i))
		{
			delete (*i);
			(*i) = nullptr;
		}
	}
}
