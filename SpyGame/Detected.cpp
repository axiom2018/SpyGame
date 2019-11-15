#include "Detected.h"
#include "Constants.h"

Detected::Detected()
{
	m_currentTimesDetected = 0;
}

void Detected::IncrementTimesDetected()
{
	++m_currentTimesDetected;
}

bool Detected::IsGameOver() const
{
	if (m_currentTimesDetected >= k_detectionLimit)
	{
		return true;
	}

	return false;
}

int Detected::GetDetectionLimit() const
{
	return k_detectionLimit;
}

int Detected::GetCurrentTimesDetected() const
{
	return m_currentTimesDetected;
}
