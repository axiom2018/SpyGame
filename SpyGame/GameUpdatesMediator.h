#pragma once
#include "Mediator.h"
#include <vector>

class GameUpdatesMediator : public Mediator
{
private:
	std::vector<class Colleague*> m_pColleagues;
public:
	virtual void Register(class Colleague * pColleague) override;
	virtual void Unregister(class Colleague * pColleague) override;
	virtual std::pair<int, int> ReceiveCoordinates() override;
	virtual bool PlaceWall(const int& x, const int& y) const override;
	virtual bool IsWallHere(const int& x, const int& y) const override;
	virtual bool IsLevelTargetHere(const int& x, const int& y) const override;
	virtual bool ResetWallCoordinate(const int& x, const int& y) const override;
	virtual Node * GetGrid() const override;
	// Testing function for getting the width and height of grid for other entities to use.
	virtual std::pair<int, int> GetWidthAndHeightOfGrid() const override;
};

