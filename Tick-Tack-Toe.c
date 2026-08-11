#include <stdio.h>
#include <stdbool.h>

#define SIZE 3

// Initialize the board with numbers 1-9 so players can pick positions easily
void initBoard(char board[SIZE][SIZE]) {
    char count = '1';
    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {
            board[r][c] = count++;
        }
    }
}

// Display the current state of the board
void printBoard(char board[SIZE][SIZE]) {
    printf("\n");
    for (int r = 0; r < SIZE; r++) {
        printf(" %c | %c | %c \n", board[r][0], board[r][1], board[r][2]);
        if (r < SIZE - 1) {
            printf("---|---|---\n");
        }
    }
    printf("\n");
}

// Place player token ('X' or 'O') based on position 1-9
bool placeMark(char board[SIZE][SIZE], int move, char token) {
    int row = (move - 1) / SIZE;
    int col = (move - 1) % SIZE;

    // Check if space is already taken by 'X' or 'O'
    if (board[row][col] == 'X' || board[row][col] == 'O') {
        return false;
    }

    board[row][col] = token;
    return true;
}

// Check for victory across rows, columns, and diagonals
bool checkWin(char board[SIZE][SIZE], char token) {
    // Rows and Columns
    for (int i = 0; i < SIZE; i++) {
        if ((board[i][0] == token && board[i][1] == token && board[i][2] == token) ||
            (board[0][i] == token && board[1][i] == token && board[2][i] == token)) {
            return true;
        }
    }

    // Diagonals
    if ((board[0][0] == token && board[1][1] == token && board[2][2] == token) ||
        (board[0][2] == token && board[1][1] == token && board[2][0] == token)) {
        return true;
    }

    return false;
}

// Check if all spots are filled
bool isBoardFull(char board[SIZE][SIZE]) {
    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {
            if (board[r][c] != 'X' && board[r][c] != 'O') {
                return false;
            }
        }
    }
    return true;
}

int main() {
    char board[SIZE][SIZE];
    char players[2] = {'X', 'O'};
    int turn = 0;
    bool gameOver = false;

    initBoard(board);

    printf("===============================\n");
    printf("    WELCOME TO TIC-TAC-TOE     \n");
    printf("===============================\n");

    while (!gameOver) {
        printBoard(board);
        char currentToken = players[turn];
        int move;

        printf("Player %d (%c), select a cell (1-9): ", turn + 1, currentToken);
        if (scanf("%d", &move) != 1) {
            // Clear invalid non-integer input
            while (getchar() != '\n');
            printf("Invalid input! Enter a number between 1 and 9.\n");
            continue;
        }

        if (move < 1 || move > 9) {
            printf("Invalid choice! Choose a position from 1 to 9.\n");
            continue;
        }

        if (!placeMark(board, move, currentToken)) {
            printf("Position %d is already taken! Try another.\n", move);
            continue;
        }

        // Check for win or draw
        if (checkWin(board, currentToken)) {
            printBoard(board);
            printf("🎉 Player %d (%c) wins!\n", turn + 1, currentToken);
            gameOver = true;
        } else if (isBoardFull(board)) {
            printBoard(board);
            printf("🤝 It's a draw!\n");
            gameOver = true;
        } else {
            // Switch turn (0 -> 1, 1 -> 0)
            turn = 1 - turn;
        }
    }

    return 0;
}