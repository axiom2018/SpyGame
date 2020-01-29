#pragma once
#include "Colleague.h"
#include <list>

/* Reasoning for this class:

This A * algorithm is popular from my research and is an improvement on dijkstra's algorithm. I'll be honest when I say it took me a full 2 weeks to understand 
this algorithm so finally seeing the result is so amazing to me.

																				Class member variables:

1) Reasoning for m_pStart & m_pEnd:

The nodes to start and end the algorithm. 


2) Reasoning for m_width & m_height:

We'll be updating the grids details with these variables.


3) Reasoning for m_pX & m_pY:

The enemies x and y pointers to tell to assign it new values every update, the values are from the A * algorithms vector of course.


4) Reasoning for m_coordinates:

Save the coordinates in vector format specifically. A * has us use the nodes when the algorithm is immediately done to traverse. But we want the ability 
to traverse the path forwards, then backwards, using the vector allows this with ease.


5) Reasoning for m_index:

Keep the index of the vector to know which position to go to next.


																				Class functions:

1) Reasoning for constructor:

Initialize variables.


2) Reasoning for ResetPath:

Restore the path to the start when the player gets caught.


3) Reasoning for SetBackToStartingPosition:

When player gets caught, the enemy goes to the starting position in the vector produced by A *, other enemies don't need to go anywhere.


3) Reasoning for Update:

Allow the enemy to continue their path.

																				Class functions (private):

1) Reasoning for SetNodesAndSolve:

Simply get the start node and end node according to the graph, and then get the path. The code in it used to be in multiple places so condensing it to one function
is great.


2) Reasoning for SolveAStar:

Complete the A * algorithm to find us the best path we can.



*/

class AStar : public Colleague
{
private:
	struct Node * m_pStart;
	struct Node * m_pEnd;
	int m_width;
	int m_height;
	int * m_pX;
	int * m_pY;
	std::vector<std::pair<int, int>> m_coordinates;
	int m_index;

	void SolveAStar(std::vector<std::pair<int, int>> * pCoordVec);
	void SetNodesAndSolve(const int& endX, const int& endY);
public:
	AStar(const int& endX, const int& endY, int * pX, int * pY, class GameUpdatesMediator * pGameUpdatesMediator);
	void ResetPath(const int& endX, const int& endY);
	void SetBackToStartingPosition();
	void Update();
};
