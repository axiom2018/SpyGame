#include "EnemyQueueLinkedList.h"
#include "EnemyNode.h"
#include "GameUpdatesMediator.h"
#include "Enemy.h"

EnemyQueueLinkedList::EnemyQueueLinkedList(GameUpdatesMediator * pGameUpdatesMediator)
{
	// Initialize the variables.
	m_pFront = nullptr;
	m_pBack = nullptr;
	m_size = 0;

	// Set mediator.
	m_pGameUpdatesMediator = pGameUpdatesMediator;

	// Register with mediator.
	m_pGameUpdatesMediator->Register(this);
}

EnemyNode * EnemyQueueLinkedList::CreateNode(Enemy * pEnemy)
{
	EnemyNode * pEnemyNode = new EnemyNode;
	pEnemyNode->m_pEnemy = pEnemy;
	pEnemyNode->m_pNext = nullptr;
	return pEnemyNode;
}

bool EnemyQueueLinkedList::IsEmpty() const
{
	if (!m_pFront)
	{
		return true;
	}

	return false;
}

void EnemyQueueLinkedList::Enqueue(Enemy * pEnemy)
{
	// Create the node.
	EnemyNode * pEN = CreateNode(pEnemy);

	// If empty, add to the front.
	if (IsEmpty())
	{
		m_pFront = m_pBack = pEN;
		pEN = nullptr;
	}

	else
	{
		m_pBack->m_pNext = pEN;
		m_pBack = pEN;
	}

	// Increment after insertion.
	++m_size;
}

Enemy * EnemyQueueLinkedList::Dequeue()
{
	// Check if empty, if so, can't dequeue.
	if (IsEmpty())
	{
		return nullptr;
	}

	// Save the node.
	EnemyNode * pEN = m_pFront;

	// Now the actual enemy.
	Enemy * pEnemy = pEN->m_pEnemy;

	// Send front forward.
	m_pFront = m_pFront->m_pNext;

	// Now the node.
	delete pEN;
	pEN = nullptr;

	// Decrement size.
	--m_size;

	// Return the enemy.
	return pEnemy;
}

bool EnemyQueueLinkedList::DrawEnemy(const int & x, const int & y) const
{
	// Save front node.
	EnemyNode * pEN = m_pFront;

	// Loop.
	while (pEN)
	{
		// Attempt to draw, if successful, return early since no other enemy can be drawn to same position.
		if (pEN->m_pEnemy->Draw(x, y))
		{
			return true;
		}

		// Move to next node.
		pEN = pEN->m_pNext;
	}

	return false;
}

int EnemyQueueLinkedList::GetSize() const
{
	return m_size;
}

bool EnemyQueueLinkedList::Update()
{
	// Save front node.
	EnemyNode * pEN = m_pFront;

	// Test receiving the coordinates.
	std::pair<int, int> coords = m_pGameUpdatesMediator->ReceiveCoordinates();

	// Loop.
	while (pEN)
	{
		// Update.
		if (pEN->m_pEnemy->Update(coords.first, coords.second))
		{
			return true;
		}

		// Move to next node.
		pEN = pEN->m_pNext;
	}

	return false;
}

void EnemyQueueLinkedList::ResetEnemyData()
{
	// Save front node.
	EnemyNode * pEN = m_pFront;

	// Loop.
	while (pEN)
	{
		// Reset the enemies.
		pEN->m_pEnemy->ResetEnemyData();

		// Move to next node.
		pEN = pEN->m_pNext;
	}
}

void EnemyQueueLinkedList::SetEnemiesToStartingPositions()
{
	// Save front node.
	EnemyNode * pEN = m_pFront;

	// Loop.
	while (pEN)
	{
		// Reset the enemies.
		pEN->m_pEnemy->BackToStartingPosition();

		// Move to next node.
		pEN = pEN->m_pNext;
	}
}

EnemyQueueLinkedList::~EnemyQueueLinkedList()
{
	// Start from the front and begin deleting the enemies.
	EnemyNode * pEnemyNode = m_pFront;
	
	while (pEnemyNode)
	{
		EnemyNode * pDelete = pEnemyNode;
		pEnemyNode = pEnemyNode->m_pNext;
		delete pDelete->m_pEnemy;
		pDelete->m_pEnemy = nullptr;
		delete pDelete;
		pDelete = nullptr;
		--m_size;
	}
}
