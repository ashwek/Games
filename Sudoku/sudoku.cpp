#include <iostream>

using namespace std;

// int matrix[9][9] = {{5, 3, 0, 0, 7, 0, 0, 0, 0},
//                     {6, 0, 0, 1, 9, 5, 0, 0, 0},
//                     {0, 9, 8, 0, 0, 0, 0, 6, 0},
//                     {8, 0, 0, 0, 6, 0, 0, 0, 3},
//                     {4, 0, 0, 8, 0, 3, 0, 0, 1},
//                     {7, 0, 0, 0, 2, 0, 0, 0, 6},
//                     {0, 6, 0, 0, 0, 0, 2, 8, 0},
//                     {0, 0, 0, 4, 1, 9, 0, 0, 5},
//                     {0, 0, 0, 0, 8, 0, 0, 7, 9}};

int matrix[9][9] = {{0, 0, 0, 0, 0, 9, 8, 0, 0},
                    {0, 1, 8, 4, 0, 0, 0, 2, 0},
                    {0, 0, 4, 0, 7, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 6, 0, 0, 0},
                    {6, 0, 0, 3, 0, 0, 0, 5, 0},
                    {0, 0, 0, 1, 8, 0, 7, 0, 2},
                    {0, 5, 1, 8, 0, 0, 0, 9, 3},
                    {9, 7, 0, 0, 3, 0, 0, 0, 4},
                    {0, 3, 0, 0, 6, 0, 0, 0, 0}};

// int matrix[9][9] = {{0, 2, 0, 0, 0, 4, 3, 0, 0},
//                     {9, 0, 0, 0, 2, 0, 0, 0, 8},
//                     {0, 0, 0, 6, 0, 9, 0, 5, 0},
//                     {0, 0, 0, 0, 0, 0, 0, 0, 1},
//                     {0, 7, 2, 5, 0, 3, 6, 8, 0},
//                     {6, 0, 0, 0, 0, 0, 0, 0, 0},
//                     {0, 8, 0, 2, 0, 5, 0, 0, 0},
//                     {1, 0, 0, 0, 9, 0, 0, 0, 3},
//                     {0, 0, 9, 8, 0, 0, 0, 6, 0}};

bool bruteForce(int row, int col);
bool validEntry(int num, int row, int col);
bool existsInRow(int num, int row);
bool existsInColumn(int num, int col);
bool existsInSubGrid(int num, int row, int col);
void display();

int main(){

    cout << "Input Matrix : \n";
    display();

    clock_t start = clock();

    bruteForce(0, 0);

    clock_t end = clock();

    cout <<"\n\nTime taken : " <<((float)(end - start)) / CLOCKS_PER_SEC << " seconds";

    cout << "\nSolved Matrix : \n";
    display();

    return 0;

}

bool bruteForce(int row, int col){

    if( col >= 9 ){
        col = 0;
        row++;
    }

    if( row >= 9 )
        return true;

    if( matrix[row][col] != 0 )
        return bruteForce(row, col + 1);

    for(int n = 1; n <= 9; n++){
        if( validEntry(n, row, col) ){
            matrix[row][col] = n;
            if( bruteForce(row, col + 1) )
                return true;
            matrix[row][col] = 0;
        }
    }

    return false;

}

bool validEntry(int num, int row, int col){

    return (! existsInRow(num, row)) &&
            (! existsInColumn(num, col)) &&
            (! existsInSubGrid(num, row, col));

}

bool existsInRow(int num, int row){

    for(int i = 0; i < 9; i++){
        if( matrix[row][i] == num) return true;
    }
    return false;

}

bool existsInColumn(int num, int col){

    for(int i = 0; i < 9; i++){
        if( matrix[i][col] == num) return true;
    }
    return false;

}

bool existsInSubGrid(int num, int row, int col){

    for(int i = 3 * (row / 3); i < 3 * ((row / 3) + 1); i++){
        for(int j = 3 * (col / 3); j < 3 * ((col / 3) + 1); j++){
            if( matrix[i][j] == num) return true;
        }
    }

    return false;

}

void display(){

    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            cout << matrix[i][j] <<" ";
        }
        cout <<endl;
    }

}
