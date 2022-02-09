#pragma once
#include "position.h"
#include <Windows.h>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>
#include <set>

namespace fs = std::filesystem;
using std::cin;
using std::cout;
using std::string;
using std::endl;
using std::vector;
using std::set;
using std::ifstream;

const int ESC = 27;
const int MAX_GHOST = 4;

void gotoxy(short x, short y);

enum e_board_object { EMPTY = 0, TAKEN, WALL, GHOST, PACMAN, TUNNEL, FRUIT, PROHIBIT_FRUIT_BIRTH, SCORE_BOARD };
enum e_colors { BLUE = 9, GREEN = 10, RED = 12, PINK = 13, YELLOW = 14, WHITE = 15 };
enum e_success { FAILED = 0, SUCCEEDED };

typedef struct board {
	int object;
	bool breadcrumb;
}SMART_BOARD; 

typedef struct positions {
	Position menuPosition;
	Position pac_position;
	Position ghost_position[4];
}First_positions;

const int EXIT_GAME = 10;
const int VALID = 1;
const int NOT_VALID = -1;
const int ONE_SCREEN = 1;
const int ALL_SCREENS = 2;
const int FIRST_LINE = 0;
const int LIVES = 3;
const int HIGHT_MENU = 3;
const int WIDTH_MENU = 20;

class Board {

private:
	bool playWithColors = false;
	int col_log_size = COL, row_log_size = ROW;
	First_positions first_position_objects;
	SMART_BOARD smartBoard[ROW][COL] = { {EMPTY,false} };
	set <string> screen_files_list;

public:	
	//setters
	void set_screen_file(const string& new_string) { screen_files_list.insert(new_string); };
	void set_colors(const bool& playColors) { playWithColors = playColors; };
	void set_breadcrumb(const int& x, const int& y , const bool& bread_crumb = false) { smartBoard[x][y].breadcrumb = bread_crumb; };
	void set_col_log_size(int _col) { col_log_size = _col; };
	void set_row_log_size(int _row) { col_log_size = _row; };
	void set_first_pos_ghost(const Position& pos, const int& index) { first_position_objects.ghost_position[index].set_position(pos.get_x_position(), pos.get_y_position()); };
	void set_first_pos_pac(const Position& pos) { first_position_objects.pac_position.set_position(pos.get_x_position(), pos.get_y_position()); };
	void set_first_pos_menu(const Position& pos) { first_position_objects.menuPosition.set_position(pos.get_x_position(), pos.get_y_position()); };

	//getters
	int get_object(const int& x, const int& y) { return smartBoard[x][y].object; };
	bool get_color() { return playWithColors; };
	bool get_breadcrumb(const int x, const int y)const { return smartBoard[x][y].breadcrumb; };
	int get_screen_file_size()const { return screen_files_list.size(); };
	int get_x_first_pos_pac()const { return first_position_objects.pac_position.get_x_position(); };
	int get_y_first_pos_pac()const { return first_position_objects.pac_position.get_y_position(); };
	int get_x_first_pos_menu()const { return first_position_objects.menuPosition.get_x_position(); };
	int get_y_first_pos_menu()const { return first_position_objects.menuPosition.get_y_position(); };
	int get_y_first_pos_ghost(const int& index)const { return first_position_objects.ghost_position[index].get_y_position(); };
	int get_x_first_pos_ghost(const int& index)const { return first_position_objects.ghost_position[index].get_x_position(); };
	int get_col_log_size()const { return col_log_size; };
	int get_row_log_size()const { return row_log_size; };

	//print
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	void print_map_to_screen()const;
	void _print_score(const int& lives, const int& score)const;

	//init
	bool update_first_pos_ghost(int& num_of_ghost, int& row, int& col);
	int count_sum_breadcrumbs_in_screen();
	int read_screen_map_from_file(int& num_of_ghost);
	void update_board_with_menu(int& row, int& col);
	int read_line_from_file(ifstream& screen_file, int& row, int& num_of_ghost, int& counter_pac, int& counter_menu);
	void check_tunnels();
	void check_tunnels_up();
	void check_tunnels_side();
	void init_first_positions(const int& numOfGhost);
	void init_smart_board();
	int get_sum_screens() { return screen_files_list.size(); };

	//delete
	void delete_object_from_board(Position pos);
	void delete_from_screen(const Position& pos) const;

	//update
	void update_smart_board_object(const int& x, const int& y, const int& object);
	void init_end_line(int col, const int& row);


};