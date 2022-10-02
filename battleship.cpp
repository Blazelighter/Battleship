#include <iostream>
#include <array>
#include <stdlib.h>
#include <time.h>

using namespace std;

class Battleship {
    // Handles the length of a ship when being placed
    int shiplength;

    public:
    void setLength(int length) {
        shiplength = length;
    }
    void placeShip(char field[10][10]) {
        // randomly places the ship either vertically or horizontally 
        if (rand() % 2) {
            placeHorizontal(field);
        }
        else {
            placeVertical(field);
        }
    }
    void placeHorizontal(char field[10][10]) {
        // places the ship on the field horizontally ">" is used to denote how it was placed
        int x, y;
        x = rand() % (10 - shiplength);
        y = rand() % 10;
        for (int i = 0; i < shiplength; i++) {
            field[x + i][y] = '>';
        }
    }
    void placeVertical(char field[10][10]) {
        // places the ship on the field vertically "A" is used to denote how it was placed
        int x, y;
        x = rand() % 10;
        y = rand() % (10 - shiplength);
        for (int i = 0; i < shiplength; i++) {
            field[x][y + i] = 'A';
        }
    }
};

void placeShips(char field[10][10]) {
    // populate the array with ships
    Battleship ships[5];
    int i = 2;
    for (auto ship: ships) {
        ship.setLength(i);
        ship.placeShip(field);
        i++;
        if (i == 6)
            i = 3;
    }
}

bool checkForShips (char aMatrix[10][10]) {
    // checks if ships are still in the array
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (aMatrix[i][j] == 'A' || aMatrix[i][j] == '>') {
                return true;
            }
        }
    }
    return false;
}

void resetField(char aMatrix[10][10]) {
    // sets the field to be waves
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            aMatrix[i][j] = '~';
        }
    }
}

void printField(char aMatrix[10][10]) {
    // prints all the elements of a 10x10 array
    cout << "\n";
    cout << "   1 2 3 4 5 6 7 8 9 10\n";
    cout << "   ____________________\n";
    for (int i = 0; i < 10; i++) {
        if (i < 9) 
            cout << i + 1 << " |";
        else
            cout << i+ 1 << "|";
        for (int j = 0; j < 10; j++) {
            cout << aMatrix[j][i] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

int main() {

    srand (time(NULL));

    char enemyfield[10][10];
    char playerfield[10][10];
    int x, y;
    char keepPlaying;

    resetField(enemyfield);
    resetField(playerfield);

    placeShips(enemyfield);
    printField(playerfield);

    while (checkForShips(enemyfield)) {

        // Ask the player if they want to keep going
        cout << "Fire again? (y/n): \n";
        cin >> keepPlaying;
        if (keepPlaying == 'n' || keepPlaying == 'N') {
            break;
        }

        // get coordinates from player
        cout << "Choose X: ";
        cin >> x;
        cout <<"Choose Y: ";
        cin >> y;
        x--;
        y--;


        // check if player hit
        if (enemyfield[x][y] == 'A' || enemyfield[x][y] == '>'){
            // Hit
            enemyfield[x][y] = 'X';
            playerfield[x][y] = 'X';
            printField(playerfield);
            // printField(enemyfield); // uncomment this to show the enemy's board
            cout << "Hit!\n";
            
        }
        else {
            // Miss
            playerfield[x][y] = 'O';
            enemyfield[x][y] = 'O';
            printField(playerfield);
            // printField(enemyfield); // uncomment this to show the enemy's board
            cout << "Miss!\n";
        }

    }

    printField(playerfield);

    // Victory/Loss message
    if (!(keepPlaying == 'n' || keepPlaying == 'N')) {
        cout << "Congrats, You Win!\n";
    }
    else {
        cout << "Better luck next time.\n";
    }
    cout << "Thanks for playing!";
    return 0;
}