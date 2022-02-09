#include "game.h"
#include "menu.h"

Game::Game() {

	// for random function
	srand(time(NULL));
	menu.print_welcome();

	bool keepPlaying = true;

	while (keepPlaying)
	{
		if ( menu.choose_settings(smartLevel,myBoard)== EXIT_GAME) {
			keepPlaying = false;
			continue;
		}
		start_game();
	}

}
void Game::ghost_turn(bool& ghost_wait_one_turn)
{
	if (ghost_wait_one_turn)
		ghost_wait_one_turn = false;

	else
	{
		for (int i = 0; i < numOfGhosts; i++)
		{
			if (smart_Ghost* ghostP = dynamic_cast<smart_Ghost*>(arrGhost[i]))
			{
				ghostP->set_pacman_position(myPacman.get_position());
			}
			else if (goodGhost* ghostP = dynamic_cast<goodGhost*>(arrGhost[i]))
			{
				if(ghostP->get_status() == SMART)
					ghostP->set_pacman_position(myPacman.get_position());
			}

			int object_in_arr = arrGhost[i]->move(myBoard);

			switch (object_in_arr)
			{
			case PACMAN:
				pacman_meet_ghost();
				if (myPacman.get_status() == LOST)
					return;
				myPacman.user_pick_direction();
				break;

			case FRUIT:
				gamesFruit.disappear(myBoard);
				break;
			}
		}

		ghost_wait_one_turn = true;

	}
}
void Game::start_game() {

	int num_of_game = 0, value_returned, sum_screens =  myBoard.get_screen_file_size();
	bool gameOver = false;
	char key;

	init_new_game();

	while (num_of_game < sum_screens && !gameOver)
	{
		if (num_of_game != 0)
			init_new_screen();

		value_returned = myBoard.read_screen_map_from_file(numOfGhosts);
		
		if (value_returned!= SUCCEEDED)
		{
			menu.print_invaild_file(value_returned);
			return;
		}

		bool ghost_wait_one_turn = false;

		init_game();

		myPacman.user_pick_direction();

		while (!gameOver) {

			while (!_kbhit() && !gameOver) {
				ghost_turn(ghost_wait_one_turn);
				if (myPacman.get_status() == LOST)
				{
					gameOver = true;
					continue;
				}
				fruit_turn();
				pacman_turn();
				if (myPacman.get_status() != STILL_ALIVE)
				{
					gameOver = true;
					continue;
				}
				Sleep(100);
			}

			if (gameOver)
				continue;

			key = _getch();

			switch (key)
			{
			case ESC:
				pause_game();
				break;
			default:
				if (myPacman.check_input_direction(key))
					myPacman.set_direction(key);
				break;
			}
		}

		if (myPacman.get_status() == WON)
		{
			num_of_game++;
			menu.print_game_over(true,sum_screens-num_of_game);
			gameOver = false;
		}
		else
		{
			menu.print_game_over(false, sum_screens - num_of_game);
			myPacman.init_sum_breadcrumbs_to_eat();
		}

		key = _getch();

		menu.clearScreen();
	}
	delete_ghost_arr();
}
void Game::waitingForSecondESC() {
	while (_getch() != ESC) {
		continue;
	}
}
void Game::pause_game() {
	int row_log_size = myBoard.get_row_log_size();
	menu.print_ESC_massage(row_log_size);
	waitingForSecondESC();
	menu.delete_ESC_massage(row_log_size);
}
void Game::set_start_data() {

	//delete pacman and init 
	myPacman.update_position(myBoard,myBoard.get_x_first_pos_pac(),myBoard.get_y_first_pos_pac(),PACMAN);

	////////delete ghosts from board and init
	for (int i = 0; i < numOfGhosts; i++) 
	{
		arrGhost[i]->update_position(myBoard, myBoard.get_x_first_pos_ghost(i), myBoard.get_y_first_pos_ghost(i),GHOST);
		arrGhost[i]->init_values();
	}
}
void Game::init_game()
{
	//init pacman
	myPacman.set_status(STILL_ALIVE);
	myPacman.set_position(myBoard.get_x_first_pos_pac(), myBoard.get_y_first_pos_pac());

	//////init ghosts and print
	for (int i = 0; i < numOfGhosts; i++)
	{
		arrGhost[i]->init_ghost(myBoard, i);
		if (goodGhost* ghostP = dynamic_cast<goodGhost*>(arrGhost[i]))
			ghostP->init_steps();
		
	}
	
	//////init fruit 
	gamesFruit.init(myBoard);

	//init breadcrunbs
	myPacman.set_sum_breadcrumbs_to_eat(myBoard.count_sum_breadcrumbs_in_screen());

	//print
	myBoard.print_map_to_screen();
	gotoxy(myBoard.get_y_first_pos_menu(), myBoard.get_x_first_pos_menu());
	myBoard._print_score(myPacman.get_lives(), myPacman.get_score());
	gamesFruit.print(myBoard.get_color());
}
void Game::pacman_meet_ghost() 
{
	myPacman.set_lives();
	if (myPacman.get_status() == LOST)
		return;
	myBoard._print_score(myPacman.get_lives(), myPacman.get_score());
	set_start_data();
}
void Game::fruit_turn() 
{
	if (gamesFruit.getNumOfTurns() > 0)
		gamesFruit.setNumOfTurns();
	
	else
	{
		gamesFruit.initNumOfTurns();

		int object = gamesFruit.move(myBoard);

		if(object == PACMAN)
		{
			myPacman.set_score(gamesFruit.get_worth());
			myBoard._print_score(myPacman.get_lives(), myPacman.get_score());
			gamesFruit.disappear(myBoard);
		}
	}
}
void Game::pacman_turn()
{
	int object = myPacman.move(myBoard);

	int new_X_pos = gamesFruit.get_position().get_x_position();
	int new_Y_pos = gamesFruit.get_position().get_y_position();
	
	switch (object)
	{
		
	case FRUIT:
		
		myPacman.set_score(gamesFruit.get_worth());

		if (myBoard.get_breadcrumb(new_X_pos, new_Y_pos) == true) 
		{
			myBoard.set_breadcrumb(new_X_pos, new_Y_pos);
			myPacman.set_score();
			myPacman.set_sum_breadcrumbs_to_eat();

			if (myPacman.get_sum_breadcrumbs_to_eat() == 0)
				myPacman.set_status(WON);
		}

		gamesFruit.disappear(myBoard);

		myPacman.update_position(myBoard, new_X_pos, new_Y_pos, PACMAN);
		myBoard._print_score(myPacman.get_lives(), myPacman.get_score());
		break;
	case GHOST:

		pacman_meet_ghost();
		if (myPacman.get_status() == LOST)
			return;
		myPacman.user_pick_direction();
		break;

	}

}






void Game::create_ghost_by_user_choice_difficulty()
{
	for (int i = 0; i < MAX_GHOST; i++)
	{
		switch (smartLevel)
		{
		case SMART:
				arrGhost[i] = new smart_Ghost;
			break;
		case GOOD:
				arrGhost[i] = new goodGhost;
			break;
		case NOVICE:
				arrGhost[i] = new noviceGhost;
			break;
		}
	}
}
void Game::init_new_screen()
{
	myBoard.set_row_log_size(ROW);
	myBoard.set_col_log_size(COL);
	myBoard.init_first_positions(numOfGhosts);
	myBoard.init_smart_board();
	numOfGhosts = 0;
}
void Game::init_new_game()
{
	create_ghost_by_user_choice_difficulty();
	myPacman.init_pacman(myBoard);
	myBoard.init_first_positions(numOfGhosts);
	numOfGhosts = 0;
	myBoard.init_smart_board();
}
void Game::delete_ghost_arr()
{
	for (int i = 0; i < MAX_GHOST; i++)
		delete arrGhost[i];
	
}
