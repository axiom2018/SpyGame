#pragma once

/* Reasoning for this class:

This class will literally switch the char of the enemy depending on which direction they are going. If left, the char will be <, if right? It will be >. Simple idea.


																				Class member variables:

1) Reasoning for k_arrSize:

There will be a constant size array of size 4. It'll hold all the keys for the enemy, <, >, ^, and v. We'll save them here and use it for directional control.


2) Reasoning for m_directionalChars:

The array of the chars depending on the direction of the enemy.


3) Reasoning for m_currentChar:

The char we'll return to draw depending on the direction.


4) Reasoning for m_pX & m_pY:

Hold the x and y position of the enemy using the system, so when it moves, we know which char to return to draw.


5) Reasoning for m_currentX & m_currentY:

These will hold the players "old" positions, since we have the pointers to the x and y, this will hold the position before it changes. So we can know which 
direction they went, and therefore which character to return.


																				Class functions:

1) Reasoning for constructor:

Initialize the array properly.


2) Reasoning for Update:

Update the directional system.


3) Reasoning for UpdateDirection:

Choose a different direction at random.


4) Reasoning for GetChar:

Return the char to assist the line of sight so it can adjust it's own positioning.


*/

class DirectionalSystem
{
private:
	static const int k_arrSize = 4;
	char m_directionalChars[k_arrSize];
	char * m_pCurrentChar;
	int * m_pX;
	int * m_pY;
	int m_currentX;
	int m_currentY;
public:
	DirectionalSystem(int * pX, int * pY);
	char Update();
	void UpdateDirection();
	void UpdateCurrentXAndY();
	char * GetChar() const;
	~DirectionalSystem();
};

