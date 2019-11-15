#pragma once
#include "Coordinates.h"
#include "Colleague.h"
#include <vector>

/* Reasoning for class:

Manage how the blocks or the barriers will be done in the game. O(n^2) time total.


																				Class member variables:

1) Reasoning for k_edgeCheck:

This is the space that the block will start being built from, from the edge of the grid. For example if the width is 30. The blocks edge check on the west will NOT allow
a block to be built at index 0 or 1, starting from the west.


2) Reasoning for k_maxBlocks:

Simply the amount of blocks per level.


3) Reasoning for m_gridWidth & m_gridHeight:

Need the space we're working with to make proper blocks.


4) Reasoning for m_canPaint:

Hold a boolean to know, when we're doing the main algorithm, that we can paint walls or just draw them to the grid.


5) Reasoning for topLeft/bottomLeft/topRight/bottomRight:

The way the block system works is we give the blocks a range WITHIN the actual grid. Imagine a 10 x 10 grid, and on the inside theres a 7 x 7 grid. 
That's the concept behind the coordinates and how it helps us to give the blocks a zone where they can go. We always want them to be in the general middle,
not far off on the left hand side or something.


6) Reasoning for m_innerStart/m_innerDiagonal/m_innerStartingPoint:

Assists with the process of making SURE the inner blocks are filled.


7) Reasoning for m_ranCoord:

A random coordinate to begin painting the wall.


																				Class functions:

1) Reasoning for constructor:

Set the width and height and begin creating blocks.


2) Reasoning for CreateNewBlocks:

Forms new blocks on the grid with a new width and height the World.cpp gives us.



																				Class functions (private):


1) Reasoning for AssignCoordinates:

Build the inner grid.


2) Reasoning for GenerateBlocks:

Produce n amount of blocks to display on screen.


3) Reasoning for SetCanPaint:

In order to paint the block/walls we have to be sure it's time. The first part of the algorithm is meant to check the space to see IF we're not overlapping 
or out of bounds when it comes to painting. If we're not, then we switch the boolean m_canPaint to true, and we'll be able to re-do that part of the
algorithm but draw.


4) Reasoning for FillInsideOfBlock:

When the algorithm runs, it's main job will be to align the outskirts, see if it's not overlapping, then place walls to create the block if no overlap occurs.
If that's done, then we go to the inner area of the block and fill that section up.


5) Reasoning for IsInRange:

Make sure, even though technically impossible, that the random coordinates between the inner grid don't go out of the whole grid ITSELF. For example,
if we have a 20 x 20 grid, and our INNER grid has a top left of 2,2, and top right of 17,2, and a bottom left of 2,17, and a bottom right of 17,17. 
Than our random point that occurs WITHIN this that is maybe, 8, 13 isn't out of bounds with the original width and height (20,20). With the code set up 
this is almost guaranteed not to happen, BUT if it does this is  the emergency check.


6) Reasoning for InBoundsOfInnerGrid:

This makes sure the process of the algorithm, outlining the block before we paint, makes sure the block is in a good spot as a whole.


7) Reasoning for XCheck:

Checks the outline of the block. Let's say we need to create one starting at position 5,8. And the goal is 7,10. We'll check to the right and end up at 7,8.
Then downward, and we'll end up at 7,10. That's how XCheck works.


8) Reasoning for YCheck:

Like XCheck but checks down first, THEN to the right.


9) Reasoning for CanPaintWalls:

If the boolean is true, we can paint the walls even though the main functions that call this function see if the outline is allowed. After we know we CAN 
outline, we allow the algorithm to put the walls in place to begin forming the block.


*/

class BlockManager : public Colleague
{
private:
	const int k_edgeCheck = 2;
	const int k_maxBlocks = 3;
	int m_gridWidth;
	int m_gridHeight;
	bool m_canPaint;

	Coordinate m_topLeft;
	Coordinate m_bottomLeft;
	Coordinate m_topRight;
	Coordinate m_bottomRight;
	Coordinate m_innerStart;
	Coordinate m_innerDiagonal;
	Coordinate m_innerStartingPoint;
	Coordinate m_ranCoord;

	std::vector<std::pair<int, int>> m_coords;
	int m_index;

	void CanPaintWalls(const Coordinate& point);
	bool YCheck(const Coordinate& startingPos, const Coordinate& diagPos);
	bool XCheck(const Coordinate& startingPos, const Coordinate& diagPos);
	bool InBoundsOfInnerGrid(const Coordinate& point);
	bool IsInRange(const Coordinate& point);
	void FillInsideOfBlock(const Coordinate& startingPoint, Coordinate * pDiagonalPos);
	void SetCanPaint();
	void GenerateBlocks();
	void AssignCoordinates();
public:
	BlockManager(const int& gridWidth, const int& gridHeight, class GameUpdatesMediator * pGameUpdatesMediator);
	void CreateNewBlocks(const int& gridWidth, const int& gridHeight);
};

