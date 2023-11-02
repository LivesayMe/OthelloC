/*
* othello.c
* Implementation of the Othello game
* Author: Hunter Livesay
* Date: 1/6/2023
* General notes
* Black = -1, White = 1, Empty = 0
*/

#include "othello.h"
#include <stdio.h>
#include <stdlib.h>

//Returns a pointer to a 2D array of ints representing the starting board
int** get_starting_board()
{
    int** board = (int**)malloc(sizeof(int*) * 8);
    for (int i = 0; i < 8; i++)
    {
        board[i] = (int*)malloc(sizeof(int) * 8);
    }

    //Init board to empty
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            board[i][j] = 0;
        }
    }

    board[3][3] = 1;
    board[3][4] = -1;
    board[4][3] = -1;
    board[4][4] = 1;
    return board;
}

//Returns a pointer to a 2D array of ints representing a copy of the board
int** get_board_copy(int** board)
{
    int** copy = (int**)malloc(sizeof(int*) * 8);
    for (int i = 0; i < 8; i++)
    {
        copy[i] = (int*)malloc(sizeof(int) * 8);
    }
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            copy[i][j] = board[i][j];
        }
    }
    return copy;
}

//Returns a pointer to a 2D array of ints representing the tiles that would be flipped if the player made the move at row, col represented as a Nx2 array of ints, where N is the number of tiles to flip, returns NULL if the move is invalid
int** tiles_to_flip(int** board, int player, int row, int col)
{
    if (board[row][col] != 0)
    {
        return NULL;
    }

    //Maximum number of tiles that can be flipped is 32
    int** tiles = (int**)malloc(sizeof(int*) * 32);
    for (int i = 0; i < 32; i++)
    {
        tiles[i] = (int*)malloc(sizeof(int) * 2);
    }
    int count = 0;
    //Check all 8 directions
    //Up
    if(row - 1 >= 0)
    {
        for(int i = row - 1; i >= 0; i--)
        {
            if (board[i][col] == 0)
            {
                break;
            }
            else if (board[i][col] == player)
            {
                if (i != row - 1)
                {
                    for (int j = row - 1; j > i; j--)
                    {
                        tiles[count][0] = j;
                        tiles[count][1] = col;
                        count++;
                    }
                }
                break;
            }
        }
    }
    //Down
    if(row + 1 < 8)
    {    
        for (int i = row + 1; i < 8; i++)
        {
            if (board[i][col] == 0)
            {
                break;
            }
            else if (board[i][col] == player)
            {
                if (i != row + 1)
                {
                    for (int j = row + 1; j < i; j++)
                    {
                        tiles[count][0] = j;
                        tiles[count][1] = col;
                        count++;
                    }
                }
                break;
            }
        }
    }
    //Left
    if(col - 1 >= 0)
    {
        for (int i = col - 1; i >= 0; i--)
        {
            if (board[row][i] == 0)
            {
                break;
            }
            else if (board[row][i] == player)
            {
                if (i != col - 1)
                {
                    for (int j = col - 1; j > i; j--)
                    {
                        tiles[count][0] = row;
                        tiles[count][1] = j;
                        count++;
                    }
                }
                break;
            }
        }
    }
    //Right
    if(col + 1 < 8)
    {
        for (int i = col + 1; i < 8; i++)
        {
            if (board[row][i] == 0)
            {
                break;
            }
            else if (board[row][i] == player)
            {
                if (i != col + 1)
                {
                    for (int j = col + 1; j < i; j++)
                    {
                        tiles[count][0] = row;
                        tiles[count][1] = j;
                        count++;
                    }
                }
                break;
            }
        }
    }
    //Up-Left
    if(row - 1 >= 0 && col - 1 >= 0)
    {
        for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--)
        {
            if (board[i][j] == 0)
            {
                break;
            }
            else if (board[i][j] == player)
            {
                if (i != row - 1 && j != col - 1)
                {
                    for (int k = row - 1, l = col - 1; k > i && l > j; k--, l--)
                    {
                        tiles[count][0] = k;
                        tiles[count][1] = l;
                        count++;
                    }
                }
                break;
            }
        }
    }
    //Up-Right
    if(row - 1 >= 0 && col + 1 < 8)
    {
        for (int i = row - 1, j = col + 1; i >= 0 && j < 8; i--, j++)
        {
            if (board[i][j] == 0)
            {
                break;
            }
            else if (board[i][j] == player)
            {
                if (i != row - 1 && j != col + 1)
                {
                    for (int k = row - 1, l = col + 1; k > i && l < j; k--, l++)
                    {
                        tiles[count][0] = k;
                        tiles[count][1] = l;
                        count++;
                    }
                }
                break;
            }
        }
    }
    //Down-Left
    if(row + 1 < 8 && col - 1 >= 0)
    {
        for (int i = row + 1, j = col - 1; i < 8 && j >= 0; i++, j--)
        {
            if (board[i][j] == 0)
            {
                break;
            }
            else if (board[i][j] == player)
            {
                if (i != row + 1 && j != col - 1)
                {
                    for (int k = row + 1, l = col - 1; k < i && l > j; k++, l--)
                    {
                        tiles[count][0] = k;
                        tiles[count][1] = l;
                        count++;
                    }
                }
                break;
            }
        }
    }
    //Down-Right
    if(row + 1 < 8 && col + 1 < 8)
    {
        for (int i = row + 1, j = col + 1; i < 8 && j < 8; i++, j++)
        {
            if (board[i][j] == 0)
            {
                break;
            }
            else if (board[i][j] == player)
            {
                if (i != row + 1 && j != col + 1)
                {
                    for (int k = row + 1, l = col + 1; k < i && l < j; k++, l++)
                    {
                        tiles[count][0] = k;
                        tiles[count][1] = l;
                        count++;
                    }
                }
                break;
            }
        }
    }
    

    if (count == 0)
    {
        return NULL;
    }
    else
    {
        //Add a marker to the end of the array
        tiles[count][0] = -1;
        return tiles;
    }
}

//Returns a pointer to a 2D array of ints representing a copy of the board after the move has been made
int** make_move(int** board, int player, int row, int col)
{
    int** copy = get_board_copy(board);
    int** tiles = tiles_to_flip(copy, player, row, col);
    if (tiles != NULL)
    {
        copy[row][col] = player;
        for (int i = 0; i < 32; i++)
        {
            if (tiles[i][0] != -1)
            {
                //Check if the tile is in bounds
                if (tiles[i][0] < 0 || tiles[i][0] > 7 || tiles[i][1] < 0 || tiles[i][1] > 7)
                {
                    break;
                }
                copy[tiles[i][0]][tiles[i][1]] = player;
            }
            else
            {
                break;
            }
        }
        return copy;
    }
    else
    {
        return NULL;
    }
}

//Returns 1 if the game is over, and 0 otherwise
int is_game_over(int** board)
{
    //Check if there are any possible moves for either player
    int** moves = get_possible_moves(board, 1);
    if (moves[0][0] == -1)
    {
        moves = get_possible_moves(board, -1);
        if (moves[0][0] == -1)
        {
            return 1;
        }
    }
    return 0;
}

//Returns the winner of the game, or 0 if the game is not over
int get_winner(int** board)
{
    if (is_game_over(board))
    {
        int* score = get_score(board);
        if (score[0] > score[1])
        {
            return 1;
        }
        else if (score[0] < score[1])
        {
            return -1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}

//Returns a pointer to a 2D array of ints representing the possible moves for the player, each move is given as a row and column, returns -1 if there are no possible moves
int** get_possible_moves(int** board, int player)
{
    int** moves = (int**)malloc(sizeof(int*) * 64);
    for (int i = 0; i < 64; i++)
    {
        moves[i] = (int*)malloc(sizeof(int) * 2);
    }
    int count = 0;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (board[i][j] == 0)
            {
                //First check if there is a neighbor of the opposite color
                int has_neighbor = 0;
                for (int k = -1; k < 2; k++)
                {
                    for (int l = -1; l < 2; l++)
                    {
                        if (k != 0 || l != 0)
                        {
                            int r = i + k;
                            int c = j + l;
                            if (r >= 0 && r < 8 && c >= 0 && c < 8 && board[r][c] == -player && board[r][c] != 0)
                            {
                                has_neighbor = 1;
                            }
                        }
                    }
                }
                if (has_neighbor)
                {
                    int** temp = tiles_to_flip(board, player, i, j);
                    if (temp != NULL)
                    {
                        moves[count][0] = i;
                        moves[count][1] = j;
                        count++;
                    }
                }
            }
        }
    }
    if (count == 0)
    {
        moves[0][0] = -1;
        return moves;
    }
    else
    {
        //Set remaining moves to -1
        for (int i = count; i < 64; i++)
        {
            moves[i][0] = -1;
        }
        return moves;
    }
}

//Return the score of the board for both players
int* get_score(int** board)
{
    int* score = (int*)malloc(sizeof(int) * 2);
    score[0] = 0;
    score[1] = 0;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (board[i][j] == 1)
            {
                score[0]++;
            }
            else if (board[i][j] == -1)
            {
                score[1]++;
            }
        }
    }
    return score;
}