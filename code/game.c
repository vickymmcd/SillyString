#include <stdlib.h>
#include <curses.h>
#include <menu.h>
#include <string.h>


void mc_question(char *question, int n_choices, char *options[], int correct){
  if(n_choices > 8){
    endwin();
    exit(0);
  }

  char *Letters = "ABCDEFGH";

  printw(question);
  ITEM **my_items;
  int i;
  WINDOW *my_menu_win;
  int c;
  my_items = (ITEM **)calloc(n_choices + 1, sizeof(ITEM *));
  for(i=0; i<n_choices; i++){
    my_items[i] = new_item(&Letters[i], options[i]);
  }
  MENU *my_menu = new_menu(my_items);

  my_menu_win = newwin(10, 40, 4, 4);
  keypad(my_menu_win, TRUE);

  set_menu_win(my_menu, my_menu_win);
  set_menu_sub(my_menu, derwin(my_menu_win, 6, 38, 3, 1));
  set_menu_format(my_menu, 5, 1);

  set_menu_mark(my_menu, " * ");

  box(my_menu_win, 0, 0);
  refresh();
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

  if(strcmp(item_name(current_item(my_menu)), &Letters[correct])==0){
    printw("Congratulations! You escaped!");
  }
  else{
    printw("Sorry, that's not right. Lose 1 life.");
  }

  free_item(my_items[0]);
  free_item(my_items[1]);
  free_item(my_items[2]);
  free_item(my_items[3]);
  free_menu(my_menu);
}


int main(int argc, char *argv[])
{
    int num = 0;
    char *question1 = "You find yourself locked out of the room. You need to acquire a key, \
    but where should you look? The forgetful librarians always leave hints for themselves \
    in case they ever lock themselves out. In this case, the hint is: ELBAT EHT REDNU\n";

    int num_choices = 4;
    char *options[num_choices];
    options[0] = "Inside the cupboard";
    options[1] = "Under the table";
    options[2] = "Under the door mat";
    options[3] = "On top of the shelf";


    (void) initscr();      /* initialize the curses library */
    keypad(stdscr, TRUE);  /* enable keyboard mapping */
    (void) nonl();         /* tell curses not to do NL->CR/NL on output */
    (void) cbreak();       /* take input chars one at a time, no wait for \n */
    (void) echo();         /* echo input - in color */

    mc_question(question1, num_choices, options, 1);

    getch();

    endwin();               /* we're done */
    exit(0);
}
