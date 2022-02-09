#include "menu.h"

int Menu::main_menu(Board& myBoard)
{
	//get choice from user
	bool isValid = false;
	char ch_userChoice = DEFAULT;
	int user_choice = DEFAULT;

	while (!isValid || user_choice == INSTRUCTION) {

		print_main_menu();

		cin >> ch_userChoice;

		user_choice = int(ch_userChoice - '0');
		isValid = check_input_user_choice_menu(user_choice);

		if (isValid && user_choice == INSTRUCTION)
		{
			clearScreen();
			print_instructions();
			back_to_main_menu();
		}

		clearScreen();

		if (!isValid)
			print_invalid();
	}

	if (user_choice == EXIT)
		return EXIT_GAME;
	
	if (user_choice == PLAY_COLOR)
		myBoard.set_colors(true);
	else
		myBoard.set_colors(false);

	return CONTINUE_PLAY;
	
}
void Menu::back_to_main_menu() {
	char key = _getch();
}
bool Menu::check_input_user_choice_menu(const int& userChoice)const {
	return (userChoice == PLAY_NO_COLORS || userChoice == PLAY_COLOR || userChoice == INSTRUCTION || userChoice == EXIT);
}
void Menu::print_instructions() const {

	cout << "Instructions Pacman" << endl << endl;
	cout << "Goal - Guide Pacman around the maze and eat all the little white dots whilst avoiding those nasty ghosts." << endl;
	cout << "Bread crumbs are scattered on the game board which adds a point to your score when eaten." << endl << endl;
	cout << "Controls" << endl;
	cout << "left - a or A" << endl;
	cout << "right - d or D" << endl;
	cout << "up - w or W" << endl;
	cout << "down - x or x" << endl;
	cout << "stay - s or S" << endl;

	cout << "ESC : Pause / unpause game" << endl << endl << endl;

	cout << "Press any key to back to menu" << endl;
}
void Menu::print_menu()const {

	cout << "Please press the relevant number" << endl;

	cout << "(1) Start a new game" << endl;
	cout << "(2) Start a new game - with colors" << endl;

	cout << "(8) Show instructions and keys" << endl;
	cout << "(9) EXIT" << endl;
}
void Menu::print_difficulty_menu() {
	cout << "Please press the relevant number" << endl;

	cout << "(1) for BEST player" << endl;
	cout << "(2) for GOOD player" << endl;
	cout << "(3) for NOVICE player" << endl;
}
void Menu::print_ESC_massage(const int& row_log_size)const
{

	gotoxy(0, row_log_size + 1);
	cout << "*****************************************" << endl;
	cout << "Game paused, press ESC again to continue" << endl;
	cout << "*****************************************" << endl;

}
void Menu::delete_ESC_massage(const int& row_log_size) const
{
	gotoxy(0, row_log_size + 1);
	cout << "                                          " << endl;
	cout << "                                          " << endl;
	cout << "                                          " << endl;

}
void Menu::print_game_over(const int& status,const int&sum_screen_left) {

	clearScreen();

	if (status == SUCCEEDED)
	{
		if (sum_screen_left == EMPTY)
		{
			cout << "CONGRATULATIONS!! YOU WON THE GAME!! YOU ARE AMAZINGGGG" <<
				endl << "Preass any key to back to main menu" << endl;
		}
		else
		{
			cout << "!!! You ate all breadcrumbs!!!" << endl;
			cout << "press any key to move to the next screen" << endl;
		}
	}

	else //lose game..
		cout << "GAME - OVER" << endl << endl
		<< "Press any key to back to menu" << endl;
}
void Menu::print_choose_screen() {

	cout << "If you want a specific screen, please enter its full name." << endl
		<< endl << " If you want all screens, press 1 " << endl;

}
void Menu::print_main_menu()const {

	cout << "Please press the relevant number" << endl;

	cout << "(1) Start a new game" << endl;
	cout << "(2) Start a new game - with colors" << endl;

	cout << "(8) Show instructions and keys" << endl;
	cout << "(9) EXIT" << endl;
}
void Menu:: print_invaild_file(const int&object)
{
	switch (object)
	{
	case PACMAN:
		cout << "There are more than 1 pacman";
		break;
	case GHOST:
		cout << "There are more than 4 ghosts";
		break;
	}

	cout << " !! invalid screen !!" << endl << endl << "Press any key to continue.." << endl;

	char key = _getch();
	clearScreen();
}
int Menu::choose_Difficulty() {

	bool isValid = false;
	char ch_userChoice = DEFAULT;
	int user_choice_smart_level = DEFAULT;

	while (!isValid) {

		print_difficulty_menu();
		cin >> ch_userChoice;

		user_choice_smart_level = int(ch_userChoice - '0');

		isValid = check_input_user_choice_difficulty(user_choice_smart_level);

		clearScreen();

		if (!isValid)
			print_invalid();
	}

	return user_choice_smart_level;
}
int Menu::choose_settings(int& difficulty, Board& myBoard)
{
	if (main_menu(myBoard) == EXIT_GAME)
		return EXIT_GAME;

	if (choose_screen(myBoard) == EXIT_GAME)
		return EXIT_GAME;

	difficulty = choose_Difficulty();

	return CONTINUE_PLAY;
}
bool Menu::check_input_user_choice_difficulty(const int& userChoice)const {
	return (userChoice == 1 || userChoice == 2 || userChoice == 3);
}
void Menu::print_no_files_error(const int& user_choice, const string& file_name)
{
	if (user_choice == ONE_SCREEN)
		cout << "There is no file match to " << file_name << endl << endl;
	else
		cout << "There are no screen files at the working directory.." << endl;
}
int Menu::choose_screen(Board& myBoard) {

	string screen_file_name;
	int user_choice = get_screen_option_from_user(screen_file_name);

	if (user_choice == EXIT_GAME)
		return EXIT_GAME;

	clearScreen();

	//get screens name in sorted way 
	get_screen_names_from_file(myBoard, user_choice, screen_file_name);

	if (myBoard.get_screen_file_size() == 0)
	{
		print_no_files_error(user_choice, screen_file_name);
		return EXIT_GAME;
	}

	return VALID;
}
int Menu::check_valid_name(const string& name) {
	if (name._Starts_with("pacman"))
		return VALID;
	return NOT_VALID;
}
int Menu::get_screen_option_from_user(string& file_name) {

	string user_choice;
	int next_step;

	print_choose_screen();

	cin >> user_choice;

	if (user_choice.compare("1") == 0)
	{
		next_step = ALL_SCREENS;
	}

	else
		if (check_valid_name(user_choice) == VALID)
		{
			file_name = user_choice;
			next_step = ONE_SCREEN;
		}
		else
		{
			print_no_files_error(ONE_SCREEN, user_choice);
			next_step = EXIT_GAME;
		}

	return next_step;
}
void Menu::get_screen_names_from_file(Board& myBoard,int user_choice, const string& file_name)
{
	string path = ".";

	for (const auto& entry : fs::directory_iterator(path))
	{
		if (user_choice == ONE_SCREEN) {
			if (entry.path().filename().string() == file_name)
			{
				myBoard.set_screen_file(entry.path().filename().string());
				return;
			}
		}

		else if (entry.path().filename().extension().string() == ".screen") 
		{
			myBoard.set_screen_file(entry.path().filename().string());
		}
	}
}
