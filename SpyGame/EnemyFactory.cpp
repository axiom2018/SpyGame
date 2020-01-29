#include "EnemyFactory.h"
#include "Stationary.h"
#include "StationaryRotation.h"
#include "TwoPoint.h"
#include "FindVacantPosition.h"
#include "Node.h"

Enemy * EnemyFactory::CreateEnemy(const int & choice, FindVacantPosition * pFindVacantPosition, class GameUpdatesMediator * pGameUpdatesMediator)
{
	switch (choice)
	{
	case 0:
		return new Stationary(pFindVacantPosition, pGameUpdatesMediator);
	case 1:
		return new StationaryRotation(pFindVacantPosition, pGameUpdatesMediator);
	case 2:
		return new TwoPoint(pFindVacantPosition, pGameUpdatesMediator);
	default:
		break;
	}

	return nullptr;
}
