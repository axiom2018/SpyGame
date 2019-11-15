#include "Point.h"
#include <iostream>

// Initialize the start x and y in the constructor.
Point::Point(int startX, int startY)
{
	m_x = startX;
	m_y = startY;
}

bool Point::operator==(const Point & o)
{
	return o.m_x == m_x && o.m_y == m_y;
}

Point Point::operator+(const Point & o)
{
	return Point(o.m_x + m_x, o.m_y + m_y);
}

Point Point::GetPoint() const
{
	return Point(m_x, m_y);
}

int Point::GetX() const
{
	return m_x;
}

int Point::GetY() const
{
	return m_y;
}

void Point::DisplayPoint() const
{
	std::cout << "X: " << m_x << " Y: " << m_y << "\n";
}
