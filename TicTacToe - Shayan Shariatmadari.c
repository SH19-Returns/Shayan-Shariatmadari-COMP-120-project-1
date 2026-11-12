/*
 * Tic Tac Toe project
 * Input:   Any number from 0-8
 * Output:  Board with player icons O and X as the player and the computer play against each other
 * Author:  Shayan Shariatmadari
 * Date:    October 20th / 2026
 * Sources: Gemini, Claude, Stackoverflow
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// Function prototypes
void init_board(char board[9]);
void display_board(const char board[9]);
bool is_winner(const char board[9], char player);
char other_player(char player);
int get_human_move(const char board[9]);
int get_computer_move(const char board[9]);
void take_turn(char board[9], char player);
void play_game();
bool play_again();

// Makes the main board with empty spaces
void init_board(char board[9]) {
    for (int i = 0; i < 9; i++) {
        board[i] = ' ';
    }
}

// Displays the board in a 3x3 grid using a temporary array
void display_board(const char board[9]) {
    char c[9];

    // Copies board and replaces empty spaces with numbers 0-8
    for (int i = 0; i < 9; i++) {
        if (board[i] == ' ') {
            c[i] = '0' + i;
        } else {
            c[i] = board[i];
        }
    }

    printf("\n");
    for (int i = 0; i < 9; i++) {
        printf(" %c ", c[i]);

        if ((i + 1) % 3 == 0) {
            printf("\n");
            // Prints a horizontal separator line for the first two rows
            if (i < 6) {
                printf("---+---+---\n");
            }
        } else {
            printf("|"); // Prints vertical separators between columns
        }
    }
    printf("\n");
}

// Checks if the given player has three in a row
bool is_winner(const char board[9], char player) {
    // Vertical win check
    for (int i = 0; i < 3; i++) {
        if (board[i] == player && board[i + 3] == player && board[i + 6] == player) {
            return true;
        }
    }

    // Horizontal win check
    for (int i = 0; i < 9; i += 3) {
        if (board[i] == player && board[i + 1] == player && board[i + 2] == player) {
            return true;
        }
    }

    // Diagonal win checks
    if (board[0] == player && board[4] == player && board[8] == player) {
        return true;
    }
    if (board[2] == player && board[4] == player && board[6] == player) {
        return true;
    }

    return false;
}

// Returns the opposite player symbol
char other_player(char player) {
    return (player == 'O') ? 'X' : 'O';
}

// Asks until the user enters a valid empty square from 0 to 8
int get_human_move(const char board[9]) {
    int choice;
    bool valid = false;

    while (!valid) {
        printf("Your turn (O). Enter a square number (0-8): ");

        // Checks validity of typed input
        if (scanf("%d", &choice) != 1) {
            printf("  Invalid input. Please enter a number from 0 to 8.\n");
            while (getchar() != '\n');
            continue;
        }

        // Checks if number is within 0-8
        if (choice < 0 || choice > 8) {
            printf("  Number out of range. Please choose a square from 0 to 8.\n");
            continue;
        }

        // Checks if square is already taken
        if (board[choice] != ' ') {
            printf("  That square is already taken. Choose an empty one.\n");
            continue;
        }

        valid = true;
    }

    return choice;
}

// Picks a random empty square for the computer
int get_computer_move(const char board[9]) {
    int choice;

    do {
        choice = rand() % 9;
    } while (board[choice] != ' ');

    return choice;
}

// Lets the current player make one move and updates the board
void take_turn(char board[9], char player) {
    int move;

    if (player == 'O') {
        move = get_human_move(board);
    } else {
        printf("Computer (X) is thinking...\n");
        move = get_computer_move(board);
        printf("Computer (X) chose square %d. Your move next!\n", move);
    }

    board[move] = player;
}

// Plays one complete game of up to 9 turns
void play_game() {
    char board[9];
    char current_player = 'O'; // Human is O and goes first
    bool game_over = false;

    init_board(board);

    printf("=====================================\n");
    printf("        TIC-TAC-TOE vs COMPUTER\n");
    printf("=====================================\n");
    printf("You are O and you go first. The computer is X.\n");
    printf("On your turn, type the number of an empty square:\n");

    display_board(board);

    // Counted loop for the maximum 9 turns of a game
    for (int turn = 0; turn < 9 && !game_over; turn++) {
        take_turn(board, current_player);
        display_board(board);

        if (is_winner(board, current_player)) {
            if (current_player == 'O') {
                printf("Congratulations! You (O) win!\n");
            } else {
                printf("Computer (X) wins! Better luck next time.\n");
            }
            game_over = true;
        } else {
            current_player = other_player(current_player);
        }
    }

    if (!game_over) {
        printf("It's a draw!\n");
    }
}

// Asks whether to play another game (y) or quit (q)
bool play_again() {
    char choice;

    while (true) {
        printf("\nWould you like to play again? Enter 'y' to play again or 'q' to quit: ");
        scanf(" %c", &choice);
        while (getchar() != '\n'); // Clears remaining characters in input buffer

        if (choice == 'y' || choice == 'Y') {
            return true;
        } else if (choice == 'q' || choice == 'Q') {
            return false;
        } else {
            printf("  Invalid choice. Please enter 'y' or 'q'.\n");
        }
    }
}

int main() {
    srand(time(NULL)); // Seed random number generator once at the start of main

    do {
        play_game();
    } while (play_again());

    printf("Thanks for playing! Goodbye.\n");
    return 0;
}