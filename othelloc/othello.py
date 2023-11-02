# othello.py
# Author: Hunter Livesay
# Date: 1/6/2023
# Description: Wraps the othello game logic from the c file into a python class
# 
# General Notes
# Black = -1, White = 1, Empty = 0
#
# C Functions
# //Returns a pointer to a 2D array of ints representing the starting board
# int** get_starting_board();

# //Returns a pointer to a 2D array of ints representing a copy of the board
# int** get_board_copy(int** board);

# //Returns a pointer to a 2D array of ints representing a copy of the board after the move has been made
# int** make_move(int** board, int player, int row, int col);

# //Returns 1 if the game is over, and 0 otherwise
# int is_game_over(int** board);

# //Returns the winner of the game, or 0 if the game is not over
# int get_winner(int** board);

# //Returns a pointer to a 2D array of ints representing the possible moves for the player, each move is given as a row and column
# int** get_possible_moves(int** board, int player);

# //Return the score of the board for both players
# int* get_score(int** board);

# //Returns a pointer to a 2D array of ints representing the tiles that would be flipped if the player made the move at row, col
# int** tiles_to_flip(int** board, int player, int row, int col);

import ctypes
import os

class Othello:

    def __init__(self) -> None:
        current_dir = os.path.dirname(os.path.abspath(__file__))
        library_file = os.path.join(current_dir, "othello.so")
        self.lib = ctypes.cdll.LoadLibrary(library_file)
        self.lib.get_starting_board.restype = ctypes.POINTER(ctypes.POINTER(ctypes.c_int))
        self.lib.get_board_copy.restype = ctypes.POINTER(ctypes.POINTER(ctypes.c_int))
        self.lib.make_move.restype = ctypes.POINTER(ctypes.POINTER(ctypes.c_int))
        self.lib.is_game_over.restype = ctypes.c_int
        self.lib.get_winner.restype = ctypes.c_int
        self.lib.get_possible_moves.restype = ctypes.POINTER(ctypes.POINTER(ctypes.c_int))
        self.lib.get_score.restype = ctypes.POINTER(ctypes.c_int)
        self.lib.tiles_to_flip.restype = ctypes.POINTER(ctypes.POINTER(ctypes.c_int))

        self.board = self.get_starting_board()
        self.cur_player = -1

    def get_starting_board(self) -> list:
        return self.lib.get_starting_board()
    
    def copy(self) -> object:
        ng = Othello()
        ng.board = self.lib.get_board_copy(self.board)
        ng.cur_player = self.cur_player
        return ng

    def make_move(self, player: int, move: list) -> list:
        self.board = self.lib.make_move(self.board, player, *move)
        self.cur_player = -player

        #Check if next player has moves
        if self.get_possible_moves(-player)[1] == 0:
            self.cur_player = player
        return self.board
    
    def is_game_over(self) -> int:
        return self.lib.is_game_over(self.board)
    
    def get_winner(self) -> int:
        return self.lib.get_winner(self.board)
    
    def get_possible_moves(self, player: int) -> list:
        moves = self.lib.get_possible_moves(self.board, player)
        #Check if moves is null
        if moves[0][0] == -1:
            return [], 0
        count = 0
        while moves[count][0] != -1:
            count += 1
        # Convert the 2D array of moves into a list of tuples
        return moves, count
    
    def get_score(self) -> list:
        s = self.lib.get_score(self.board)
        return [s[0], s[1]]
    
    def tiles_to_flip(self, player: int, *move) -> list:
        return self.lib.tiles_to_flip(self.board, player, *move)
    
    def print_board(self) -> None:
        tile_map = {-1: "⚫", 0: "  ", 1: "⚪"}

        #Print the board, score, and number grid along sides
        print("  ", end="")
        for i in range(8):
            print(str(i) + " ", end=" ")
        print()
        for i in range(8):
            print(i, end=" ")
            for j in range(8):
                print(tile_map[self.board[i][j]], end=" ")
            print()
        print("Score:", self.get_score())
        print("Current Player:", "White" if self.cur_player == 1 else "Black")
        
    def print_moves(self, player: int) -> None:
        moves, count = self.get_possible_moves(player)
        for i in range(count):
            print("Move", i, ":", moves[i][0], moves[i][1])
    
    def get_fen(self) -> str:
        fen = ""
        for i in range(8):
            for j in range(8):
                fen += str(self.board[i][j]+1)
            if i != 7:
                fen += "/"
        fen += "#" + str(self.cur_player)
        return fen