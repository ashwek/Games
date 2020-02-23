#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>

using namespace std;


// game variables
int *matrix, movesPlayed, endStatus;
bool curPlayer, gameFinished;


void initializeGame();
void displayMatrix();
bool validMove(int row, int col);
void input(int row, int col);
int checkGameState();
void endGame();
int computersMove();
vector<int> minimax(bool, int);
void sleep(int);


int main(){

    int row, col;

    initializeGame();

    while( ! gameFinished ){

        system("clear");
        displayMatrix();

        do{

            cout <<" *** " <<(curPlayer ? "X" : "Computer's") <<"'s Chance ***" <<flush;

            if( curPlayer ){
                cout <<"\nEnter row = ";
                cin >> row;
                cout <<"Enter col = ";
                cin >> col;
            }
            else {
                int temp = computersMove();
                row = temp / 3;
                col = temp % 3;
                cout <<"\nEnter row = " <<flush;
                sleep(600);
                cout <<row <<"\nEnter col = " <<flush;
                sleep(600);
                cout <<col <<"\n" <<flush;
            }

            if( validMove(row, col) ){
                input(row, col);
                break;
            }
            else {
                cout << "\n\n >>> Invalid Move <<<\n\n";
            }

        }while( 1 );

        int result = checkGameState();
        if( result != -1 ){
            gameFinished = true;
            endStatus = result;
        }
        else {
            curPlayer = ! curPlayer;
        }

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

}


// check if someone has won the game or not
int checkGameState(){

    if( movesPlayed <= 4 )
        return -1;

    // check rows
    for(int r = 0; r < 9; r += 3){
        if( matrix[r] != 0 &&
            matrix[r] == matrix[r + 1] && matrix[r] == matrix[r + 2] ){
                return matrix[r];
            }
    }

    // check columns
    for(int c = 0; c < 3; c++){
        if( matrix[c] != 0 &&
            matrix[c] == matrix[c + 3] && matrix[c] == matrix[c + 6] ){
                return matrix[c];
            }
    }

    // check diagonal 1
    if( matrix[0] != 0 &&
        matrix[0] == matrix[4] && matrix[0] == matrix[8] ){
            return matrix[0];
    }

    // check diagonal 2
    if( matrix[2] != 0 &&
        matrix[2] == matrix[4] && matrix[2] == matrix[6] ){
            return matrix[2];
    }

    // check draw
    if( movesPlayed == 9){
        return 0;
    }

    return -1;

}


// end message
void endGame(){

    system("clear");
    displayMatrix();

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

    int temp;

    if( movesPlayed == 0 ){
        srand(clock());
        temp = rand() % 9;
    }
    else {
        vector<int> result = minimax(curPlayer, 10);
        temp = result[1];
    }

    return temp;

}


vector<int> minimax(bool currentSimulatedPlayer, int depth) {

    vector<int> finalResult;

    for(int i = 0; i < 9; i++){

        if( matrix[i] != 0 ) continue;

        matrix[i] = (currentSimulatedPlayer ? 1 : 2);
        movesPlayed++;

        int result = checkGameState();
        vector<int> tempResult = vector<int>(2);

        if( result == -1 ) {
            tempResult = minimax(!currentSimulatedPlayer, depth - 1);
        }
        else {
            if( result == 0 ) tempResult[0] = 0;
            else tempResult[0] = depth * ((currentSimulatedPlayer == curPlayer) ? 1 : -1);
        }
        tempResult[1] = i;

        matrix[i] = 0;
        movesPlayed--;

        if( finalResult.size() <= 0 )
            finalResult = tempResult;

        if( curPlayer == currentSimulatedPlayer){
            finalResult = ( finalResult[0] < tempResult[0]) ? tempResult : finalResult;
            if( finalResult[0] == depth ) break;
        }
        else {
            finalResult = ( finalResult[0] > tempResult[0]) ? tempResult : finalResult;
            if( finalResult[0] == -depth ) break;
        }

    }

    return finalResult;

}


void sleep(int miliSeconds){

    clock_t start = clock();
    clock_t end;
    clock_t CLOCKS_PER_MILI_SEC = CLOCKS_PER_SEC / 1000;

    do{
        end = clock();
    }while((end - start) < (miliSeconds * CLOCKS_PER_MILI_SEC));

}
