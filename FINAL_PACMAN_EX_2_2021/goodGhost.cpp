#include "goodGhost.h"
int goodGhost:: move(Board& myBoard)
{
	if (steps == 0)
	{
		if (status == NOVICE)
			update_steps(MAX_STEPS);
		else //status == SMART
			update_steps(NOVICE_MAX_STEPS);

		set_status();
	}
	
	int object;

	if (status == NOVICE)
		object = novice_move(myBoard,GOOD);
	else
		object = smart_move(myBoard);
	return object;
}



