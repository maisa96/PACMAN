#pragma once
#include <conio.h>
#include "board.h"

enum e_options { DEFAULT = 0, PLAY_NO_COLORS = 1, PLAY_COLOR = 2, INSTRUCTION = 8 , EXIT=9};

class Menu
{
private:

public:
	enum e_play { GAME_OVER = 0, CONTINUE_PLAY };

	bool check_input_user_choice_menu(const int& userChoice)const;
	void back_to_main_menu();
	int main_menu(Board& myBoard);
	bool check_input_user_choice_difficulty(const int& userChoice)const;
	int choose_settings(int& difficulty, Board& myBoard);
	int choose_Difficulty();


	void print_difficulty_menu();
	void print_welcome() const { cout << "Hello! Welcome to PACMAN :)" << endl << endl; };
	void print_menu() const;
	void print_goodbye() const { cout << "THANK YOU! BYE..." << endl << endl; };
	void print_instructions() const;
	void print_ESC_massage(const int& row_log_size)const;
	void print_game_over(const int& status, const int& sum_screen_left);
	void print_choose_screen();
	void print_no_files_error(const int& user_choice, const string& file_name);
	void print_main_menu()const;
	void delete_ESC_massage(const int& row_log_size) const;
	void clearScreen() { system("cls"); };
	void print_invalid()const { cout << "Invalid input! try again..." << endl << endl; };
	int choose_screen(Board& myBoard);
	int check_valid_name(const string& name);
	int get_screen_option_from_user(string& file_name);
	void get_screen_names_from_file(Board& myBoard,int user_choice, const string& file_name);
	void print_invaild_file(const int& object);


};