#include "gameObject.h"

void GameObject::init_object(const int& pos_x, const int& pos_y) {
	set_direction(STAY);
	set_position(pos_x,pos_y);
}
char GameObject::rand_direction() {

	int num = rand() % DIRECTIONS;
	char direction = STAY;

	switch (num)
	{
	case 0:
		direction = LEFT;
		break;
	case 1:
		direction = RIGHT;
		break;
	case 2:
		direction = UP;
		break;
	case 3:
		direction = DOWN;
		break;
	}
	return direction;
}
int GameObject::check_info_next_step_and_update_x_y(Board& myBoard, int& x, int& y)
{
	 x = position.get_x_position();
	 y = position.get_y_position();

	switch (direction)
	{
	case UP:
	case UP1:
		x--;
		break;
	case DOWN:
	case DOWN1:
		x++;
		break;
	case LEFT:
	case LEFT1:
		y--;
		break;
	case RIGHT:
	case RIGHT1:
		y++;
		break;

	}

	return myBoard.get_object(x, y);
}
void GameObject::update_position(Board& myBoard, int x, int y,int object)
{
	myBoard.delete_object_from_board(position);
	set_position(x, y);
	myBoard.update_smart_board_object(x, y, object);
	print(myBoard.get_color());
}
void GameObject::print(bool playWithColors)
{
	gotoxy(position.get_y_position(),position.get_x_position());
	HANDLE hConsole = 0;
	if (playWithColors)
	{ 
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, color);
	}
	std::cout << form;

	if (playWithColors)
		SetConsoleTextAttribute(hConsole, WHITE);
}


