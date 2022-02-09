#pragma once
#include "gameObject.h"
#include <conio.h>

const int MAX_LIVES = 3;
enum e_status { LOST = -5, WON, STILL_ALIVE };

class Pacman:public GameObject
{
private:
	
	int status = STILL_ALIVE;
	int score = EMPTY;
	int lives = LIVES;
	int sum_breadcrumbs_to_eat = EMPTY;
public:
	Pacman() : GameObject(YELLOW) { set_form(); };

	//getters
	int get_score()const { return score; };
	int get_status()const { return status; };
	int get_lives()const { return lives; };
	int get_sum_breadcrumbs_to_eat()const { return sum_breadcrumbs_to_eat; };

	//setters
	void set_lives(int _lives = -1);
	void set_status(const int& _status) { status = _status; };
	void set_score(int _score = 1) { score += _score; };
	void set_form()override { form = '@'; };
	void set_sum_breadcrumbs_to_eat(int num = -1) { sum_breadcrumbs_to_eat += num; };

	//init
	void init_pacman(const Board& myBoard);
	void init_score() { score = EMPTY; };
	void init_sum_breadcrumbs_to_eat() { sum_breadcrumbs_to_eat = EMPTY; };
	//move
	int move(Board& myBoard)override;
	bool check_input_direction(const char& direction)const;
	void user_pick_direction();
	int check_info_next_step_and_update_x_y(Board& myBoard, int& x, int& y)override;
};
