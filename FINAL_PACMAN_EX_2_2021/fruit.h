#pragma once
#include "gameObject.h"
#include <time.h>

const int FRUIT_TURNS = 2;
const int WORTH_OPTIONS = 5;

class Fruit :public GameObject {
private:
	int steps = MAX_STEPS, numOfTurns = FRUIT_TURNS;
	int worth;
protected:
public:
	Fruit() : GameObject(GREEN) {};
	
	//setters
	void setNumOfSteps() { steps--; };
	void set_worth(); 
	void set_form()override { form = get_worth() + '0'; };
	void setNumOfTurns() { numOfTurns--; };
	void setSteps() { steps = MAX_STEPS; };

	//getters
	int get_worth()const { return worth; };
	int getNumOfSteps()const { return steps; };
	int getNumOfTurns()const { return numOfTurns; };

	//init
	void init(Board& myBoard);
	void initNumOfTurns(bool isDisappear = false);

	//move
	void disappear(Board& myBoard);
	int move(Board& myBoard)override;
	void change_direction();
};