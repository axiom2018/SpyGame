#pragma once
#include "Colleague.h"

/* Reasoning for this class: 

For the player functionality.


																				Class member variables:

1) Reasoning for k_char:

The players symbol.


2) Reasoning for m_pControlsInvoker:

This is the control system for the player to use to move around.


3) Reasoning for m_x & m_y:

Position for the player.


4) Reasoning for m_gridWidth & m_gridHeight:

Save the dimensions so we can detect if movement is okay to proceed.


																				Class functions:

1) Reasoning for constructor:

Initialize class data.


2) Reasoning for MoveUp, MoveDown, MoveLeft & MoveRight:

Directional controls to move the player.


3) Reasoning for GetInput:

Call controls invoker for proper input. Depending on the key pressed, return a value to determine if we want to quit the game.


4) Reasoning for Draw:

Display the player.


5) Reasoning for ResetPosition:

When a new grid loads, we'll need this ability to place player back to default position.


6) Reasoning for ReturnRequestedCoordinates:

For the enemy mediator system to update the enemies with the player coordinates.


*/

class Player : public Colleague
{
private:
	static const char k_char = '$';
	class ControlsInvoker * m_pControlsInvoker;
	int m_x;
	int m_y;
	int m_gridWidth;
	int m_gridHeight;
public:
	Player(class GameUpdatesMediator * pGameUpdatesMediator);
	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
	bool GetInput() const;
	bool Draw(const int& x, const int& y);
	void ResetPosition();
	virtual std::pair<int, int> ReturnRequestedCoordinates() override;
	~Player();
};

