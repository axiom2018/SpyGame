#pragma once
#include "Enemy.h"

class Stationary : public Enemy
{
private:
	const int k_sightDistance = 4;
	class AdjustDirection * m_pAdjustDirection;
public:
	Stationary(class FindVacantPosition * pFindVacantPosition, class GameUpdatesMediator * pGameUpdatesMediator);
	virtual bool Draw(const int& x, const int& y) override;
	virtual void ResetEnemyData() override;
	virtual bool Update(const int& playerX, const int& playerY) override;
	~Stationary();
};

