#pragma once
#include "Point.h"

/* Reasoning for this class:

For the A star algorithm. */

class PathNode
{
private:
	Point m_pos;
	Point m_parent;
	int m_distance;
	int m_cost;
public:
	bool operator == (const PathNode& o);
	bool operator == (const Point& o);
	bool operator < (const PathNode& o);

	void SetCost(const int& cost);
	void SetPosition(const Point& point);
	void SetParent(const Point& parent);
	void SetDistance(const int& distance);

	int GetCost() const;
	Point GetPosition() const;
	Point GetParent() const;
	int GetDistance() const;
};