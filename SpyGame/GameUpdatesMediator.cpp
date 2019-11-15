#include "GameUpdatesMediator.h"
#include "Colleague.h"

void GameUpdatesMediator::Register(Colleague * pColleague)
{
	m_pColleagues.push_back(pColleague);
}

void GameUpdatesMediator::Unregister(Colleague * pColleague)
{
	for (unsigned int i = 0; i < m_pColleagues.size(); ++i)
	{
		if (m_pColleagues.at(i) == pColleague)
		{
			m_pColleagues.erase(m_pColleagues.begin() + i);
			return;
		}
	}
}

std::pair<int, int> GameUpdatesMediator::ReceiveCoordinates(Colleague * pColleague)
{
	// Loop over the colleagues.
	for (unsigned int i = 0; i < m_pColleagues.size(); ++i)
	{
		// Attempt to get coordinates from the PROPER class that should get this request.
		std::pair<int, int> coords = m_pColleagues.at(i)->ReturnRequestedCoordinates();

		// If the coordinates returned are NOT -1's, the right class processed the request, exit function by returning coordinates.
		if (coords.first != k_defaultValue && coords.second != k_defaultValue)
		{
			return coords;
		}
	}

	return std::pair<int, int>();
}

bool GameUpdatesMediator::PlaceWall(const int & x, const int & y) const
{
	// Loop over the colleagues.
	for (unsigned int i = 0; i < m_pColleagues.size(); ++i)
	{
		// Save the result of the function in a boolean.
		bool result = m_pColleagues.at(i)->PlaceWallAtPosition(x, y);

		// If the boolean result is true, the right class processed the function, return true.
		if (result)
		{
			return true;
		}
	}

	return false;
}

bool GameUpdatesMediator::IsWallHere(const int & x, const int & y) const
{
	// Loop over the colleagues.
	for (unsigned int i = 0; i < m_pColleagues.size(); ++i)
	{
		// Save the result of the function in a boolean.
		bool result = m_pColleagues.at(i)->IsWallAtPosition(x, y);

		// If the boolean result is true, the right class processed the function, return true.
		if (result)
		{
			return true;
		}
	}

	return false;
}

bool GameUpdatesMediator::IsLevelTargetHere(const int & x, const int & y) const
{
	// Loop over the colleagues.
	for (unsigned int i = 0; i < m_pColleagues.size(); ++i)
	{
		// Save the result of the function in a boolean.
		bool result = m_pColleagues.at(i)->IsLevelTargetAtPosition(x, y);

		// If the boolean result is true, the right class processed the function, return true.
		if (result)
		{
			return true;
		}
	}

	return false;
}

bool GameUpdatesMediator::ResetWallCoordinate(const int & x, const int & y) const
{
	// Loop over the colleagues.
	for (unsigned int i = 0; i < m_pColleagues.size(); ++i)
	{
		// Save the result of the function in a boolean.
		bool result = m_pColleagues.at(i)->ResetWallAtPosition(x, y);

		// If the boolean result is true, the right class processed the function, return true.
		if (result)
		{
			return true;
		}
	}

	return false;
}

Node * GameUpdatesMediator::GetGrid() const
{
	// Loop over the colleagues.
	for (unsigned int i = 0; i < m_pColleagues.size(); ++i)
	{
		// Save the result of the function in a boolean.
		Node * pResult = m_pColleagues.at(i)->Get2DGrid();

		// If the boolean result is true, the right class processed the function, return true.
		if (pResult)
		{
			return pResult;
		}
	}

	return nullptr;
}