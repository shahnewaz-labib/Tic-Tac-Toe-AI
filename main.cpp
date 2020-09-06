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
string playerName;
bool turn = true; // true for HUMAN --> X
bool active = true;
bool runGame = true;

void clr() {
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
    printf("\t\t\tTic Tac Toe\n\n");
    printf("\t\t\t%c | %c | %c\n\t\t\t----------\n\t\t\t%c | %c | %c\n\t\t\t----------\n\t\t\t%c | %c | %c\n", board[0][0], board[0][1], board[0][2], board[1][0], board[1][1], board[1][2], board[2][0], board[2][1], board[2][2]);
    cout << endl << endl;
}

void take_input() {
    if(turn) {
        // player turn
        tryagain:
        printf("\t\t\tEnter Row Play : ");
        int row;
        cin >> row;
        printf("\t\t\tEnter Col Play : ");
        int col;
        cin >> col;

        if(board[row-1][col-1] != ' ' or !(row >= 1 and row <= 3 and col >= 1 and col <= 3)) {
            printf("\t\t\tInvalid move... Try again!\n");
            goto tryagain;
        }

        board[row-1][col-1] = player;

        turn = !turn;        
        
    } else {
        // AI turn
        // sleep(5);
        pair<int, int> aiMove = getAiMove(board);
        board[aiMove.first][aiMove.second] = ai;
        turn = !turn;
    }
}

void check_winner() {
    int score = getCurrentScore(board);
    if(score == 10) {
        active = false;
        printf("\t\t\tGAME OVER!\n\t\t\t\tAI WON! You lost!\n");
        getchar();
        getchar();
        return;
    } else if(score == -10) {
        active = false;
        printf("\t\t\tGAME OVER!\n\t\t\t\tYOU WON! AI lost!\n");
        getchar();
        getchar();
        return;
    }
    if(noMovesLeft(board)) {
        active = false;
        printf("\t\t\tGAME OVER!\n\t\t\t\tIt's a TIE!\n");
        getchar();
        getchar();
    }
    
    return;
}


void play() {
    show_board();
    take_input();
    check_winner();

    clr();
}


void initialize() {
    memset(board, ' ', sizeof board);
    active = true;
    turn = true;
}

void menu() {
    clr();
    printf("\t\t\tTic Tac Toe\n\n");
    printf("Wanna Play?\n\t1. Play\n\t2. Quit\nYour Choice : ");
    int choice;
    cin >> choice;
    if(choice == 1) {
        active = true;
        clr();
    } else {
        active = false;
        runGame = false;
    }

    return;
}


int main() {
    initialize();
    while(runGame) {
        menu();
        while(active) {
            play();
        }
    }

    return 0;
}