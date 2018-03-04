#include <stdlib.h>
#include <curses.h>
#include <menu.h>
#include <string.h>


int main(int argc, char *argv[])
{
    int num = 0;

    /* initialize your non-curses data structures here */

    (void) initscr();      /* initialize the curses library */
    keypad(stdscr, TRUE);  /* enable keyboard mapping */
    (void) nonl();         /* tell curses not to do NL->CR/NL on output */
    (void) cbreak();       /* take input chars one at a time, no wait for \n */
    (void) echo();         /* echo input - in color */

    if (has_colors())
    {
        start_color();

        /*
         * Simple color assignment, often all we need.  Color pair 0 cannot
         * be redefined.  This example uses the same value for the color
         * pair as for the foreground color, though of course that is not
         * necessary:
         */
        init_pair(1, COLOR_RED,     COLOR_BLACK);
        init_pair(2, COLOR_GREEN,   COLOR_BLACK);
        init_pair(3, COLOR_YELLOW,  COLOR_BLACK);
        init_pair(4, COLOR_BLUE,    COLOR_BLACK);
        init_pair(5, COLOR_CYAN,    COLOR_BLACK);
        init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
        init_pair(7, COLOR_WHITE,   COLOR_BLACK);
    }

    printw("You find yourself locked out of the room. You need to acquire a key, \
    but where should you look? The forgetful librarians always leave hints for themselves \
    in case they ever lock themselves out. In this case, the hint is: ELBAT EHT REDNU\n");

    ITEM **my_item;
    int n_choices = 5;
    WINDOW *my_menu_win;
    int c;
    my_item = (ITEM **)calloc(n_choices + 1, sizeof(ITEM *));
    my_item[0] = new_item("A", "Inside the cupboard");
    my_item[1] = new_item("B", "Under the table");
    my_item[2] = new_item("C", "Under the door mat");
    my_item[3] = new_item("D", "On top of the shelf");
    MENU *my_menu = new_menu(my_item);

    /* Create the window to be associated with the menu */
          my_menu_win = newwin(10, 40, 4, 4);
          keypad(my_menu_win, TRUE);

  	/* Set main window and sub window */
          set_menu_win(my_menu, my_menu_win);
          set_menu_sub(my_menu, derwin(my_menu_win, 6, 38, 3, 1));
  	set_menu_format(my_menu, 5, 1);

  	/* Set menu mark to the string " * " */
          set_menu_mark(my_menu, " * ");

  	/* Print a border around the main window and print a title */
          box(my_menu_win, 0, 0);
          refresh();
  	//print_in_middle(my_menu_win, 1, 0, 40, "My Menu", COLOR_PAIR(1));
  	//mvwaddch(my_menu_win, 2, 0, ACS_LTEE);
  	//mvwhline(my_menu_win, 2, 1, ACS_HLINE, 38);
  	mvwaddch(my_menu_win, 2, 39, ACS_RTEE);

    post_menu(my_menu);
    wrefresh(my_menu_win);
    refresh();

    while((c = getch()) != '\r')
    {   switch(c)
        { case KEY_DOWN:
            menu_driver(my_menu, REQ_DOWN_ITEM);
            break;
          case KEY_UP:
            menu_driver(my_menu, REQ_UP_ITEM);
            break;
        }
        wrefresh(my_menu_win);
      }
    clear();
    printw("You chose choice: %s\n", item_name(current_item(my_menu)));
    printw("Which is: %s\n", item_description(current_item(my_menu)));

    if(strcmp(item_name(current_item(my_menu)), "B")==0){
      printw("Congratulations! You escaped!");
    }
    else{
      printw("Sorry, that's not right. Lose 1 life.");
    }
    free_item(my_item[0]);
    free_item(my_item[1]);
    free_item(my_item[2]);
    free_item(my_item[3]);
    free_menu(my_menu);
    getch();

    endwin();               /* we're done */
    exit(0);
}
