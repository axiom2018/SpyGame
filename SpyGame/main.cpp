#include <iostream>
#include <conio.h>
#include <ctime>
#include "vld.h"
#include "World.h"
#include "Constants.h"
#include <list>
#include <iostream>

/* Notes: This game was inspired by stealth game functionality, such as in Metal Gear Solid, The Last of Us, Bioshock Infinite, etc. I was always inspired and interested in ai 
systems, so I worked on this. It's a simple game, just avoid being seen by the enemies and escape. But it's an extremely dynamic game. The levels will change, the types of
enemies will change, and it's NEVER exactly the same as before. The enemies have good intelligence to them as well. */

int main()
{
	// Seed for random numbers.
	srand((unsigned int)time(0));

	// Update the game.
	World::GetInstance()->Update();

	// Clean memory when game is done.
	World::GetInstance()->Delete();

	return 0;
}