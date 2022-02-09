#include "pacman.h"

//init
void Pacman::init_pacman(const Board& myBoard)
{
	status = STILL_ALIVE;
	direction = STAY;
	score = 0;
	set_position(myBoard.get_x_first_pos_pac(), myBoard.get_y_first_pos_pac());
	lives = MAX_LIVES;
};
//setters
void Pacman::set_lives(int _lives) 
{
	lives+=_lives;
	if (lives == EMPTY) {
		set_status(LOST);
	}
};
//move
int Pacman::move(Board& myBoard)
{
	int x, y;
	int boardObject = check_info_next_step_and_update_x_y(myBoard, x, y);

	switch (boardObject)
	{
	case TAKEN:
	case WALL:
		set_direction(STAY);
		break;

	case PROHIBIT_FRUIT_BIRTH:
		update_position(myBoard, x, y, PACMAN);
		break;

	case EMPTY:
		if (myBoard.get_breadcrumb(x, y) == true) {
			set_score();
			set_sum_breadcrumbs_to_eat();

			if (get_sum_breadcrumbs_to_eat() == 0)
			{
				status = WON;
				return WON;
			}

			myBoard._print_score(lives, score);
			myBoard.set_breadcrumb(x, y);
		}
		update_position(myBoard, x, y, PACMAN);
		break;
	}
	return boardObject;

}
void Pacman:: user_pick_direction()
{
	char key;
	bool valid_key = false;

	while (!valid_key) {
		key = _getch();
		if (check_input_direction(key)) {
			set_direction(key);
			valid_key = true;
		}
	}	
}
bool Pacman::check_input_direction(const char& direction)const {
	return (direction == UP || direction == DOWN || direction == RIGHT || direction == LEFT ||
		direction == UP1 || direction == DOWN1 || direction == RIGHT1 ||
		direction == LEFT1 || direction == STAY || direction == STAY1);
}
int Pacman::check_info_next_step_and_update_x_y(Board& myBoard, int& x, int& y)
{
	int tunnelX = x = position.get_x_position();
	int tunnelY = y = position.get_y_position();

	switch (direction)
	{
	case UP:
	case UP1:
		x--;
		tunnelX = myBoard.get_row_log_size() - 2;
		break;
	case DOWN:
	case DOWN1:
		x++;
		tunnelX =  1;
		break;
	case LEFT:
	case LEFT1:
		y--;
		tunnelY = myBoard.get_col_log_size() - 2;
		break;
	case RIGHT:
	case RIGHT1:
		y++;
		tunnelY = 1;
		break;
	}

	int object = myBoard.get_object(x, y);

	if (object == TUNNEL)
	{
		x = tunnelX;
		y = tunnelY;

		return myBoard.get_object(x, y);
	}
	return(object);

}
