#include "board.h"

void gotoxy (short x,short y)
{
	static HANDLE hConsoleOutput = NULL;
	if (NULL == hConsoleOutput)
		hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	COORD dwCursorPosition = { x, y };
	std::cout.flush();
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}
void Board::print_map_to_screen()const {

	//for colors option
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	char object = ' ';
	int object_color = WHITE;

	for (int row = 0; row < row_log_size; row++) {
		for (int col = 0; col < col_log_size; col++) {
			switch (smartBoard[row][col].object)
			{
			case TUNNEL:
			case PROHIBIT_FRUIT_BIRTH:
			case TAKEN:
				object = ' ';
				break;
			case EMPTY:
				if (smartBoard[row][col].breadcrumb) {
					object = '.';
					object_color = WHITE;
				}
				else
					object = ' ';
				break;
			case WALL:
				object = char(4);
				object_color = BLUE;
				break;
			case GHOST:
				object = '$';
				object_color = PINK;
				break;
			case PACMAN:
				object = char(1);
				object_color = YELLOW;
				break;
			default:
				break;
			}

			if (playWithColors)
				SetConsoleTextAttribute(hConsole, object_color);
			cout << object;

			if (playWithColors)
				SetConsoleTextAttribute(hConsole, WHITE);
		}
		cout << endl;
	}

}
void Board::_print_score(const int& lives, const int& score)const
{
	int i, liveToDelete = LIVES - lives;

	gotoxy(first_position_objects.menuPosition.get_y_position(), first_position_objects.menuPosition.get_x_position());

	cout << "live: ";

	if (playWithColors)
		SetConsoleTextAttribute(hConsole, RED);

	for (i = 0; i < lives; i++)
		cout << " " << char(3) << " ";

	SetConsoleTextAttribute(hConsole, WHITE);

	for (i = 0; i < liveToDelete; i++)
		cout << "  ";

	gotoxy(first_position_objects.menuPosition.get_y_position(), first_position_objects.menuPosition.get_x_position() + 1);

	cout << "score:  " << score;
}
void Board::delete_from_screen(const Position& pos) const {

	int x = pos.get_x_position(), y = pos.get_y_position();
	gotoxy(y, x);

	if (get_breadcrumb(x, y))
		cout << ".";
	else
		cout << " ";

}
void Board::delete_object_from_board(Position pos)
{
	int x_pos = pos.get_x_position(), y_pos = pos.get_y_position();

	smartBoard[x_pos][y_pos].object = EMPTY;
	delete_from_screen(pos);
}
void Board::update_smart_board_object(const int& x, const int& y, const int& object)
{
	smartBoard[x][y].object = object;
}
int Board::read_screen_map_from_file(int& num_of_ghost)
{
	ifstream screen_file;
	
	int row = 0, counter_pac = 0, counter_menu = 0, value_returned;
	set<string>::iterator ptr_begin = screen_files_list.begin();
	
	screen_file.open(*ptr_begin, std:: ios::in);

	if (screen_file.is_open())
	{
		while (!screen_file.eof())
		{
			value_returned = read_line_from_file(screen_file, row, num_of_ghost, counter_pac, counter_menu);
		
			if(value_returned!=SUCCEEDED)
				return value_returned;
		}
		row_log_size = row;
		check_tunnels();
		screen_file.close();
		screen_files_list.erase(*ptr_begin);
		return SUCCEEDED;
	}
	else
	{
		cout << "Failure to open - " << *ptr_begin << endl;
		cout << "Press any key to go back to menu" << *ptr_begin << endl;

		return FAILED;
	}
}
int Board::read_line_from_file(ifstream& screen_file, int& row, int& num_of_ghost, int& counter_pac, int& counter_menu)
{
	int col = 0;
	string line;
	char ch = screen_file.get();

	while (col < col_log_size && ch != '\n' && !screen_file.eof())
	{
		if (smartBoard[row][col].object != TAKEN)
		{
			switch (ch)
			{
			case '%':
				smartBoard[row][col].object = PROHIBIT_FRUIT_BIRTH;
				break;
			case '@':
				if (counter_pac > 0)
					return PACMAN;
				counter_pac++;
				smartBoard[row][col].object = PACMAN;
				first_position_objects.pac_position.set_position(row, col);
				break;
			case '#':
				smartBoard[row][col].object = WALL;
				break;
			case '$':
				smartBoard[row][col].object = GHOST;
				smartBoard[row][col].breadcrumb = true;
				if (update_first_pos_ghost(num_of_ghost, row, col) == FAILED)
					return GHOST;
				break;
			case '&':
				if (counter_menu > 0)
					return SCORE_BOARD;
				
				update_board_with_menu(row, col);
				counter_menu++;
				break;
			case ' ':
				smartBoard[row][col].object = EMPTY;
				smartBoard[row][col].breadcrumb = true;
				break;
			}
		}
		col++;
		ch = screen_file.get();
	}

	if (row == FIRST_LINE)
		col_log_size = col;

	if (col < col_log_size)
		init_end_line(col, row);
	
	if (ch != '\n')
		std::getline(screen_file, line);

	if ((!screen_file.eof()) || (screen_file.eof() && col > 0))
		row++;

	return SUCCEEDED;
}
void Board:: init_end_line(int col, const int& row)
{
	for (col; col < col_log_size; col++)
	{
		if (smartBoard[row][col].object != TAKEN)
			smartBoard[row][col].object = PROHIBIT_FRUIT_BIRTH;
	}
}
void Board::update_board_with_menu(int& row, int& col) {

	first_position_objects.menuPosition.set_position(row, col);
	int menu_height_size = row + HIGHT_MENU;
	int menu_width_size = col + WIDTH_MENU;

	for (int i = row; i < menu_height_size; i++)
		for (int j = col; j < menu_width_size; j++)
		{
			smartBoard[i][j].object = TAKEN;

			smartBoard[i][j].breadcrumb = false;
		}
}
void Board::check_tunnels_up() {

	for (int i = 0; i < col_log_size; i++) {
		if (smartBoard[FIRST_LINE][i].object == EMPTY || smartBoard[FIRST_LINE][i].object == PROHIBIT_FRUIT_BIRTH) {
			if (smartBoard[row_log_size - 1][i].object == EMPTY || smartBoard[row_log_size - 1][i].object == PROHIBIT_FRUIT_BIRTH)
			{
				smartBoard[FIRST_LINE][i].object = TUNNEL;
				smartBoard[FIRST_LINE][i].breadcrumb = false;

				smartBoard[row_log_size - 1][i].object = TUNNEL;
				smartBoard[row_log_size - 1][i].breadcrumb = false;
			}
		}
	}

}
void Board::check_tunnels_side()
{
	for (int i = 0; i < row_log_size; i++) {
		if (smartBoard[i][0].object == EMPTY || smartBoard[i][0].object == PROHIBIT_FRUIT_BIRTH)
			if (smartBoard[i][col_log_size - 1].object == EMPTY || smartBoard[i][col_log_size - 1].object == PROHIBIT_FRUIT_BIRTH)
			{
				smartBoard[i][col_log_size - 1].object = TUNNEL;
				smartBoard[i][col_log_size - 1].breadcrumb = false;

				smartBoard[i][0].object = TUNNEL;
				smartBoard[i][0].breadcrumb = false;
			}
	}
}
void Board::check_tunnels()
{
	check_tunnels_up();
	check_tunnels_side();
}
bool Board::update_first_pos_ghost(int& num_of_ghost, int& row, int& col)
{
	if (num_of_ghost == MAX_GHOST)
	{
		cout << "There are more than 4 ghost - invalid screen!" << endl <<
			"Press any key to EXIT" << endl;

		return FAILED;
	}

	first_position_objects.ghost_position[num_of_ghost].set_position(row, col);
	num_of_ghost++;

	return SUCCEEDED;
}
int Board::count_sum_breadcrumbs_in_screen() {
	int counter = 0;
	for (int j = 0; j < row_log_size; j++)
		for (int i = 0; i < col_log_size; i++)
			if (smartBoard[j][i].breadcrumb)
				counter++;
	return counter;
}
void Board::init_first_positions(const int& numOfGhost) {

	set_first_pos_pac(Position());
	set_first_pos_menu(Position());
	for (int i = 0; i < numOfGhost; i++)
		set_first_pos_ghost(Position(), i);
}
void Board::init_smart_board()
{
	for(int i = 0; i< ROW; i++)
		for (int j = 0; j < COL; j++)
		{
			smartBoard[i][j].object = EMPTY;
			smartBoard[i][j].breadcrumb = false;
		}

}