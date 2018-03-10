#include <stdlib.h>
#include <curses.h>
#include <menu.h>
#include <string.h>


/* Sets up an NCURSES multiple choice question
 *
 * question: text of the question as a string
 * n_choices: number of choices
 * options: array of strings which are the choices
 * correct: index of correct choice in options
 */
int mc_question(char *question, int n_choices, char *options[], int correct){

  // set up variables for this functions
  char letter[n_choices][2];
  const char *response;
  ITEM **my_items;
  WINDOW *my_menu_win;
  int i;
  int c;
  my_items = (ITEM **)calloc(n_choices + 1, sizeof(ITEM *));

  // only allow for 7 or fewer multiple choice options
  if(n_choices > 8){
    printw("Sorry, this only supports questions with 7 or fewer choices");
    return -1;
    //endwin();
    //exit(0);
  }

  printw(question);

  // set up the menu items with the appropriate letter and option text
  for(i=0; i<n_choices; i++){
    // A is 65 in ASCII
    letter[i][0] = (char)i+65;
    letter[i][1] = '\0';
    my_items[i] = new_item(letter[i], options[i]);
  }

  // set up the menu with the items
  MENU *my_menu = new_menu(my_items);

  // sets up a menu window (height, width, y, x)
  my_menu_win = newwin(15, 60, 6, 8);
  // activates the keypad for that window
  keypad(my_menu_win, TRUE);

  // put the menu into the menu window
  set_menu_win(my_menu, my_menu_win);
  // sets up subwindow for menu so it is nicely padded in center
  set_menu_sub(my_menu, derwin(my_menu_win, 6, 38, 3, 1));
  // sets max display size for menu and makes scrollable if necessary
  set_menu_format(my_menu, 5, 1);

  set_menu_mark(my_menu, " * ");

  // draws a box around the menu window
  box(my_menu_win, 0, 0);
  refresh();

  // post the menu and refresh everything
  post_menu(my_menu);
  wrefresh(my_menu_win);
  refresh();

  // handle selection and scrolling through the menu
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

  // display the user's choice
  clear();
  printw("You chose choice: %.1s\n", item_name(current_item(my_menu)));
  printw("Which is: %s\n", item_description(current_item(my_menu)));

  // get response then free items
  response = item_name(current_item(my_menu));
  free_item(my_items[0]);
  free_item(my_items[1]);
  free_item(my_items[2]);
  free_item(my_items[3]);
  free_menu(my_menu);
  delwin(my_menu_win);

  // determine if they were right or wrong return 0 for correct and 1 for incorrect
  if(strcmp(response, letter[correct])==0){
    printw("Congratulations! You escaped!\n");
    return 1;
  }
  else{
    printw("Sorry, that's not right. Lose 1 life.\n");
    return 0;
  }

}


/* Sets up gameplay for NCURSES escape the room game
 */
int main(int argc, char *argv[])
{
    // setup NCURSES
    (void) initscr();      /* initialize the curses library */
    keypad(stdscr, TRUE);  /* enable keyboard mapping */
    (void) nonl();         /* tell curses not to do new line carriage return */
    (void) cbreak();       /* take input chars one at a time, no wait for \n */
    (void) echo();         /* echo input */


    // set up variables for question 1
    int num = 0;
    char *question1 = "You find yourself locked out of the room. You need to acquire a key, \
    but where should you look? The forgetful librarians always leave hints for themselves \
    in case they ever lock themselves out. In this case, the hint is: ELBAT EHT REDNU\n";

    int num_choices = 4;
    char *options1[num_choices];
    options1[0] = "Inside the cupboard";
    options1[1] = "Under the table";
    options1[2] = "Under the door mat";
    options1[3] = "On top of the shelf";

    mc_question(question1, num_choices, options1, 1);

    // wait for the user to press a key after the question
    getch();

    // exit NCURSES
    endwin();
    exit(0);
}
