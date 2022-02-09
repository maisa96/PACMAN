#pragma once
#include"ghost.h"

class smart_Ghost : public Ghost
{
private:
  
public:
    int move(Board& myBoard)override { return smart_move(myBoard); };
protected:


};
