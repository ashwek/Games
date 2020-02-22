#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <string>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {

    ui->setupUi(this);

    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){

            matrix[i][j] = 0;

            buttonArray[i * 9 + j] = new QPushButton(this);
            buttonArray[i * 9 + j]->setGeometry(10 + (50 * j), 10 + (50 * i), 50, 50);
            buttonArray[i * 9 + j]->setStyleSheet(getCSS(i, j));

            const int loc = i * 9 + j;
            connect(buttonArray[loc], &QPushButton::clicked, [this, loc]{ gridClick(loc); });

        }
    }

    int i = 0;
    connect(ui->entryOne, &QPushButton::clicked, [this, i]{ handleEntry(1); });
    connect(ui->entryTwo, &QPushButton::clicked, [this, i]{ handleEntry(2); });
    connect(ui->entryThree, &QPushButton::clicked, [this, i]{ handleEntry(3); });
    connect(ui->entryFour, &QPushButton::clicked, [this, i]{ handleEntry(4); });
    connect(ui->entryFive, &QPushButton::clicked, [this, i]{ handleEntry(5); });
    connect(ui->entrySix, &QPushButton::clicked, [this, i]{ handleEntry(6); });
    connect(ui->entrySeven, &QPushButton::clicked, [this, i]{ handleEntry(7); });
    connect(ui->entryEight, &QPushButton::clicked, [this, i]{ handleEntry(8); });
    connect(ui->entryNine, &QPushButton::clicked, [this, i]{ handleEntry(9); });
    connect(ui->entryClear, &QPushButton::clicked, [this, i]{ handleEntry(-1); });

}


MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::gridClick(int i){

    if( activeButton != -1 ){
        buttonArray[activeButton]->setStyleSheet(getCSS(activeButton / 9, activeButton % 9));
    }

    if( activeButton == i ){
        buttonArray[activeButton]->setStyleSheet(getCSS(activeButton / 9, activeButton % 9));
        activeButton = -1;
    }
    else {
        activeButton = i;
        buttonArray[activeButton]->setStyleSheet("background-color: #fdf77c");
    }

}


void MainWindow::handleEntry(int entry){

    if( activeButton != -1 ){
        if( entry == -1 ){
            buttonArray[activeButton]->setText("");
            matrix[activeButton / 9][activeButton % 9] = 0;
        }
        else{
            buttonArray[activeButton]->setText(QString::number(entry));
            matrix[activeButton / 9][activeButton % 9] = entry;
        }
    }

}


void MainWindow::on_resetButton_clicked() {

    activeButton = -1;

    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){

            matrix[i][j] = 0;

            buttonArray[i * 9 + j]->setText("");
            buttonArray[i * 9 + j]->setStyleSheet(getCSS(i, j));

        }
    }

}


void MainWindow::on_solveButton_clicked() {

    bruteForce(0, 0);

    activeButton = -1;

    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){

            buttonArray[i * 9 + j]->setText(QString::number(matrix[i][j]));
            buttonArray[i * 9 + j]->setStyleSheet(getCSS(i, j));

        }
    }

}

bool MainWindow::bruteForce(int row, int col){

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

bool MainWindow::validEntry(int num, int row, int col){

    return (! existsInRow(num, row)) &&
            (! existsInColumn(num, col)) &&
            (! existsInSubGrid(num, row, col));

}

bool MainWindow::existsInRow(int num, int row){

    for(int i = 0; i < 9; i++){
        if( matrix[row][i] == num) return true;
    }
    return false;

}

bool MainWindow::existsInColumn(int num, int col){

    for(int i = 0; i < 9; i++){
        if( matrix[i][col] == num) return true;
    }
    return false;

}

bool MainWindow::existsInSubGrid(int num, int row, int col){

    for(int i = 3 * (row / 3); i < 3 * ((row / 3) + 1); i++){
        for(int j = 3 * (col / 3); j < 3 * ((col / 3) + 1); j++){
            if( matrix[i][j] == num) return true;
        }
    }

    return false;

}


QString MainWindow::getCSS(int i, int j){

    int startBlock = (((i/3)*3)*9) + ((j/3)*3);

    switch(startBlock){
        case 0:
        case 6:
        case 30:
        case 54:
        case 60:
            return "background-color: #a6a6ed";
        default:
            return "";
    }

}
