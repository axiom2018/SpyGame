#pragma once
#include "Enemy.h"

class StationaryRotation : public Enemy
{
private:
	const int k_sightDistance = 5;
public:
	StationaryRotation(class FindVacantPosition * pFindVacantPosition, class GameUpdatesMediator * pGameUpdatesMediator);
	virtual bool Draw(const int& x, const int& y) override;
	virtual void ResetEnemyData() override;
	virtual bool Update(const int& playerX, const int& playerY) override;
	~StationaryRotation();
};

