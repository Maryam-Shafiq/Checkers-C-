#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class Piece {
public:
    char symbol;
    bool isKing;
    Piece(char sym) : symbol(sym), isKing(false) {}
};

class Checkers {
private:
    Piece* board[8][8];
    char player1Symbol, player2Symbol;
    int player1Count, player2Count;
    bool player1Turn;

public:
    Checkers() {
        player1Symbol = '#';
        player2Symbol = '@';
        player1Count = 12;
        player2Count = 12;
        player1Turn = true;
        initializeBoard();
    }

    void initializeBoard() {
        // Initialize empty board
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                board[i][j] = NULL;
            }
        }

        // Set up player 1 pieces
        for (int i = 0; i < 3; ++i) {
            for (int j = (i % 2); j < 8; j += 2) {
                board[i][j] = new Piece(player1Symbol);
            }
        }

        // Set up player 2 pieces
        for (int i = 5; i < 8; ++i) {
            for (int j = (i % 2); j < 8; j += 2) {
                board[i][j] = new Piece(player2Symbol);
            }
        }
    }

    void displayBoard() {
        cout << "  +---+---+---+---+---+---+---+---+\n";
        for (int i = 0; i < 8; ++i) {
            cout << i + 1 << " | ";
            for (int j = 0; j < 8; ++j) {
                if (board[i][j] == NULL) {
                    cout << "  | ";
                } else {
                    cout << board[i][j]->symbol << (board[i][j]->isKing ? 'K' : ' ') << " | ";
                }
            }
            cout << "\n  +---+---+---+---+---+---+---+---+\n";
        }
        cout << "    A   B   C   D   E   F   G   H  \n";
    }

    void playerMove() {
        string pos;
        cout << "\nPlayer (" << (player1Turn ? player1Symbol : player2Symbol) << ") Turn...." << endl;
        cout << "Enter the position of your piece (e.g., A6): ";
        cin >> pos;

        int x = pos[0] - 'A';
        int y = pos[1] - '1';

        if (!isValidPosition(x, y) || board[y][x] == NULL || board[y][x]->symbol != (player1Turn ? player1Symbol : player2Symbol)) {
            cout << "Invalid position. Try again." << endl;
            return;
        }

        int dir;
        cout << "Which direction?" << endl;
        cout << "1: Upper Left, 2: Upper Right, 3: Lower Left, 4: Lower Right" << endl;
        cin >> dir;

        if (!movePiece(y, x, dir)) {
            cout << "Invalid move. Try again." << endl;
            return;
        }

        if (player1Count == 0 || player2Count == 0) {
            declareWinner();
        } else {
            player1Turn = !player1Turn;
        }
    }

    bool isValidPosition(int x, int y) {
        return x >= 0 && x < 8 && y >= 0 && y < 8;
    }

    bool movePiece(int y, int x, int dir) {
        int dy, dx;
        if (dir == 1) { dy = -1; dx = -1; }
        else if (dir == 2) { dy = -1; dx = 1; }
        else if (dir == 3) { dy = 1; dx = -1; }
        else if (dir == 4) { dy = 1; dx = 1; }
        else { return false; }

        int ny = y + dy, nx = x + dx;
        if (!isValidPosition(nx, ny) || board[ny][nx] != NULL) {
            return false;
        }

        board[ny][nx] = board[y][x];
        board[y][x] = NULL;

        if ((player1Turn && ny == 7) || (!player1Turn && ny == 0)) {
            board[ny][nx]->isKing = true;
        }

        return true;
    }

    void declareWinner() {
        if (player1Count > player2Count) {
            cout << "Player 1 (" << player1Symbol << ") wins!" << endl;
        } else if (player2Count > player1Count) {
            cout << "Player 2 (" << player2Symbol << ") wins!" << endl;
        } else {
            cout << "It's a draw!" << endl;
        }
    }
};

int main() {
    Checkers game;
    while (true) {
        game.displayBoard();
        game.playerMove();
    }
    return 0;
}