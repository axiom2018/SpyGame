#pragma once
#include <vector>

// This is the base node for the 2d grid.

struct Node
{
	char m_displayCharacter;
	int m_colorValue;
	bool m_obstacle = false;
	bool m_visited = false;
	float m_global;
	float m_local;
	int m_x;
	int m_y;
	std::vector<Node*> m_neighbors;
	Node * m_pParent;
};