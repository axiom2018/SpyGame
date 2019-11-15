#include "BlockManager.h"
#include "GameUpdatesMediator.h"
#include <iostream>
#include <Windows.h>
#include <conio.h>

// Set the grid width and height so proper calculations can occur for the blocks in a certain space.
BlockManager::BlockManager(const int& gridWidth, const int& gridHeight, class GameUpdatesMediator * pGameUpdatesMediator) :
	m_gridWidth(gridWidth),
	m_gridHeight(gridHeight),
	m_canPaint(false)
{
	// Set mediator.
	m_pGameUpdatesMediator = pGameUpdatesMediator;

	// Register with mediator.
	m_pGameUpdatesMediator->Register(this);

	// Assign the coordinates to create the blocks.
	AssignCoordinates();

	// Create x amount of blocks within the range of the points created.
	GenerateBlocks();
}

void BlockManager::AssignCoordinates()
{
	// Get the top left cooridnate by edge check. We want the corners so we have "bounds" to aim in to place the real blocks. 
	m_topLeft.m_x = k_edgeCheck;
	m_topLeft.m_y = k_edgeCheck;

	// Get the bottom left.
	m_bottomLeft.m_x = k_edgeCheck;
	m_bottomLeft.m_y = (m_gridHeight - k_edgeCheck) - 1;

	// Get the top right.
	m_topRight.m_x = (m_gridWidth - k_edgeCheck) - 1;
	m_topRight.m_y = k_edgeCheck;

	// Get the bottom right.
	m_bottomRight.m_x = (m_gridWidth - k_edgeCheck) - 1;
	m_bottomRight.m_y = (m_gridHeight - k_edgeCheck) - 1;
}

bool BlockManager::IsInRange(const Coordinate& point)
{
	// Check if it's in range, begin with the x coordinate or the m_y of the point. If it's greater than the width, it's not in range.
	if (point.m_x >= m_gridWidth)
	{
		return false;
	}
	
	// Now check the y coordinate or the m_x of the point. If it's greater than the height, it's not in range.
	else if (point.m_y >= m_gridHeight)
	{
		return false;
	}

	return true;
}

bool BlockManager::InBoundsOfInnerGrid(const Coordinate& point)
{
	if (point.m_x > m_topRight.m_x)
	{
		return false;
	}

	else if (point.m_y > m_bottomRight.m_y)
	{
		return false;
	}

	return true;
}

void BlockManager::CanPaintWalls(const Coordinate& point)
{
	// If boolean is true, we can paint.
	if (m_canPaint)
	{
		if (!IsInRange(point))
		{
			std::cout << "\n";
		}

		m_pGameUpdatesMediator->PlaceWall(point.m_y, point.m_x);
	}
}

bool BlockManager::YCheck(const Coordinate & startingPos, const Coordinate & diagPos)
{
	// Save the starting position in our own coordinate.
	Coordinate start = startingPos;

	// Keep running until we get to the diagonal value.
	while (start.m_y < diagPos.m_y)
	{
		// Increment down.
		++start.m_y;

		if (!IsInRange(start))
		{
			std::cout << "\n";
		}

		// Check if it's in bounds of the INNER grid. If not, return.
		else if (!InBoundsOfInnerGrid(start))
		{
			return false;
		}

		// Check if there's a wall here.
		else if (m_pGameUpdatesMediator->IsWallHere(start.m_y, start.m_x))
		{
			// If so, find a new point.
			return false;
		}

		// Place wall if allowed.
		CanPaintWalls(start);
	}

	// Keep running until we go past the diagonal value.
	while (start.m_x < diagPos.m_x)
	{
		// Increment to the right.
		++start.m_x;

		if (!IsInRange(start))
		{
			std::cout << "\n";
		}

		// Check if it's in bounds of the INNER grid. If not, exit function.
		else if (!InBoundsOfInnerGrid(start))
		{
			return false;
		}

		// Check if there's a wall here.
		else if (m_pGameUpdatesMediator->IsWallHere(start.m_y, start.m_x))
		{
			// If so, continue, find new point from the beginning.
			return false;
		}

		// Place wall if allowed.
		CanPaintWalls(start);
	}

	return true;
}

bool BlockManager::XCheck(const Coordinate& startingPos, const Coordinate& diagPos)
{
	// Save the starting position in our own coordinate.
	Coordinate start = startingPos;

	// Keep running until we go past the diagonal value.
	while (start.m_x < diagPos.m_x)
	{
		// Increment to the right.
		++start.m_x;

		if (!IsInRange(start))
		{
			std::cout << "\n";
		}

		// Check if it's in bounds of the INNER grid. If not, exit function.
		else if (!InBoundsOfInnerGrid(start))
		{
			return false;
		}

		// Check if there's a wall here.
		else if (m_pGameUpdatesMediator->IsWallHere(start.m_y, start.m_x))
		{
			// If so, continue, find new point from the beginning.
			return false;
		}

		// Place wall if allowed.
		CanPaintWalls(start);
	}

	/* We CANNOT just call YCheck for this and pass it arguments and the same wiht calling XCheck from Y check because we'll create a loop that will go into a nullptr memory
	crash. So to make it work, we just copy the YCheck code down here to check the edges around the square we're building. */
	while (start.m_y < diagPos.m_y)
	{
		// Increment down.
		++start.m_y;

		if (!IsInRange(start))
		{
			std::cout << "\n";
		}

		// Check if it's in bounds of the INNER grid. If not, return.
		else if (!InBoundsOfInnerGrid(start))
		{
			return false;
		}

		// Check if there's a wall here.
		else if (m_pGameUpdatesMediator->IsWallHere(start.m_y, start.m_x))
		{
			// If so, find a new point.
			return false;
		}

		// Place wall if allowed.
		CanPaintWalls(start);
	}

	return true;
}

void BlockManager::FillInsideOfBlock(const Coordinate& startingPoint, Coordinate * pDiagonalPos)
{
	// Save the starting position.
	Coordinate startPos = startingPoint;

	/* Check if it's minimum size. The smallest size for a block is 3 in width and height. If we make a 3 x 3 block, all we have to do is fill in
	one point on the inside. */
	if ((startingPoint.m_x + k_edgeCheck == pDiagonalPos->m_x) && (startingPoint.m_y + k_edgeCheck == pDiagonalPos->m_y))
	{
		// Just increment the coordinate of start by 1 on x and y.
		startPos.m_x += 1;
		startPos.m_y += 1;

		// Draw to screen.
		CanPaintWalls(startPos);

		// Return because we're done.
		return;
	}

	/* Get the starting point x and the diagonal point x. Plus the starting x and y by 1. Keep going as long as the x is less than the diagonal point x. 
	
	The while loop should last as long as the starting point y is less than diagonal point y. */
	startPos.m_x += 1;
	startPos.m_y += 1;
	Coordinate begin = startPos;

	// Save the starting point too.
	m_innerStartingPoint = startPos;

	// Save these to go over them again after the main chunk of code is finished.
	m_innerStart = begin;
	m_innerDiagonal = *pDiagonalPos;

	// Decrement other diagonal variable too.
	m_innerDiagonal.m_x -= 1;
	m_innerDiagonal.m_y -= 1;

	// std::cout << "Inner start. X: " << m_innerStart.m_x << " Y: " << m_innerStart.m_y << "\n";
	// std::cout << "Inner diagonal. X: " << m_innerDiagonal.m_x << " Y: " << m_innerDiagonal.m_y << "\n";

	// Alter the diagonal to fit the proper position it needs to stop at.
	pDiagonalPos->m_x -= 1;
	pDiagonalPos->m_y -= 1;

	// Begin filling out the inside.
	while (begin.m_y <= pDiagonalPos->m_y)
	{
		if (begin.m_x >= pDiagonalPos->m_x)
		{
			m_pGameUpdatesMediator->PlaceWall(begin.m_y, begin.m_x);

			// We've reached our max for this "line", move to the next one. Must reset the coordinates x too.
			begin.m_x = startPos.m_x;

			// Set the y pos 1 lower.
			begin.m_y += 1;

			continue;
		}

		m_pGameUpdatesMediator->PlaceWall(begin.m_y, begin.m_x);

		// Increment x to go further east.
		begin.m_x += 1;
	}
}

void BlockManager::SetCanPaint()
{
	m_canPaint = !m_canPaint;
}

// O(n^2) function in Best, Average, and Worst case. 
void BlockManager::GenerateBlocks()
{
	// Decide how many blocks we want.
	int maxBlocks = k_maxBlocks;

	// Set variable for current blocks.
	int currentBlocks = 0;

	// Use a do while because we know we'll at least have 1 block.
	do {
		// Get a random point on the grid.
		m_ranCoord.m_y = (rand() % (m_bottomLeft.m_y + 1 - m_topLeft.m_y)) + m_topLeft.m_y;
		m_ranCoord.m_x = (rand() % (m_topRight.m_x + 1 - m_topLeft.m_x)) + m_topLeft.m_x;

		// If this coordinate is taken, try again. 
		if (!IsInRange(m_ranCoord))
		{
			std::cout << "\n";
		}

		// If there is a wall already here, just continue;
		else if (m_pGameUpdatesMediator->IsWallHere(m_ranCoord.m_y, m_ranCoord.m_x))
		{
			continue;
		}

		// Place the wall at these coordinates.
		m_pGameUpdatesMediator->PlaceWall(m_ranCoord.m_y, m_ranCoord.m_x);

		// Calculate the diagonal coordinate so we can begin building the actual block.
		Coordinate diag;

		// Assign the proper points by simply adding a value to the x and y.
		diag.m_y = m_ranCoord.m_y + (k_edgeCheck + 1); 
		diag.m_x = m_ranCoord.m_x + (k_edgeCheck + 1);

		// We'll have to calculate the point that's n amount diagonally to our current point. IF that point is still within bounds, we can build here.
		if (!IsInRange(diag))
		{
			m_pGameUpdatesMediator->ResetWallCoordinate(m_ranCoord.m_y, m_ranCoord.m_x);

			// It's not in range, continue the loop.
			continue;
		}

		// Save coordinates to use below. Save the random coordinate and diagonal.
		Coordinate start = m_ranCoord;
		Coordinate moveToDiag = diag;

		// Check along the x axis if we're still in range of the INNER grid, if not, continue and start with another point.
		if (!XCheck(start, moveToDiag))
		{
			m_pGameUpdatesMediator->ResetWallCoordinate(m_ranCoord.m_y, m_ranCoord.m_x);
			continue;
		}

		// Check along the y axis if we're still in range of the INNER grid, if not, continue and start with another point.
		if (!YCheck(start, moveToDiag))
		{
			m_pGameUpdatesMediator->ResetWallCoordinate(m_ranCoord.m_y, m_ranCoord.m_x);
			continue;
		}

		// std::cout << "Starting point. X: " << m_ranCoord.m_x << " Y: " << m_ranCoord.m_y << "\n";

		// Flip the boolean value to true, now we can revisit the same positions in the algorithm from X/YCheck and start painting the board.
		SetCanPaint();

		// Call the functions again to paint the block.
		XCheck(start, moveToDiag);
		YCheck(start, moveToDiag);

		// Paint the inside of the block now. Handles the small blocks which are in minimum 3x3 and bigger blocks that are slightly more complex to fill.
		FillInsideOfBlock(start, &moveToDiag);

		// Reset boolean because we've drawn the block already, make sure we can't immediately draw once the loop goes around again.
		SetCanPaint();

		// Increment current blocks to continue algorithm.
		++currentBlocks;

		// Pop the coords vector if not empty.
		/*m_coords.erase(m_coords.begin());*/

		while (m_innerStart.m_y <= m_innerDiagonal.m_y)
		{
			if (m_innerStart.m_x >= m_innerDiagonal.m_x)
			{
				m_pGameUpdatesMediator->PlaceWall(m_innerStart.m_y, m_innerStart.m_x);

				// We've reached our max for this "line", move to the next one. Must reset the coordinates x too.
				m_innerStart.m_x = m_innerStartingPoint.m_x;

				// Set the y pos 1 lower.
				m_innerStart.m_y += 1;

				continue;
			}

			m_pGameUpdatesMediator->PlaceWall(m_innerStart.m_y, m_innerStart.m_x);

			m_innerStart.m_x += 1;
		}

		// std::cout << "\n";

	} while (currentBlocks != maxBlocks);
}

void BlockManager::CreateNewBlocks(const int& gridWidth, const int& gridHeight)
{
	// Set new width and height.
	m_gridWidth = gridWidth;
	m_gridHeight = gridHeight;

	// Assign the new coordinates.
	AssignCoordinates();

	// Create x amount of blocks within the range of the points created.
	GenerateBlocks();
}