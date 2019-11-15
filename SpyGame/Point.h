#pragma once

/* Reasoning for this class:

Position assistance for A star. */

class Point
{
private:
	int m_x;
	int m_y;
public:
	Point(int startX = 0, int startY = 0);
	bool operator ==(const Point& o); 
	Point operator +(const Point& o);

	Point GetPoint() const;
	int GetX() const;
	int GetY() const;
	void DisplayPoint() const;
};

//{ 0, 0, 0, 0, 0, 0, 0, 0 }
//{ 0, 0, 0, 0, 0, 0, 0, 0 }
//{ 0, 0, 0, 0, 1, 1, 1, 0 }
//{ 0, 0, 1, 0, 0, 0, 1, 0 }
//{ 0, 0, 1, 0, 0, 0, 1, 0 }
//{ 0, 0, 1, 1, 1, 1, 1, 0 }
//{ 0, 0, 0, 0, 0, 0, 0, 0 }
//{ 0, 0, 0, 0, 0, 0, 0, 0 }