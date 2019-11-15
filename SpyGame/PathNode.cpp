#include "PathNode.h"

bool PathNode::operator==(const PathNode & o)
{
	return m_pos == o.m_pos;
}

bool PathNode::operator==(const Point & o)
{
	return m_pos == o;
}

bool PathNode::operator<(const PathNode & o)
{
	return m_distance + m_cost < o.m_distance + o.m_cost;
}

void PathNode::SetCost(const int & cost)
{
	m_cost = cost;
}

void PathNode::SetPosition(const Point & point)
{
	m_pos = point;
}

void PathNode::SetParent(const Point & parent)
{
	m_parent = parent;
}

void PathNode::SetDistance(const int & distance)
{
	m_distance = distance;
}

int PathNode::GetCost() const
{
	return m_cost;
}

Point PathNode::GetPosition() const
{
	return m_pos;
}

Point PathNode::GetParent() const
{
	return m_parent;
}

int PathNode::GetDistance() const
{
	return m_distance;
}
