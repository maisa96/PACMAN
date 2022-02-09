#pragma once
#include "board.h"
#include <iostream>
#include <conio.h>
#include "pacman.h"
#include "ghost.h"
#include "fruit.h"
#include "noviceGhost.h"
#include "goodGhost.h"
#include "smartGhost.h"
#include"menu.h"

class Game {

private:
	Menu menu;
	Board myBoard;
	Pacman myPacman;
	Ghost* arrGhost[MAX_GHOST];
	Fruit gamesFruit;
	int numOfGhosts;
	int smartLevel;
	
	enum e_smart_ghost { SMART = 1, GOOD, NOVICE};
public:

	Game();
	void waitingForSecondESC();

	//setters
	void set_start_data();
	void setNumOfGhosts(const int& num) { numOfGhosts = num; };
	void set_leve_smart(const int& new_level) { smartLevel = new_level; };

	//getters
	int get_Num_Of_Ghosts()const { return numOfGhosts; };
	int get_smart_level()const { return smartLevel; };

	//init
	void start_game();
	void pause_game();
	void init_game();

	void create_ghost_by_user_choice_difficulty();
	void init_new_screen();
	void init_new_game();
	void delete_ghost_arr();
	
	//move
	void pacman_meet_ghost();
	void ghost_turn(bool& ghost_wait_one_turn);
	void pacman_turn();
	void fruit_turn();

	~Game(){ cout << "THANK YOU! GOODBYE..." << endl << endl; };
};