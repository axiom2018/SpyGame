#pragma once

// Base class for Command pattern.

class Command
{
public:
	virtual void Execute() = 0;
};