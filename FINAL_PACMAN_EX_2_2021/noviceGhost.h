#pragma once
#include "ghost.h"


class noviceGhost : public Ghost
{
private:
public:
	//move
	int move(Board& myBoard)override { return novice_move(myBoard,NOT_GOOD); };
protected:


};