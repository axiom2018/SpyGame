#include "Positions.h"

void Positions::AddPosition(const int & x, const int & y)
{
	m_positions.push_back(std::make_pair(x, y));
}

bool Positions::IsPositionOccupied(const int & x, const int & y)
{
	// Loop through and check all positions we currently have for a match.
	for (unsigned int i = 0; i < m_positions.size(); ++i)
	{
		if (x == m_positions.at(i).first && y == m_positions.at(i).second)
		{
			return true;
		}
	}

	return false;
}

void Positions::ClearPositions()
{
	m_positions.clear();
}