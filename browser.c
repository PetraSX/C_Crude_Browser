#include <ncurses.h>
#include "defines.h"

void init_ncurses(int useRaw, int useNoecho)
{
	initscr();
	if(useRaw == 1)
		raw();
	if(useNoecho == 1)
		noecho();
}

char mainpage_title[25][90] = {
" $$$$$$  $$$$$$  $$$$$$$ $     $  $$$$$  $$$$$$$ $$$$$$  $     $ $       ",
" $     $ $     $ $     $ $  $  $ $     $ $       $     $ $     $ $       ",
" $     $ $     $ $     $ $  $  $ $       $       $     $ $     $ $       ",
" $$$$$$  $$$$$$  $     $ $  $  $  $$$$$  $$$$$   $$$$$$  $     $ $       ",
" $     $ $   $   $     $ $  $  $       $ $       $   $   $     $ $       ",
" $     $ $    $  $     $ $  $  $ $     $ $       $    $  $     $ $       ",
" $$$$$$  $     $ $$$$$$$  $$ $$   $$$$$  $$$$$$$ $     $  $$$$$  $$$$$$$ ",
"                                                                         ",
" $       $     $ $$$                                                     ",
" $       $     $  $                                                      ",
" $       $     $  $                                                      ",
" $       $     $  $                                                      ",
" $       $     $  $                                                      ",
" $       $     $  $                                                      ",
" $$$$$$$  $$$$$  $$$                                                     ",
"                                                                         ",
" $$$$$$  $$$       $ $     $                                             ",
" $     $  $        $ $     $                                             ",
" $     $  $        $ $     $                                             ",
" $$$$$$   $        $ $     $                                             ",
" $     $  $  $     $ $     $                                             ",
" $     $  $  $     $ $     $                                             ",
" $$$$$$  $$$  $$$$$   $$$$$                                              ",
};

WINDOW *create_newwin(int height, int width, int y_start, int x_start);
void destroy_win(WINDOW *local_win);
void print_title(int y_max, int x_max);
void searchBar_prep(int *no_letter, char word[], int *is_pressed);
void parse_search(SITE_MEMORY *web_pages, int no_sites, int has_keyword[], int no_letters, char words[]);

int main (int argc, char ** argv)
{
	SITE_MEMORY *web_pages = NULL;
	WINDOW *inputwin;
	WINDOW *outputwin;

	int index_i;
	int y_max;
	int x_max;
	int no_sites;
	int has_keyword[1000] = {0};
	int no_letters = 0;
	int is_enter_pressed = 0;
	

	char querry[1000] = {0};
	char ch_1;
	char ch_2;

	//Reading HTML data BASE
	read_dataBase(&web_pages);
	no_sites = web_pages->no_sites;
	
	//Initializing the main screen and colors
	init_ncurses(true, true);
	if(!has_colors())
	{
		printw("Terminal does not support colors.\nPress any key to exit...");
		getch();
		return -1;
	}
	start_color();
	init_pair(1, 1, 2);
	
	//Getting screen max size
	getmaxyx(stdscr, y_max, x_max);

	while(1)
	{
		print_title(y_max, x_max);
		ch_1 = getch();
		if(ch_1 == 'C')
		{
			clear();
			refresh();

			//Initializing the search bar
			outputwin = create_newwin(y_max - 1, x_max - 6, 0, 3);
			inputwin = create_newwin(3, x_max-10, 1, 5);
			
			wmove(inputwin, 1, 1);
			searchBar_prep(&no_letters, querry, &is_enter_pressed);

			while(1)
			{
				ch_2 = wgetch(inputwin);
				if(ch_2 == 10)
				{
					curs_set(0);
					querry[no_letters] = '\0';
					is_enter_pressed = 1;

					//parse_search(web_pages, no_sites, has_keyword, no_letters, querry);

					mvprintw(10, 10, "%s", querry);
					refresh();
				}

				if(is_enter_pressed == 0)
				{
					wprintw(inputwin, "%c", ch_2);
					querry[no_letters++] = ch_2;
				}
				else if(is_enter_pressed == 1 && ch_2 == 'Q')
				{
					destroy_win(inputwin);
					destroy_win(outputwin);
					curs_set(1);
					break;
				}
			}
		}
		else if(ch_1 == 'Q')
		{
			//Pressing the Q exits the program (in this case is interrupting the infinite loop)
			break;
		}	
	}

	//Freeing the database memory
	for (index_i = 0; index_i < no_sites; index_i++)
	{
		free(web_pages[index_i].container);
		free(web_pages[index_i].tag);
	}				    
	free(web_pages);
	
	//Waiting for input to close the application
	endwin();
	


	return 0;
}

WINDOW *create_newwin(int height, int width, int y_start, int x_start)
{
	WINDOW *local_win;
	local_win = newwin(height, width, y_start, x_start);
	box(local_win, 0 , 0);
	wrefresh(local_win);
	return local_win;
}

void destroy_win(WINDOW *local_win)
{
	wborder(local_win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	wrefresh(local_win);
	delwin(local_win);
	clear();
}

void print_title(int y_max, int x_max)
{
	int poz_y = y_max/4;
	int poz_x = x_max/6;
	int i;

	for(i = 0; i < 24; i++)
	{
		mvprintw(poz_y + i, poz_x, "%s", mainpage_title[i]);
	}
}

void searchBar_prep(int *no_letter, char word[], int *is_pressed)
{
	int i;
	for(i = 0; i < *no_letter; i++)
		word[i] = 0;
	*no_letter = 0;
	*is_pressed = 0;
}

void parse_search(SITE_MEMORY *web_pages, int no_sites, int has_keyword[], int no_letters, char words[])
{
	int index = 0;
	int quote_flag = 0;
	while(index < no_letters)
	{
		if(words[index] == '"')
		{
			index++;
			while(words[index] != '"')
			{
				index++;
				//More to be continued
			}
		}
		index++;
	}
}
