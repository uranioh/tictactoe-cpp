#include <iostream>
using namespace std;

// cls = windows
// clear = unix

const int fieldSize = 3;
char gameMatrix[fieldSize][fieldSize];


void resetField() {
    for (int i=0; i<fieldSize; i++) {
        for (int j=0; j<fieldSize; j++) {
            gameMatrix[i][j] = ' ';
        }
    }
}


void showField() {
    cout << endl;
    cout << "   0   1   2" << endl;
    for (int i=0; i<fieldSize; i++) {
        cout << i << " ";
        for (int j=0; j<fieldSize; j++) {
            cout << "[" << gameMatrix[i][j] << "] ";
        }
        cout << endl;
    }
}

void clearScreen() {
    // cls = windows
    // clear = unix
    system("clear");
}

bool insertChar(char player, int row, int col) {
    // check empty section
    if (row >= 0 && row < 3 && col >= 0 && col < 3) {
        if (gameMatrix[row][col] == ' ') {
                if (player == 'x' || player == 'o') {
                    gameMatrix[row][col] = player;
                    return true;
                }
                else {
                    cout << "Carattere non valido.";
                    return false;
                }
        }
        else {
                cout << "La casella non e' vuota.";
                return false;
        }
    }
    else {
        cout << "Coordinate non valide.";
        return false;
    }
}


char checkWinner() {
    char winner;
    for (int i=0; i<fieldSize; i++) {
        if (gameMatrix[i][0] == gameMatrix[i][1] && gameMatrix[i][0] == gameMatrix[i][2]) {
            if (gameMatrix[i][0] != ' ') {
                winner = gameMatrix[i][0];
                break;
            }
            else winner = 'n';
        }
        else if (gameMatrix[0][i] == gameMatrix[1][i] && gameMatrix[0][i] == gameMatrix[2][i]) {
            if (gameMatrix[0][i] != ' ') {
                winner = gameMatrix[0][i];
                break;
            }
            else winner = 'n';
        }
        else {
            winner = 'n';
        }
    }
    return winner;
}


int main() {
    int gameStatus = 0;
    char currentPlayer = 'x';
    int row; int col;

    clearScreen();
    resetField();
    while (gameStatus == 0) {
        showField();

        cout << "Turno del giocatore "
             << "[" << currentPlayer << "]"
             << endl;

        cout << "Inserisci la riga: ";
        cin >> row;
        cout << "Inserisci la colonna: ";
        cin >> col;



        if (insertChar(currentPlayer, row, col)) {
            if (currentPlayer == 'x') {
                currentPlayer = 'o';
            }
            else {
                currentPlayer = 'x';
            }
        }

        if (checkWinner() != 'n') {
            cout << "Il giocatore [" << checkWinner() << "] vince!" << endl;
            gameStatus = 1;
        }
        else {
            clearScreen();
        }
    }
    return 0;
}