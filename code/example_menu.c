#include <stdlib.h>
#include <curses.h>
#include <signal.h>
#include <menu.h>

static void finish(int sig);

int main(int argc, char *argv[])
{
    int num = 0;

    /* initialize your non-curses data structures here */

    (void) signal(SIGINT, finish);      /* arrange interrupts to terminate */

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

    ITEM **my_item;
    int n_choices = 5;
    int c;
    my_item = (ITEM **)calloc(n_choices + 1, sizeof(ITEM *));
    my_item[0] = new_item("A", "insert choice a here");
    my_item[1] = new_item("B", "insert choice b here");
    my_item[2] = new_item("C", "insert choice c here");
    my_item[3] = new_item("D", "insert choice d here");
    MENU *my_menu = new_menu(my_item);
    post_menu(my_menu);
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
      }
    clear();
    printw("You chose choice: %s\n", item_name(current_item(my_menu)));
    printw("Which is: %s", item_description(current_item(my_menu)));
    free_item(my_item[0]);
    free_item(my_item[1]);
    free_item(my_item[2]);
    free_item(my_item[3]);
    free_menu(my_menu);
    getch();

    finish(0);               /* we're done */
}

static void finish(int sig)
{
    endwin();

    /* do your non-curses wrapup here */

    exit(0);
}
