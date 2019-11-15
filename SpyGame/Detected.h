#pragma once

/* Reasoning for this class:

Keep track of how many times the player is detected, if they were in fact detected by any enemy at all. Follows SRP.

																				Class member variables:

1) Reasoning for m_detectionLimit:

The maximum number of times player is allowed to be detected before game is over.


2) Reasoning for m_currentTimesDetected:

The current amount of times player has been detected.



																				Class functions:

1) Reasoning for constructor:

Initialize variables.


2) Reasoning for IncrementTimesDetected:

If player is caught increment this variable to get closer to game over.


3) Reasoning for IsGameOver:

If current times detected exceeds or equals detection limit, game over.


4) Reasoning for GetDetectionLimit:

Display on the screen.


5) Reasoning for GetCurrentTimesDetected:

Display on screen.



																				Class functions (private):

1)

*/

class Detected
{
private:
	static const int k_detectionLimit = 3;
	int m_currentTimesDetected;
public:
	Detected();
	void IncrementTimesDetected();
	bool IsGameOver() const;
	int GetDetectionLimit() const;
	int GetCurrentTimesDetected() const;
};

