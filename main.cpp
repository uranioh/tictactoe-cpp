#include <iostream>
using namespace std;

// definisco la dimensione del campo di gioco
const int fieldSize = 3;
char gameMatrix[fieldSize][fieldSize];


// reset del campo di gioco
void resetField() {
    for (int i=0; i < fieldSize; i++) {
        for (int j=0; j < fieldSize; j++) {
            gameMatrix[i][j] = ' ';
        }
    }
}


// mostro il campo di gioco a schermo
void showField() {
    cout << "   0   1   2" << endl;
    for (int i=0; i < fieldSize; i++) {
        cout << i << " ";
        for (int j=0; j < fieldSize; j++) {
            cout << "[" << gameMatrix[i][j] << "] ";
        }
        cout << endl;
    }
}


// clear della console
void clearScreen() {
    // windows = "cls"
    // unix-like = "clear"
    system("clear");
}

// inserimento del carattere nelle caselle
bool insertChar(char player, int row, int col) {
    bool returnStatus = false;
    // parametri invalidi:

    // righe e colonne valide: 0, 1, 2
    if (row >= 0 && row < fieldSize && col >= 0 && col < fieldSize) {
        // controllo se dove l'utente vuole posizionare una x/o è libero
        if (gameMatrix[row][col] == ' ') {
            gameMatrix[row][col] = player;
            returnStatus = true;
        }
        else {
            cout << "La casella non e' vuota." << endl;
        }
    }
    else {
        cout << "Coordinate non valide." << endl;
    }

    return returnStatus;
}


// controllo dei vincitori / stato di gioco generale
char checkWinner() {
    // n = none
    // d = draw
    // x = vince il giocatore x
    // o = vince il giocatore o
    char winner = 'n';
    for (int i=0; i < fieldSize; i++) {

        // controllo se le righe sono uguali
        if (gameMatrix[i][0] == gameMatrix[i][1] && gameMatrix[i][0] == gameMatrix[i][2]) {
            if (gameMatrix[i][0] != ' ') {
                winner = gameMatrix[i][0];
            }
        }

        // controllo se le colonne sono uguali
        else if (gameMatrix[0][i] == gameMatrix[1][i] && gameMatrix[0][i] == gameMatrix[2][i]) {
            if (gameMatrix[0][i] != ' ') {
                winner = gameMatrix[0][i];
            }
        }
    }

    if (gameMatrix[1][1] != ' ') {
        // diagonale da sinistra a destra
        if (gameMatrix[0][0] == gameMatrix[1][1] && gameMatrix[0][0] == gameMatrix[2][2]) {
            winner = gameMatrix[1][1];
        }

        // diagonale da destra a sinistra
        if (gameMatrix[0][2] == gameMatrix[1][1] && gameMatrix[0][2] == gameMatrix[2][0]) {
            winner = gameMatrix[1][1];
        }
    }

    // controllo situazione di pareggio
    int placedCount = 0;
    for (int i=0; i < fieldSize; i++) {
        for (int j=0; j < fieldSize; j++) {
            if (gameMatrix[i][j] != ' ') {
                placedCount++;
            }
        }
    }

    if (placedCount == 9) {
        winner = 'd';
    }

    return winner;
}


int main() {
    int gameStatus = 0;
    char currentPlayer = 'x';
    int row, col;

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

        clearScreen();
        // verifico se il giocatore x compie una mossa valida
        // se sì passo al giocatore o, altrimenti faccio ripetere la mossa e viceversa
        if (insertChar(currentPlayer, row, col)) {
            if (currentPlayer == 'x') {
                currentPlayer = 'o';
            }
            else {
                currentPlayer = 'x';
            }
        }

        // condizione di vincita:
        // se il char di return della funzione checkWinner è diverso da N significa che
        // sarà x oppure o, di conseguenza qualcuno ha vinto.
        if (checkWinner() != 'n') {
            clearScreen();
            showField();

            if (checkWinner() != 'd') {
                cout << "Il giocatore [" << checkWinner() << "] vince!" << endl;
            }
            else {
                cout << "La partita si conclude in pareggio." << endl;
            }

            gameStatus = 1;
        }
    }
    
    return 0;
}