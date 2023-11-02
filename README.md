# OthelloC
Python library of C implementation of Othello

# Usage
```python
from othelloc import Othello
game = Othello()
game.print_board()
cur_player = game.cur_player()
game.make_move(cur_player, game.get_possible_moves(cur_player)[0])
game.print_board()
```

# Installation
```bash
pip install othelloc
```
# Classes
## Othello()
The base game class, which contains the board and the current player.

# Methods

## get_starting_board()
Returns the starting board position.

## copy()
Returns a deep copy of the current game.

## make_move(player, move)
Makes a move for the player. The move is a tuple of (row, col).

## is_game_over()
Returns 1 if the game is over, otherwise 0.

## get_winner()
Returns the winner of the game, or 0 if the game is not over.

## get_possible_moves(player)
Returns a list of possible moves for the player. The moves are tuples of (row, col).

## get_score()
Returns the score of the game. The score is a tuple of (black, white).

## tiles_to_flip(player, move)
Returns a list of tiles that will be flipped if the player makes the move. The move is a tuple of (row, col).

## print_board()
Prints the board, the current player and the score.

## print_moves(player)
Prints the possible moves for the player.

## get_fen()
Returns the FEN string of the current game.

# Attributes

## board
The board of the game. 0 is empty, -1 is black, 1 is white.

## cur_player
The current player. -1 is black, 1 is white.