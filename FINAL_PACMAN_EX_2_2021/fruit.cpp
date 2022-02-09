#include "fruit.H"

//init
void Fruit::init(Board& myBoard) {

	int x, y, object;
	bool validPos = false;

	while (!validPos) {

		x = create_random_x_value(myBoard.get_row_log_size());
		y = create_random_y_value(myBoard.get_col_log_size());

		object = myBoard.get_object(x, y);

		if (object == EMPTY)
			validPos = true;
	}
	///////////set position and update info array////////////
	set_position(x, y);
	myBoard.update_smart_board_object(x, y, FRUIT);

	///////////////set direction/////////////////////////////
	set_direction(rand_direction());

	///////////////set num of steps/////////////////////////
	setSteps();

	//////////////set worth///////////////////////////////
	set_worth();
	//////////////set form///////////////////////////////
	set_form();
}
void Fruit::initNumOfTurns(bool isDisappear )
{
	if (isDisappear)
		numOfTurns = MAX_STEPS;
	else
		numOfTurns = FRUIT_TURNS;
};
void Fruit::set_worth() 
{ 
	worth = (rand() % WORTH_OPTIONS) + WORTH_OPTIONS;
}
//move
int Fruit::move(Board& myBoard) {

	////////check if need to disappear///////////////////
	if (steps == EMPTY)
	{
		disappear(myBoard);
		return EMPTY;
	}

	int x,y, object_in_arr = check_info_next_step_and_update_x_y(myBoard, x, y);

	while (object_in_arr == WALL || object_in_arr == TAKEN || object_in_arr == TUNNEL)
	{
		change_direction();
		object_in_arr = check_info_next_step_and_update_x_y( myBoard, x, y);
	}

	if (object_in_arr == EMPTY || object_in_arr == PROHIBIT_FRUIT_BIRTH)
	{
		update_position(myBoard, x, y,FRUIT);
		setNumOfSteps();
	}

	if(object_in_arr == GHOST)
		disappear(myBoard);
	
	return object_in_arr;
}
void Fruit::disappear(Board& myBoard)
{
	initNumOfTurns(true);
	myBoard.delete_object_from_board(position);
	init(myBoard);
}
void Fruit::change_direction()
{
	set_direction(rand_direction());
	setSteps();
}

