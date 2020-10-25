#include <iostream>
#include <string.h>

#include "minimax.h"
// #include "functions.h"

#ifdef _WIN32
    #include <windows.h>
#elif __linux__
    #include <unistd.h>
#endif


using namespace std;

char board[3][3];
// string playerName;
bool turn = true; // true for HUMAN --> X
                  // false for AI --> O
bool active = true; // true means game is running.
bool runGame = true; // for the main while loop.

void clr() {
    // Clear the screen.
    #ifdef _WIN32   
        system("cls");  
    #elif __linux__ 
        system("clear");   
    #endif
}

void show_board() {
    /*
    cout << "\t\t\t\t" << board[0][0] << "|" << board[0][1] << "|" << board[0][2] << endl;
    cout << "\t\t\t\t" << "-----" << endl;
    cout << "\t\t\t\t" << board[1][0] << "|" << board[1][1] << "|" << board[1][2] << endl;
    cout << "\t\t\t\t" << "-----" << endl;
    cout << "\t\t\t\t" << board[2][0] << "|" << board[2][1] << "|" << board[2][2] << endl;
    */
   // Display the board.
    printf("\t\t\tTic Tac Toe\n\n");
    printf("\t\t\t%c | %c | %c\n\t\t\t----------\n\t\t\t%c | %c | %c\n\t\t\t----------\n\t\t\t%c | %c | %c\n", board[0][0], board[0][1], board[0][2], board[1][0], board[1][1], board[1][2], board[2][0], board[2][1], board[2][2]);
    cout << endl << endl;
}

void take_input() {
    if(turn) {
        // player turn.
        tryagain:
        printf("\t\t\tEnter Row Play : ");
        int row;
        cin >> row;
        printf("\t\t\tEnter Col Play : ");
        int col;
        cin >> col;

        if(board[row-1][col-1] != ' ' or !(row >= 1 and row <= 3 and col >= 1 and col <= 3)) {
            printf("\t\t\tInvalid move... Try again!\n");
            goto tryagain;  // prompt the user to put valid values.
        }

        board[row-1][col-1] = player; // player move.

        turn = !turn;  // next turn is AI's.
        
    } else {
        // AI turn
        // sleep(5);
        pair<int, int> aiMove = getAiMove(board);   // function call to get the AI's optimal moves.
        board[aiMove.first][aiMove.second] = ai;    // AI move.
        turn = !turn;   // next turn is player's.
    }
}

void check_winner() {
    clr();          // clear the board
    show_board();   // Show the current state of the game.
    int score = getCurrentScore(board); // evaluating the current state of the game.
    if(score == 10) {
        // Game is over. 10 means AI has won, as AI is the maximizing player.
        active = false; // Game is now inactive.
        printf("\t\t\tGAME OVER!\n\t\t\t\tAI WON! You lost!\n");
    } else if(score == -10) {
        // Game is over. -10 means player has won at this point, as player is the minimizing player.
        active = false; // Game is now inactive.
        printf("\t\t\tGAME OVER!\n\t\t\t\tYOU WON! AI lost!\n");
    }
    if(noMovesLeft(board)) { // No moves left and nobody won. So this is a Tie state.
        active = false; // Game is now inactive.
        printf("\t\t\tGAME OVER!\n\t\t\t\tIt's a TIE!\n");
    }
    if(!active) {
        cout << "\t\t\tpress ENTER to continue. ";
        getchar();
        getchar();
    }
    return;
}


void play() {
    show_board();   // Show the board.
    take_input();   // Take moves from player or AI.
    check_winner(); // Check if anyone has won or not.

    clr();  // Clear screen.
}


void initialize() {
    memset(board, ' ', sizeof board); // Clear the board.
    active = true;  // Game is now activated.
    turn = true;    // True means player goes first.
}

void menu() {
    clr();  // Clear the screen
    printf("\t\t\tTic Tac Toe\n\n");
    printf("Wanna Play?\n\t1. Play\n\t2. Quit\nYour Choice : ");
    int choice;
    cin >> choice;  // Take player choice.
    if(choice == 1) {
        active = true;  // Activate the game
        initialize();   // Initialize the game
        clr();  // Clear screen
    } else {
        active = false; // Deactivate the game
        runGame = false;// Deactivate the main loop
    }

    return;
}


int main() {
    initialize();   // Initialize the game for the first time
    while(runGame) {    // Main loop
        menu();
        while(active) {
            play();     // :)
        }
    }
    cout << "\n\t\tHAVE A NICE DAY! :)\n";
    return 0;
}


// gg!
