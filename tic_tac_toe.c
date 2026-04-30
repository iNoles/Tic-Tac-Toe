#include <stdio.h>
#include <stdbool.h>

#define SIZE 3

// ---------------------------
// Game State Enum
// ---------------------------
typedef enum {
    GAME_CONTINUE,
    GAME_X_WINS,
    GAME_O_WINS,
    GAME_TIE
} GameState;

// ---------------------------
// Print Board
// ---------------------------
void printBoard(char board[SIZE][SIZE]) {
    printf("\n");
    printf("    0   1   2\n");
    printf("  -------------\n");

    for (int i = 0; i < SIZE; i++) {
        printf("%d |", i);
        for (int j = 0; j < SIZE; j++) {
            printf(" %c |", board[i][j]);
        }
        printf("\n  -------------\n");
    }
    printf("\n");
}

// ---------------------------
// Check Valid Move
// ---------------------------
bool isValidMove(char board[SIZE][SIZE], int row, int col) {
    if (row < 0 || row >= SIZE || col < 0 || col >= SIZE)
        return false;
    if (board[row][col] != ' ')
        return false;
    return true;
}

// ---------------------------
// Make Move
// ---------------------------
void makeMove(char board[SIZE][SIZE], int row, int col, char symbol) {
    board[row][col] = symbol;
}

// ---------------------------
// Player Move (forced valid)
// ---------------------------
void playerMove(char board[SIZE][SIZE], char symbol) {
    int row, col;

    while (1) {
        printf("Enter row and column: ");
        scanf("%d %d", &row, &col);

        if (isValidMove(board, row, col)) {
            makeMove(board, row, col, symbol);
            return;
        }

        printf("Invalid move — that spot is taken or out of bounds.\n");
    }
}

// ---------------------------
// Computer Move (simple AI)
// ---------------------------
void computerMove(char board[SIZE][SIZE]) {
    // Simple AI: first available cell
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = 'O';
                return;
            }
        }
    }
}

// ---------------------------
// Game Over Check
// ---------------------------
GameState gameOver(char board[SIZE][SIZE]) {
    // Check rows and columns
    for (int i = 0; i < SIZE; i++) {
        // Row
        if (board[i][0] != ' ' &&
            board[i][0] == board[i][1] &&
            board[i][1] == board[i][2]) {
            return (board[i][0] == 'X') ? GAME_X_WINS : GAME_O_WINS;
        }

        // Column
        if (board[0][i] != ' ' &&
            board[0][i] == board[1][i] &&
            board[1][i] == board[2][i]) {
            return (board[0][i] == 'X') ? GAME_X_WINS : GAME_O_WINS;
        }
    }

    // Diagonal TL → BR
    if (board[0][0] != ' ' &&
        board[0][0] == board[1][1] &&
        board[1][1] == board[2][2]) {
        return (board[0][0] == 'X') ? GAME_X_WINS : GAME_O_WINS;
    }

    // Diagonal TR → BL
    if (board[0][2] != ' ' &&
        board[0][2] == board[1][1] &&
        board[1][1] == board[2][0]) {
        return (board[0][2] == 'X') ? GAME_X_WINS : GAME_O_WINS;
    }

    // Check for tie (board full)
    bool full = true;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == ' ') {
                full = false;
                break;
            }
        }
        if (!full) break;
    }

    if (full) return GAME_TIE;

    return GAME_CONTINUE;
}

// ---------------------------
// Main
// ---------------------------
int main() {
    char board[SIZE][SIZE] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };

    int mode;
    printf("Choose mode:\n1. Player vs Player\n2. Player vs Computer\n");
    scanf("%d", &mode);

    bool player1Turn = true;
    GameState state = GAME_CONTINUE;

    while (state == GAME_CONTINUE) {
        printBoard(board);

        if (player1Turn) {
            printf("Player 1 (X) move:\n");
            playerMove(board, 'X');
        } else {
            if (mode == 1) {
                printf("Player 2 (O) move:\n");
                playerMove(board, 'O');
            } else {
                printf("Computer (O) move:\n");
                computerMove(board);
            }
        }

        player1Turn = !player1Turn;
        state = gameOver(board);
    }

    printBoard(board);

    switch (state) {
        case GAME_X_WINS:
            printf("Player 1 (X) wins!\n");
            break;

        case GAME_O_WINS:
            if (mode == 1)
                printf("Player 2 (O) wins!\n");
            else
                printf("Computer (O) wins!\n");
            break;

        case GAME_TIE:
            printf("It's a tie!\n");
            break;

        default:
            break;
    }

    return 0;
}
