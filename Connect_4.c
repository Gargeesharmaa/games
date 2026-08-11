#include <stdio.h>
#include <stdbool.h>

#define ROWS 6
#define COLS 7

// Initialize the board with empty spaces
void initBoard(char board[ROWS][COLS]) {
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            board[r][c] = ' ';
        }
    }
}

// Display the current state of the board
void printBoard(char board[ROWS][COLS]) {
    printf("\n");
    for (int r = 0; r < ROWS; r++) {
        printf("|");
        for (int c = 0; c < COLS; c++) {
            printf(" %c |", board[r][c]);
        }
        printf("\n");
    }
    printf("-----------------------------\n");
    printf("  1   2   3   4   5   6   7  \n\n");
}

// Drop a piece into a column. Returns the row index or -1 if column is full.
int dropPiece(char board[ROWS][COLS], int col, char token) {
    for (int r = ROWS - 1; r >= 0; r--) {
        if (board[r][col] == ' ') {
            board[r][col] = token;
            return r;
        }
    }
    return -1; // Column is full
}

// Check if the board is completely full
bool isBoardFull(char board[ROWS][COLS]) {
    for (int c = 0; c < COLS; c++) {
        if (board[0][c] == ' ') {
            return false;
        }
    }
    return true;
}

// Check if the latest move resulted in 4-in-a-row
bool checkWin(char board[ROWS][COLS], int row, int col, char token) {
    // 1. Horizontal Check ( - )
    int count = 0;
    for (int c = 0; c < COLS; c++) {
        if (board[row][c] == token) {
            count++;
            if (count == 4) return true;
        } else {
            count = 0;
        }
    }

    // 2. Vertical Check ( | )
    count = 0;
    for (int r = 0; r < ROWS; r++) {
        if (board[r][col] == token) {
            count++;
            if (count == 4) return true;
        } else {
            count = 0;
        }
    }

    // 3. Positive Diagonal Check ( / )
    count = 0;
    for (int r = ROWS - 1; r >= 3; r--) {
        for (int c = 0; c <= COLS - 4; c++) {
            if (board[r][c] == token &&
                board[r - 1][c + 1] == token &&
                board[r - 2][c + 2] == token &&
                board[r - 3][c + 3] == token) {
                return true;
            }
        }
    }

    // 4. Negative Diagonal Check ( \ )
    for (int r = 0; r <= ROWS - 4; r++) {
        for (int c = 0; c <= COLS - 4; c++) {
            if (board[r][c] == token &&
                board[r + 1][c + 1] == token &&
                board[r + 2][c + 2] == token &&
                board[r + 3][c + 3] == token) {
                return true;
            }
        }
    }

    return false;
}

int main() {
    char board[ROWS][COLS];
    initBoard(board);

    char players[2] = {'X', 'O'};
    int turn = 0;
    bool gameOver = false;

    printf("===============================\n");
    printf("     WELCOME TO CONNECT 4      \n");
    printf("===============================\n");

    while (!gameOver) {
        printBoard(board);
        char currentToken = players[turn];
        int col;

        printf("Player %d (%c), enter column (1-7): ", turn + 1, currentToken);
        if (scanf("%d", &col) != 1) {
            // Clear invalid non-integer input
            while (getchar() != '\n');
            printf("Invalid input! Please enter a number between 1 and 7.\n");
            continue;
        }

        col--; // Convert 1-indexed input to 0-indexed column

        // Input validation
        if (col < 0 || col >= COLS) {
            printf("Invalid column! Choose between 1 and 7.\n");
            continue;
        }

        int rowPlaced = dropPiece(board, col, currentToken);
        if (rowPlaced == -1) {
            printf("Column %d is full! Pick another column.\n", col + 1);
            continue;
        }

        // Check victory or tie
        if (checkWin(board, rowPlaced, col, currentToken)) {
            printBoard(board);
            printf("🎉 Congratulations! Player %d (%c) wins!\n", turn + 1, currentToken);
            gameOver = true;
        } else if (isBoardFull(board)) {
            printBoard(board);
            printf("🤝 It's a draw! The board is full.\n");
            gameOver = true;
        } else {
            // Switch player (0 -> 1, 1 -> 0)
            turn = 1 - turn;
        }
    }

    return 0;
}