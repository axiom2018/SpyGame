#include "MaxLevels.h"

MaxLevels::MaxLevels(const int& totalLevels)
{
	// Make sure total levels is a proper value by seeing if it's less than or equal to 0.
	if (totalLevels <= 0)
	{
		// If so, don't save the argument in our class variable, save a default value we create here.
		m_currentLevel = 1;
		m_totalLevels = 1;
		
		return;
	}

	// Set the current level to level 1.
	m_currentLevel = 1;

	// Set the total levels.
	m_totalLevels = totalLevels;
}

bool MaxLevels::IncreaseLevel()
{
	// Increment the level.
	++m_currentLevel;

	// Check if it's greater than total levels. If so, game over, return true.
	if (m_currentLevel > m_totalLevels)
	{
		return true;
	}

	return false;
}

int MaxLevels::GetCurrentLevel() const
{
	return m_currentLevel;
}

int MaxLevels::GetFinalLevel() const
{
	return m_totalLevels;
}
