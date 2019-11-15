#pragma once

/* Reasoning for class:

Manage the keyboard inputs for the player. Good pattern to use since it lets us encapsulate the objects or functions as requests allowing us to switch them out if need be.
This is commonly used in games that have multiple control systems such as ANY of the sports franchise video games.


																				Class member variables:

1) Reasoning for m_pPlayerUp/Down/Left/Right:

The directional keys for the player.


2) Reasoning for k_up/down/left/right/quit:

Buttons to press to interact with controls.

																				Class functions:

1) Reasoning for constructor:

Initialize variables.


2) Reasoning for SetUp/Down/Left/Right:

Assign each command.


3) Reasoning for ExecuteUp/Down/Left/Right:

Execute each assigned command.


4) Reasoning for GetInput:

Get the key press.


) Reasoning for destructor:

Clean memory.

*/

class ControlsInvoker
{
private:
	class Command * m_pPlayerUp;
	class Command * m_pPlayerDown;
	class Command * m_pPlayerLeft;
	class Command * m_pPlayerRight;

	static const char k_up = 'w';
	static const char k_down = 's';
	static const char k_left = 'a';
	static const char k_right = 'd';
	static const char k_quit = 'q';
public:
	ControlsInvoker(class Player * pPlayer);
	void SetUpCommand(class Command * pUpCommand);
	void SetDownCommand(class Command * pDownCommand);
	void SetLeftCommand(class Command * pLeftCommand);
	void SetRightCommand(class Command * pRightCommand);
	void ExecuteUp() const;
	void ExecuteDown() const;
	void ExecuteLeft() const;
	void ExecuteRight() const;
	bool GetInput() const;
	~ControlsInvoker();
};

