#include "ghost.h"

void Ghost::init_ghost(Board& myBoard, const int& index) {

	set_position(myBoard.get_x_first_pos_ghost(index), myBoard.get_y_first_pos_ghost(index));
	init_values();
	
}
void Ghost::init_values()
{
	///////////////set direction/////////////////////////////
	init_direction();

	///////////////set num of steps/////////////////////////
	set_steps(MAX_STEPS);

}
vector<STEPS_OPTIONS> Ghost::make_directions_arr(Board& myBoard)
{
	int x, y, x_dif, y_dif, num_of_steps;
	vector<STEPS_OPTIONS>arr;
	STEPS_OPTIONS tmp;

	char prev = get_direction();

	for (int i = 0; i < DIRECTIONS; i++)
	{
		switch (i)
		{
		case 0:
			set_direction(LEFT);
			break;
		case 1:
			set_direction(RIGHT);
			break;
		case 2:
			set_direction(UP);
			break;
		case 3:
			set_direction(DOWN);
			break;
		}

		int object = check_info_next_step_and_update_x_y(myBoard, x, y);

		if (object != TUNNEL || object != WALL || object != TAKEN)
		{
			x_dif = x - pacman_position.get_x_position();
			y_dif = y - pacman_position.get_y_position();
			
			num_of_steps = abs(x_dif) + abs(y_dif);

			arr.push_back({ num_of_steps,get_direction() });
		}


	}

	int sizeOfArr = arr.size();
	
	for (int i = 0; i < sizeOfArr ; i++)
	{
		for (int j = i + 1; j < sizeOfArr; j++)
		{
			if (arr[i].sum_steps_to_pacman > arr[j].sum_steps_to_pacman)
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
		}
	}

	return arr;

}
int Ghost::smart_move(Board& myBoard)
{
	char object;
	vector<STEPS_OPTIONS> arr = make_directions_arr(myBoard);
	int sizeOfArr = arr.size();

	for (int i = 0; i < sizeOfArr; i++)
	{
		int x = position.get_x_position();
		int y = position.get_y_position();

		set_direction(arr[i].direction);
		object = check_info_next_step_and_update_x_y(myBoard, x, y);

		if (object == EMPTY)
		{
			update_position(myBoard, x, y, GHOST);
			return object;
		}

		else if (object == PACMAN || object == FRUIT)
		{
			return object;
		}
	}
}
int Ghost::novice_move(Board& myBoard,int isGood)
{
	int x, y;
	int object_in_arr = check_info_next_step_and_update_x_y(myBoard, x, y);

	////////check if need to change direction///////////////////
	while (object_in_arr == WALL || object_in_arr == TAKEN || object_in_arr == TUNNEL || steps == EMPTY)
	{
		change_direction(isGood);
		object_in_arr = check_info_next_step_and_update_x_y(myBoard, x, y);
	}

	update_steps();
	update_position(myBoard, x, y, GHOST);

	return object_in_arr;
}
void Ghost::change_direction(const int& status) 
{
	init_direction(); 
	if(status == NOT_GOOD)
		set_steps();
}







