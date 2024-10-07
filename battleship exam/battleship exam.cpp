#include <iostream>
#include <conio.h>
using namespace std;

const char SHIP = 'S';
const char HIT = 'H';
const char MISS = 'O';
const char EMPTY = '+';
const int boardsize = 10;

char player1Board[boardsize][boardsize];
char player2Board[boardsize][boardsize];

int player1Ships = 10;
int player2Ships = 10;

void board(char(*board)[boardsize]);  
void showBoard(char(*board)[boardsize], bool hideShips = true);
void placeShips(char(*board)[boardsize], int* ships);  
bool attack(char(*board)[boardsize], int row, int col);
void bot(char(*board)[boardsize], int* ships, int* lastRow, int* lastCol);  
void board(char(*board)[boardsize]) {  
    for (int i = 0; i < boardsize; i++) {
        for (int j = 0; j < boardsize; j++) {
            board[i][j] = EMPTY;
        }
    }
}

void showBoard(char(*board)[boardsize], bool hideShips) {
    for (int i = 0; i < boardsize; i++) {
        for (int j = 0; j < boardsize; j++) {
            if (board[i][j] == HIT) {
                cout << HIT << " ";
            }
            else if (board[i][j] == MISS) {
                cout << MISS << " ";
            }
            else if (hideShips && board[i][j] == SHIP) {
                cout << EMPTY << " ";
            }
            else {
                cout << board[i][j] << " ";
            }
        }
        cout << endl;
    }
}

void placeShips(char(*board)[boardsize], int* ships) {  
    srand(time(0));
    for (int i = 0; i < *ships; i++) {  
        int row, col;
        do {
            row = rand() % boardsize;
            col = rand() % boardsize;
        } while (board[row][col] == SHIP);
        board[row][col] = SHIP;
    }
}

bool attack(char(*board)[boardsize], int row, int col) {
    if (board[row][col] == SHIP) {
        board[row][col] = HIT;
        return true;
    }
    else if (board[row][col] == EMPTY) {
        board[row][col] = MISS;
        return false;
    }
    return false;
}

void bot(char(*board)[boardsize], int* ships, int* lastRow, int* lastCol) {  
    srand(time(0));
    int row, col;
    do {
        row = rand() % boardsize;
        col = rand() % boardsize;
    } while (board[row][col] == HIT || board[row][col] == MISS);

    bool hit = attack(board, row, col);

    *lastRow = row;  
    *lastCol = col;

    if (hit) {
        (*ships)--; 
        cout << "Player 2 HIT!" << endl;
    }
    else {
        cout << "Player 2 MISSED!" << endl;
    }
}
void gameIntro() {
    system("cls"); 
    cout << "-------------------------------------\n";
    cout << "|           WELCOME TO              |\n";
    cout << "|           BATTLE SHIP!!!          |\n";
    cout << "-------------------------------------\n";
    cout << "Qaydalar:" << endl;
    cout << "1. Taxta 10x10 olcudedir" << endl;
    cout << "2. Her ouncunun 10 gemisi var" << endl;
    cout << "3. Oyun bota qarsidir kordinatlarla gemileri vura bilersiniz" << endl;
    cout << "4. 'H' vurulan gemini, 'O' ise gemini qacirtdiginizi bildirir"<<endl;
    cout << "5. Botun 10 gemisini vurub qazanmaga calisin!!" << endl;
    cout << "-------------------------------------" << endl;
    cout << "DEVAM ETMEK UCUN ISTENILEN DUYMEYE BASIN!!!";
    _getch();  
}

int main() {
    gameIntro();
    int currentPlayer = 1;
    int row, col;
    bool gameWon = false;
    int lastRowP2 = -1, lastColP2 = -1;

    board(player1Board);
    board(player2Board);

    placeShips(player1Board, &player1Ships);  
    placeShips(player2Board, &player2Ships);  

    while (!gameWon) {
        system("cls");

        cout << "Player " << currentPlayer << "'s turn" << endl;

        if (currentPlayer == 1) {
            showBoard(player2Board);
            cout << "Enter coordinates (row and column): ";
            cin >> row >> col;

            if (row < 0 || row >= boardsize || col < 0 || col >= boardsize) {
                cout << "Invalid coordinates!" << endl;
                continue;
            }

            bool hit = attack(player2Board, row, col);
            if (hit) {
                player2Ships--;  
                cout << "Player 1 HIT a ship!" << endl;
            }
            else {
                cout << "Player 1 MISSED!" << endl;
            }

            if (player2Ships == 0) {
                cout << "Player 1 WINS!" << endl;
                gameWon = true;
            }

        }
        else {
            showBoard(player1Board, true);

            bot(player1Board, &player1Ships, &lastRowP2, &lastColP2);  

            if (player1Ships == 0) {
                cout << "Player 2 WINS!" << endl;
                gameWon = true;
            }
        }

        currentPlayer = (currentPlayer == 1) ? 2 : 1;

        if (!gameWon) {
            cout << "DEVAM ETMEK UCUN ISTENILEN DUYMEYE BASIN!!!";
            _getch();
            if (currentPlayer == 1) {
                showBoard(player1Board, true);
            }
        }
    }

    return 0;
}