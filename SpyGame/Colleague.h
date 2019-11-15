#pragma once
#include "Constants.h"
#include "Node.h"
#include <iostream>

// Part of the mediator design pattern.

class Colleague
{
protected:
	class GameUpdatesMediator * m_pGameUpdatesMediator;
public:
	virtual std::pair<int, int> ReturnRequestedCoordinates() { return std::make_pair(k_defaultValue, k_defaultValue); }
	virtual bool PlaceWallAtPosition(const int& x, const int& y) const { return false; }
	virtual bool IsWallAtPosition(const int& x, const int& y) const { return false; }
	virtual bool IsLevelTargetAtPosition(const int& x, const int& y) const { return false; }
	virtual bool ResetWallAtPosition(const int& x, const int& y) const { return false; }
	virtual Node * Get2DGrid() const { return nullptr; }
	virtual bool ColorGridPosition(const int& x, const int& y) { return false; }
};