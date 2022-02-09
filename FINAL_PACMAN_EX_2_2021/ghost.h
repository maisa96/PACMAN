#pragma once
#include "gameObject.h"

typedef struct steps_options
{
    int sum_steps_to_pacman;
    char direction;
}STEPS_OPTIONS;

class Ghost : public GameObject {

private:
    Position pacman_position;

protected:
    int steps;
 
public:
    enum e_is_good { NOT_GOOD = 0, GOOD };

    Ghost() :GameObject(PINK) { set_form(); color = PINK; };

    //setters
    void set_steps(const int _steps = MAX_STEPS) { steps = _steps; };
    void set_form() override { form = '$'; };

    //init
    void init_direction() { set_direction(rand_direction()); };
    void init_ghost(Board& myBoard, const int& index);
    void init_values();

    //move
    void change_direction(const int& status = NOT_GOOD);

    //smart move
    int smart_move(Board& myBoard);
    void set_pacman_position(const Position& _pacman_position) { pacman_position = _pacman_position; };
    vector<STEPS_OPTIONS> make_directions_arr(Board& myBoard);

    //novice move
    int novice_move(Board& myBoard, int isGood);

    //update
    void update_steps(const int& num = -1) { steps+= num; };
};




