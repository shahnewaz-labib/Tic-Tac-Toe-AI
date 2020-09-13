#include "bits/stdc++.h"

using namespace std;

// AI is the maximizing player.
// Player is the minimizing player.
char ai = 'O', player = 'X';

// Structer to store row and col of a move
struct Move {
    int row, col;
};

// Evaluate the current state of the board
int getCurrentScore(char board[3][3]) {
    // check the rows
    for(int row = 0; row < 3; row++) {
        if(board[row][0] == board[row][1] and board[row][1] == board[row][2]) {
            if(board[row][1] == ai) return 10;
            else if(board[row][1] == player) return -10; 
        }
    }
    // check the cols
    for(int col = 0; col < 3; col++) {
        if(board[0][col] == board[1][col] and board[1][col] == board[2][col]) {
            if(board[1][col] == ai) return 10;
            else if(board[1][col] == player) return -10;
        }
    }
    // check the diagonal
    if(board[0][0] == board[1][1] and board[1][1] == board[2][2]) {
        if(board[1][1] == ai) return 10;
        else if(board[1][1] == player) return -10;
    }
    // check the diagonal
    if(board[2][0] == board[1][1] and board[1][1] == board[0][2]) {
        if(board[1][1] == ai) return 10;
        else if(board[1][1] == player) return -10;
    }
    
    return 0; // No game determining state yet

}

// Check if there is any move left
bool noMovesLeft(char board[3][3]) {
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(board[i][j] == ' ')
                return false;   // At least  one move is left
        }
    }
    return true;
}

// MiniMax algorithm
int minimax(char board[3][3], bool maximizing) {
    int currentScore = getCurrentScore(board);
    if(currentScore == 10 or currentScore == -10)
        return currentScore;
    if(noMovesLeft(board))
        return 0;
    
    if(maximizing) {
        int bestScore = -1000;

        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                if(board[i][j] == ' ') {
                    board[i][j] = ai;
                    bestScore = max(bestScore, minimax(board, !maximizing));
                    board[i][j] = ' ';
                }
            }
        }

        return bestScore;

    } else {
        int bestScore = 1000;

        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                if(board[i][j] == ' ') {
                    board[i][j] = player;
                    bestScore = min(bestScore, minimax(board, !maximizing));
                    board[i][j] = ' ';
                }
            }
        }

        return bestScore;
    }
}

Move getBestMove(char board[3][3]) {
    Move bestMove;
    bestMove.row = bestMove.col = -1;
    int bestValue = -1000;

    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(board[i][j] == ' ') {
                board[i][j] = ai;
                int moveValue = minimax(board, false);

                if(moveValue > bestValue) {
                    bestValue = moveValue;
                    bestMove.row = i;
                    bestMove.col = j;
                }

                board[i][j] = ' ';
            }
        }
    }


    return bestMove;
}

pair<int, int> getAiMove(char board[3][3]) {
    Move optimalMove = getBestMove(board);
    return {optimalMove.row, optimalMove.col};
}

/*
int main() { // for testing
    char board[3][3] = {
        {'O', 'O', 'X'},
        {'X', 'X', 'O'},
        {'O', 'X', ' '}
    };
    pair<int, int> aiMove = getAiMove(board);
    printf("Row: %d\nCol: %d\n", aiMove.first, aiMove.second);
    board[aiMove.first][aiMove.second] = ai;
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			printf("%c ", board[i][j]);
		}
		cout << endl;
	}
}
*/

