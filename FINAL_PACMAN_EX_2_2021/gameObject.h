#pragma once
#include <iostream>
#include <Windows.h>
#include  "board.h"
#include  "position.h"

const int DIRECTIONS = 4;
const int MAX_STEPS = 20;

class GameObject 
{
private:
	
protected:
	Position position;
	char direction = STAY;
	int color;
	char form;
public:
	GameObject(const int& new_color) { color = new_color; };

	//setters
	void set_position(const int& _x, const int& _y) { position.set_position(_x, _y); };
	virtual void set_direction(const char& _direc) { direction = _direc; };
	virtual void set_form() = 0;

	//getters
	char get_direction()const { return direction; };
	int get_color()const { return color; };
	char get_form()const { return form; };
	Position get_position ()const { return position; };

	//init
	virtual void init_object(const int& pos_x, const int& pos_y);

	//move
	char rand_direction();
	int create_random_x_value(int row) { return (rand() % row); };
	int create_random_y_value(int col) { return (rand() % col); };
	void update_position(Board& myBoard, int x, int y, int object);
	virtual int check_info_next_step_and_update_x_y(Board& myBoard,int& x, int& y);
	virtual int move(Board& myBoard) = 0;

	//print object
	void print(bool playWithColors = false);


};
