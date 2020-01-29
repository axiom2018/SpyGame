#pragma once

/* Reasoning for this class:

Create different kinds of enemy objects.

																				Class member variables:

1) 

																				Class functions:

1) Reasoning for CreateEnemy:

Factory function to create enemies.

																				Class functions (private);

1) 

*/

class EnemyFactory
{
public:
	static class Enemy * CreateEnemy(const int& choice, class FindVacantPosition * pFindVacantPosition, class GameUpdatesMediator * pGameUpdatesMediator);
};

