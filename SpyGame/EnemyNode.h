#pragma once

// Used in EnemyQueueLinkedList.h/.cpp

struct EnemyNode
{
	class Enemy * m_pEnemy;
	EnemyNode * m_pNext;
};