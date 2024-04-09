#include <stdio.h>
#include <stdbool.h>

// Function to print the Tic Tac Toe board
void printBoard(char board[3][3]) {
    printf("\n-------------\n");
    for (int i = 0; i < 3; i++) {
        printf("| ");
        for (int j = 0; j < 3; j++) {
            printf("%c | ", board[i][j]);
        }
        printf("\n-------------\n");
    }
}

// Function to check if the game is over
bool gameOver(char board[3][3]) {
    // Check rows, columns, and diagonals for a win
    for (int i = 0; i < 3; i++) {
        if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            return true; // Row win
        }
        if (board[0][i] != ' ' && board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
            return true; // Column win
        }
    }
    if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        return true; // Diagonal win (top-left to bottom-right)
    }
    if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        return true; // Diagonal win (top-right to bottom-left)
    }

    // Check for a tie (board full)
    bool tie = true;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                tie = false;
                break;
            }
        }
        if (!tie) break;
    }
    if (tie) return true;

    // If none of the above conditions are met, game is not over
    return false;
}

// Function to check if a move is valid
bool isValidMove(char board[3][3], int row, int col) {
    if (row < 0 || row >= 3 || col < 0 || col >= 3) {
        return false;
    }
    if (board[row][col] != ' ') {
        return false;
    }
    return true;
}

// Function to perform a move
void makeMove(char board[3][3], int row, int col, char player) {
    board[row][col] = player;
}

int main() {
    char board[3][3] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };
    bool player1Turn = true;

    while (!gameOver(board)) {
        printBoard(board);
        int row, col;
        if (player1Turn) {
            printf("Player 1's turn (X): ");
        } else {
            printf("Player 2's turn (O): ");
        }
        scanf("%d %d", &row, &col);

        if (isValidMove(board, row, col)) {
            if (player1Turn) {
                makeMove(board, row, col, 'X');
            } else {
                makeMove(board, row, col, 'O');
            }
            player1Turn = !player1Turn; // Switch turns
        } else {
            printf("Invalid move! Please try again.\n");
        }
    }

    printBoard(board);
    if (gameOver(board)) {
        if (player1Turn) {
            printf("Player 2 (O) wins!\n");
        } else {
            printf("Player 1 (X) wins!\n");
        }
    } else {
        printf("It's a tie!\n");
    }

    return 0;
}
