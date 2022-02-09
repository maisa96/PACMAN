#pragma once
#include "ghost.h"

enum LevelSmart {NOVICE = 0, BEST};
const int NOVICE_MAX_STEPS = 5;

class goodGhost : public Ghost
{
private:
	int status = NOVICE;

public:
	//setters
	void set_status() {status = (status + 1) % 2; };

	//getters
	int get_status()const { return status; };

	//move
	int move(Board& myBoard)override;

	//init
	void init_steps() { steps = NOVICE_MAX_STEPS; };


};
