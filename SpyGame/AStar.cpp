#include "AStar.h"
#include "Node.h"
#include "World.h"
#include "GameUpdatesMediator.h"
#include "Node.h"
#include "Constants.h"
#include <iostream>

AStar::AStar(const int& endX, const int& endY, int * pX, int * pY, GameUpdatesMediator * pGameUpdatesMediator)
{
	// Initialize start and end nodes.
	m_pStart = nullptr;
	m_pEnd = nullptr;

	// Save the position pointer variables.
	m_pX = pX;
	m_pY = pY;

	// Allocate mediator.
	m_pGameUpdatesMediator = pGameUpdatesMediator;

	// Register this.
	m_pGameUpdatesMediator->Register(this);

	// Get the width and height of the grid we're working with.
	std::pair<int, int> size = m_pGameUpdatesMediator->GetWidthAndHeightOfGrid();
	m_width = size.first;
	m_height = size.second;

	// Assign nodes with proper x and y coordinates.
	SetNodesAndSolve(endX, endY);
}

void AStar::SolveAStar(std::vector<std::pair<int, int>> * pCoordVec)
{
	// Use mediator to get the grid.
	Node * pNodeGrid = m_pGameUpdatesMediator->GetGrid();

	for (int x = 0; x < m_height; ++x)
	{
		for (int y = 0; y < m_width; ++y)
		{
			pNodeGrid[y * m_height + x].m_visited = false;
			pNodeGrid[y * m_height + x].m_global = INFINITY;
			pNodeGrid[y * m_height + x].m_local = INFINITY;
			pNodeGrid[y * m_height + x].m_pParent = nullptr;
		}
	}

	// Distances. We don't know them here and we'll use pythagoraus theorem.
	auto distance = [](Node * a, Node * b)
	{
		return sqrtf(float((a->m_x - b->m_x)*(a->m_x - b->m_x) + (a->m_y - b->m_y)*(a->m_y - b->m_y)));
	};

	// Heuristic calculations. Just returns the distance.
	auto heuristic = [distance](Node* a, Node* b)
	{
		return distance(a, b);
	};

	// Begin algorithm with start node.
	Node * pNodeCurrent = m_pStart;
	m_pStart->m_local = 0.0f;
	// global is distance which is distance between start and end locations.
	m_pStart->m_global = heuristic(m_pStart, m_pEnd);

	// Get list of nodes that have not been tested yet or to BE tested.
	std::list<Node*> listOfNodesNotTested;
	// Push the start node, it WILL be tested.
	listOfNodesNotTested.push_back(m_pStart);

	// The algorithm will be done with a while loop to test if we've still got nodes to test.
	while (!listOfNodesNotTested.empty() && pNodeCurrent != m_pEnd)
	{
		// Sort the list into ascending order of global goals with lambda function.
		listOfNodesNotTested.sort([](const Node* lhs, const Node* rhs) { return lhs->m_global < rhs->m_global; });

		// Implies element at START of the list has the loweest global, so maybe it's the best! BUT the list may contain a node we've already visited.
		while (!listOfNodesNotTested.empty() && listOfNodesNotTested.front()->m_visited)
		{
			listOfNodesNotTested.pop_front();
		}

		// MUST check if it's empty, stop the algorithm.
		if (listOfNodesNotTested.empty())
		{
			break;
		}

		// Set the current nodeat list front to begin.
		pNodeCurrent = listOfNodesNotTested.front();
		// MUST set visited to true so we don't revisit.
		pNodeCurrent->m_visited = true;

		// Now we check the nodes neighbhors.
		for (auto nodeNeighbor : pNodeCurrent->m_neighbors)
		{
			// If we've not visited it, we want to add it to the list, AND if it's an obstacle, we also don't want to add it to the list.
			if (!nodeNeighbor->m_visited && nodeNeighbor->m_obstacle == 0)
			{
				listOfNodesNotTested.push_back(nodeNeighbor);
			}

			// Now we calculate the local goals. Is current local PLUS the distance TO the neighbhor, less than neighbhors local?
			float maybeLowerGoal = pNodeCurrent->m_local + distance(pNodeCurrent, nodeNeighbor);

			// If the above is true, the local + distance is less than neighbhors goal, we update neighbhor.
			if (maybeLowerGoal < nodeNeighbor->m_local)
			{
				// Update the neighbhors parent AND the local.
				nodeNeighbor->m_pParent = pNodeCurrent;
				nodeNeighbor->m_local = maybeLowerGoal;

				// Now set the global with the help of the heuristic.
				nodeNeighbor->m_global = nodeNeighbor->m_local + heuristic(nodeNeighbor, m_pEnd);
			}
		}
	}


	// Drawing the path means taking the ENDS location and drawing it backwards following the parents. If end location is not null, create temp pointer to the node.
	if (m_pEnd != nullptr)
	{
		// Save the end.
		Node * p = m_pEnd;

		// Continue this while it has a parent.
		while (p->m_pParent != nullptr)
		{
			// Push coordinate to vector.
			pCoordVec->push_back(std::pair<int, int>(p->m_x, p->m_y));

			// If node does have parent, we can backtrack!
			p = p->m_pParent;
		}
	}

	// Push back the start coordinate in the vector.
	pCoordVec->push_back(std::pair<int, int>(m_pStart->m_x, m_pStart->m_y));
	
	// FLIP the vector because it's backwards at the moment.
	std::reverse(pCoordVec->begin(), pCoordVec->end());
}

void AStar::SetNodesAndSolve(const int & endX, const int & endY)
{
	// Use mediator to get the grid.
	Node * pGameGrid = m_pGameUpdatesMediator->GetGrid();

	// Get start node.
	m_pStart = &pGameGrid[*m_pX * m_height + *m_pY];

	// Get end node.
	m_pEnd = &pGameGrid[endX * m_height + endY];

	// Set index to 1 to traverse vector properly.
	m_index = 1;

	// Solve A star.
	SolveAStar(&m_coordinates);
}

void AStar::ResetPath(const int& endX, const int& endY)
{
	// Clean out the coordinate vector.
	m_coordinates.clear();

	// Get the width and height of the grid we're working with.
	std::pair<int, int> size = m_pGameUpdatesMediator->GetWidthAndHeightOfGrid();
	m_width = size.first;
	m_height = size.second;

	// Assign nodes with proper x and y coordinates.
	SetNodesAndSolve(endX, endY);
}

void AStar::SetBackToStartingPosition()
{
	// Set index back to 1.
	m_index = 1;

	// Set x and y.
	*m_pX = m_coordinates.at(0).second;
	*m_pY = m_coordinates.at(0).first;
}

void AStar::Update()
{
	// Get vector size.
	int size = (int)m_coordinates.size();

	// If index is less than size, switch to new location.
	if (m_index < size)
	{
		// Set the x and y according to the coordinates.
		*m_pX = m_coordinates.at(m_index).second;
		*m_pY = m_coordinates.at(m_index).first;

		// Increment to move onto the next one.
		++m_index;
	}

	else
	{
		// FLIP the vector because we need to start from the other end.
		std::reverse(m_coordinates.begin(), m_coordinates.end());

		// Set index to 1.
		m_index = 1;
	}
}
