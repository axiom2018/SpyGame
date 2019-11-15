#include "EnemyFactory.h"
#include "Stationary.h"
#include "StationaryRotation.h"
#include "TwoPoint.h"
#include "FindVacantPosition.h"
#include "Node.h"

Enemy * EnemyFactory::CreateEnemy(const int & choice, const int& gridWidth, const int& gridHeight, FindVacantPosition * pFindVacantPosition, 
	class GameUpdatesMediator * pGameUpdatesMediator)
{
	switch (choice)
	{
	case 0:
		return new Stationary(gridWidth, gridHeight, pFindVacantPosition, pGameUpdatesMediator);
	case 1:
		return new StationaryRotation(gridWidth, gridHeight, pFindVacantPosition, pGameUpdatesMediator);
	case 2:
		return new TwoPoint(gridWidth, gridHeight, pFindVacantPosition, pGameUpdatesMediator);
	default:
		break;
	}

	return nullptr;
}
