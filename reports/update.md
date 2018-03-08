# Escape the Room Game
### Vicky McDermott

## Project Idea Description
For this project we will be creating an interactive, text-based game in the terminal. It will be an “escape room” game, where the player will try different interaction commands to escape the room. Our stretch goal is to create multiple endings based on the decisions the player makes. Our lower bound is a basic straightforward escape room that is easy to complete, and the game has preset commands to choose from.

## Learning Goals
I want to learn more about strings and how strings work in C. I want to learn about how we can manipulate strings and how pointers to strings and char arrays work. By making a terminal based game, we will also learn how to be more familiar with working with special characters. I plan on creating functions that pass string pointers for questions and options. This will both help the code to be clean and help me to learn more about working with string pointers in C.

## Resources and Current Progress
We have found a tutorial online for NCURSES, which is helping in formatting our game in the terminal: [NCURSES introduction](https://invisible-island.net/ncurses/ncurses-intro.html).
Another great resource that we are using to learn about NCURSES is this online tutorial: [NCURSES Tutorial] (http://tldp.org/HOWTO/NCURSES-Programming-HOWTO/).
So far, I have worked through 7 of the 12 NCURSES Tutorials and created a basic implementation of our game. In this basic implementation, an NCURSES menu prompts the user for their answer to a puzzle question. The user uses the arrow keys to select an answer and if they get the question correct, are told on the next screen that they have successfully escaped the room. Otherwise, they are told they lost the game.

## First Steps
* Currently, I am working on refactoring the code. I would like to split it up into a question function so that it is easy to add additional questions to the game and so that I am able to better understand string pointers in C. Definition of done is that the code is split into at least two functions that allow for additional questions to be added easily.
* I am also working on incorporating other question types (in addition to multiple choice) into the code. I am going to add one open response question that I implemented as part of one of the tutorials.
* I am also going to work through the mouse input tutorial and see if I can make one question involving mouse input.
* Lastly, I need to finish brainstorming and planning out the escape the room questions and solutions.
