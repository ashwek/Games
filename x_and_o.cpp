#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;


// game variables
int *matrix, movesPlayed, endStatus;
bool curPlayer, gameFinished;


void initializeGame();
void displayMatrix();
bool validMove(int row, int col);
void input(int row, int col);
void checkGameState();
void endGame();
int computersMove();
void sleep(int);


int main(){

    int row, col;

    initializeGame();

    while( ! gameFinished ){

        system("clear");
        displayMatrix();

        do{

            cout <<" *** " <<(curPlayer ? "X" : "Computer's") <<"'s Chance ***" <<flush;

            if( curPlayer){
                cout <<"\nEnter row = ";
                cin >> row;
                cout <<"Enter col = ";
                cin >> col;
            }
            else {
                sleep(800);
                int temp = computersMove();
                row = temp / 3;
                col = temp % 3;
            }

            if( validMove(row, col) ){
                input(row, col);
                break;
            }
            else {
                cout << "\n\n >>> Invalid Move <<<\n\n";
            }

        }while( 1 );

    }

    endGame();

    return 0;

}


// Initialize all game variables
void initializeGame(){

    movesPlayed = 0;
    gameFinished = false;

    srand(time(NULL));
    curPlayer = (rand() % 2);

    free(matrix);
    matrix = new int[9];
    for(int r = 0; r < 3; r++){
        for(int c = 0; c < 3; c++){
            matrix[r * 3 + c] = 0;
        }
    }

}


// display game matrix
void displayMatrix(){

    string displayCharacter = " XO";

    for(int r = 0; r < 3; r++){
        for(int c = 0; c < 3; c++){
            cout << displayCharacter[matrix[r * 3 + c]];
            if( c != 2 )
                cout << " | ";
        }
        cout << "\n";
        if( r != 2 )
            cout<< "- + - + -\n";
    }

}


// check if an input move is valid or not
bool validMove(int row, int col){

    return ( row >= 0 && row <= 2 &&
        col >=0 && col <= 2 &&
        matrix[row * 3 + col] == 0 );

}


void input(int row, int col){

    movesPlayed++;
    matrix[row * 3 + col] = (curPlayer ? 1 : 2);

    checkGameState();

    if( ! gameFinished ){
        curPlayer = ! curPlayer;
    }

}


// check if someone has won the game or not
void checkGameState(){

    if( movesPlayed <= 4 )
        return;

    // check rows
    for(int r = 0; r < 9; r += 3){
        if( matrix[r] != 0 &&
            matrix[r] == matrix[r + 1] && matrix[r] == matrix[r + 2] ){
                gameFinished = true;
                endStatus = matrix[r];
                return;
            }
    }

    // check columns
    for(int c = 0; c < 3; c++){
        if( matrix[c] != 0 &&
            matrix[c] == matrix[c + 3] && matrix[c] == matrix[c + 6] ){
                gameFinished = true;
                endStatus = matrix[c];
                return;
            }
    }

    // check diagonal 1
    if( matrix[0] != 0 &&
        matrix[0] == matrix[4] && matrix[0] == matrix[8] ){
            gameFinished = true;
            endStatus = matrix[0];
            return;
    }

    // check diagonal 2
    if( matrix[2] != 0 &&
        matrix[2] == matrix[4] && matrix[2] == matrix[6] ){
            gameFinished = true;
            endStatus = matrix[2];
            return;
    }

    // check draw
    if( movesPlayed == 9){
        gameFinished = true;
        endStatus = 0;
    }

}


// end message
void endGame(){

    switch( endStatus ){
        case 0:
            cout << "\n\nDraw Game\n\n";
            break;
        case 1:
            cout << "\n\nPlayer X won\n\n";
            break;
        case 2:
            cout << "\n\nComputer won\n\n";
            break;
    }

}


// generate move for computer
int computersMove(){

    srand(clock());
    int temp;
    do {
        temp = rand() % 9;
    }while (! validMove(temp / 3, temp % 3));

    return temp;

}


void sleep(int miliSeconds){

    clock_t start = clock();
    clock_t end;
    clock_t CLOCKS_PER_MILI_SEC = CLOCKS_PER_SEC / 1000;

    do{
        end = clock();
    }while((end - start) < (miliSeconds * CLOCKS_PER_MILI_SEC));

}
