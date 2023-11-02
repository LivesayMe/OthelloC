/*
* Header file for othello game
* Optimized code for othello game
* Author: Hunter Livesay
* 1/6/2023
*
* General notes
* Black = -1, White = 1, Empty = 0
*/

//Returns a pointer to a 2D array of ints representing the starting board
int** get_starting_board();

//Returns a pointer to a 2D array of ints representing a copy of the board
int** get_board_copy(int** board);

//Returns a pointer to a 2D array of ints representing a copy of the board after the move has been made
int** make_move(int** board, int player, int row, int col);

//Returns 1 if the game is over, and 0 otherwise
int is_game_over(int** board);

//Returns the winner of the game, or 0 if the game is not over
int get_winner(int** board);

//Returns a pointer to a 2D array of ints representing the possible moves for the player, each move is given as a row and column
int** get_possible_moves(int** board, int player);

//Return the score of the board for both players
int* get_score(int** board);

//Returns a pointer to a 2D array of ints representing the tiles that would be flipped if the player made the move at row, col
int** tiles_to_flip(int** board, int player, int row, int col);