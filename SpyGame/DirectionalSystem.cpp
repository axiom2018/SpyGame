#include "DirectionalSystem.h"
#include "Constants.h"
#include <stdlib.h>
#include <iostream>

DirectionalSystem::DirectionalSystem(int * pX, int * pY)
{
	// Initialize the array with all directional characters.
	m_directionalChars[0] = k_northSymbol;
	m_directionalChars[1] = k_southSymbol;
	m_directionalChars[2] = k_westSymbol;
	m_directionalChars[3] = k_eastSymbol;

	// Allocate memory.
	m_pCurrentChar = new char;

	// Get a random one to set as current char.
	*m_pCurrentChar = m_directionalChars[0 + (rand() % 4)];

	// Set position.
	m_pX = pX;
	m_pY = pY;

	// Set current positions.
	m_currentX = *m_pX;
	m_currentY = *m_pY;
}

char DirectionalSystem::Update()
{
	// If enemy went to the left.
	if (m_currentX > *m_pX)
	{
		*m_pCurrentChar = k_westSymbol; 
	}

	// If enemy went to the right.
	else if (m_currentX < *m_pX)
	{
		*m_pCurrentChar = k_eastSymbol; 
	}

	// If enemy went up.
	else if (m_currentY > *m_pY)
	{
		*m_pCurrentChar = k_northSymbol; 
	}

	// If enemy went down.
	else if (m_currentY < *m_pY)
	{
		*m_pCurrentChar = k_southSymbol; 
	}

	// Set current positions.
	m_currentX = *m_pX;
	m_currentY = *m_pY;

	return *m_pCurrentChar;
}

void DirectionalSystem::UpdateDirection()
{
	*m_pCurrentChar = m_directionalChars[0 + (rand() % 4)];
}

void DirectionalSystem::UpdateCurrentXAndY()
{
	// Set current positions.
	m_currentX = *m_pX;
	m_currentY = *m_pY;
}

char * DirectionalSystem::GetChar() const
{
	// All I had to do was return a type "const char *" and I can return the mem address like "&m_currentChar"?
	return m_pCurrentChar;
}

DirectionalSystem::~DirectionalSystem()
{
	delete m_pCurrentChar;
	m_pCurrentChar = nullptr;
}

