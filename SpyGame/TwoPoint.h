//#pragma once
#include "Enemy.h"

class TwoPoint : public Enemy
{
private:
	const int k_sightDistance = 6;
	int m_endPointX;
	int m_endPointY;
	class AStar * m_pAStar;
public:
	TwoPoint(const int& gridWidth, const int& gridHeight, class FindVacantPosition * pFindVacantPosition, class GameUpdatesMediator * m_pGameUpdatesMediator);
	virtual bool Draw(const int& x, const int& y) override;
	virtual bool Update(const int& playerX, const int& playerY) override;
	virtual void ResetEnemyData() override;
	virtual void BackToStartingPosition() override;
	~TwoPoint();
};