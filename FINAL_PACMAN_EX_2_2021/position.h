#pragma once

const char LEFT = 'a';
const char LEFT1 = 'A';
const char RIGHT = 'd';
const char RIGHT1 = 'D';
const char UP = 'W';
const char UP1 = 'w';
const char DOWN = 'X';
const char DOWN1 = 'x';
const char STAY = 's';
const char STAY1 = 'S';
const int COL = 80;
const int ROW = 25;

class Position
{
private:
	int x, y;
public:
	Position(const int _x = 0, const int _y = 0) { x = _x;	y = _y; };
	void set_position(const int& _x, const int& _y) { x = _x;	y = _y; };
	int get_x_position() const { return x; };
	int get_y_position() const { return y; };
};