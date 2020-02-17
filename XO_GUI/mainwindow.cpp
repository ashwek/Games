#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vector>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {

    ui->setupUi(this);

    // initialize X & O board
    matrix = new int[9];
    for(int i = 0; i < 9; i++) matrix[i] = 0;

    // initialize variables
    movesPlayed = winner = youCount = computerCount = 0;
    gameFinished = false;

    ui->newGame->setVisible(false);
    ui->resetGame->setVisible(false);

    // randomly choose which player goes first
    // curPlayer = true, Your (Human / X) chance
    // curPlayer = false, Computers (O) chance
    srand(clock());
    curPlayer = rand() % 2;
    changeChanceLabel();

    // if its computers chance, generate a move
    if( ! curPlayer ){
        int result = computersMove();
        handleInput(getBlockFromPos(result), result);
    }

}


MainWindow::~MainWindow() {
    delete this->matrix;
    delete ui;
}


// On clicks for all the blocks in X & O board
// send the block object and the its position to handleInput method
void MainWindow::on_block0_clicked() { handleInput((MainWindow *)ui->block0, 0); }
void MainWindow::on_block1_clicked() { handleInput((MainWindow *)ui->block1, 1); }
void MainWindow::on_block2_clicked() { handleInput((MainWindow *)ui->block2, 2); }
void MainWindow::on_block3_clicked() { handleInput((MainWindow *)ui->block3, 3); }
void MainWindow::on_block4_clicked() { handleInput((MainWindow *)ui->block4, 4); }
void MainWindow::on_block5_clicked() { handleInput((MainWindow *)ui->block5, 5); }
void MainWindow::on_block6_clicked() { handleInput((MainWindow *)ui->block6, 6); }
void MainWindow::on_block7_clicked() { handleInput((MainWindow *)ui->block7, 7); }
void MainWindow::on_block8_clicked() { handleInput((MainWindow *)ui->block8, 8); }


// change top heading dislaying whose chance it is
void MainWindow::changeChanceLabel() {

    if( curPlayer )
        ui->chanceLabel->setText("Player X's chance");
    else
        ui->chanceLabel->setText("Computer's chance");

}


// handle input
void MainWindow::handleInput(MainWindow *block, int pos){

    /*
     * takes 2 parameters, block and pos
     * block is the pointer to the selected block
     * pos is the position of the block [0-8]
     */

    ui->newGame->setVisible(true);
    ui->resetGame->setVisible(true);

    // change block text, disable the button, increment the move count
    QPushButton *button = (QPushButton*)block;
    if( curPlayer ){
        button->setText("X");
        button->setStyleSheet("color: red");
    }
    else {
        button->setText("O");
        button->setStyleSheet("color: blue");
    }
    button->setEnabled(false);
    movesPlayed++;

    // make similar entry in the matrix
    matrix[pos] = curPlayer ? 1 : 2;

    // check if the game can still continue
    // checkGameState returns {-1, 0, 1, 2}
    // -1 : game can continue
    //  0 : game is draw
    //  1 : X won
    //  2 : O won
    winner = checkGameState();
    if( winner != -1 ){
        gameFinished = true;
        endGame();
    }
    else {
        // if games is not over, switch player
        curPlayer = ! curPlayer;
        changeChanceLabel();

        if( ! curPlayer && ! gameFinished ){

            // force UI (chanceLabel) refresh
            ui->chanceLabel->repaint();

            disableAllBlocks();
            sleep(1000);

            // generate move for computer
            int result = computersMove();
            handleInput(getBlockFromPos(result), result);

            enableEmptyBlocks();
        }

    }
}


// generate a move for computer
int MainWindow::computersMove(){

    // if this is the first move
    // generate a random number [0, 8]
    // else use minimax

    int temp;
    if( movesPlayed == 0 ){
        srand(clock());
        temp = rand() % 9;
    }
    else {
        temp = minimax(curPlayer, 10)[1];
    }
    return temp;

}


// get the block at a given position
MainWindow *MainWindow::getBlockFromPos(int pos){

    switch(pos){
        case 0: return (MainWindow*)ui->block0;
        case 1: return (MainWindow*)ui->block1;
        case 2: return (MainWindow*)ui->block2;
        case 3: return (MainWindow*)ui->block3;
        case 4: return (MainWindow*)ui->block4;
        case 5: return (MainWindow*)ui->block5;
        case 6: return (MainWindow*)ui->block6;
        case 7: return (MainWindow*)ui->block7;
        case 8: return (MainWindow*)ui->block8;
    }

    return NULL;

}


// check game state
int MainWindow::checkGameState(){

    // if less than 5 moves are player, there can be no winner
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


// end game processing
void MainWindow::endGame(){

    switch(winner){
        case 0:
            ui->chanceLabel->setText("Draw Game");
            break;
        case 1:
            youCount++;
            ui->chanceLabel->setText("Player X Won");
            break;
        case 2:
            computerCount++;
            ui->chanceLabel->setText("Computer Won");
            break;
    }

    ui->yourScore->setText("You : " + QString::number(youCount));
    ui->computerScore->setText("Computer : " + QString::number(computerCount));

    disableAllBlocks();
    paintWinnerTrack();

}


void MainWindow::disableAllBlocks(){

    for(int i = 0; i < 9; i++){
        ((QPushButton*)getBlockFromPos(i))->setEnabled(false);
    }

}


void MainWindow::enableEmptyBlocks(){

    for(int i = 0; i < 9; i++){
        QPushButton *button = (QPushButton *)getBlockFromPos(i);
        if( button->text().size() == 0 ){
            button->setEnabled(true);
        }
    }

}


void MainWindow::sleep(int miliSeconds){

    clock_t start = clock();
    clock_t end;
    clock_t CLOCKS_PER_MILI_SEC = CLOCKS_PER_SEC / 1000;

    do{
        end = clock();
    }while((end - start) < (miliSeconds * CLOCKS_PER_MILI_SEC));

}


std::vector<int> MainWindow::minimax(bool currentSimulatedPlayer, int depth) {

    std::vector<int> finalResult;

    for(int i = 0; i < 9; i++){

        if( matrix[i] != 0 ) continue;

        matrix[i] = (currentSimulatedPlayer ? 1 : 2);
        movesPlayed++;

        int result = checkGameState();
        std::vector<int> tempResult = std::vector<int>(2);

        if( result == -1 ) {
            tempResult = minimax(!currentSimulatedPlayer, depth - 1);
        }
        else {
            if( result == 0 ) tempResult[0] = 0;
            else tempResult[0] = depth * ((currentSimulatedPlayer == curPlayer) ? 1 : -1);
        }
        tempResult[1] = i;

        if( finalResult.size() <= 0 )
            finalResult = tempResult;

        if( curPlayer == currentSimulatedPlayer){
            finalResult = ( finalResult[0] < tempResult[0]) ? tempResult : finalResult;
        }
        else {
            finalResult = ( finalResult[0] > tempResult[0]) ? tempResult : finalResult;
        }

        matrix[i] = 0;
        movesPlayed--;

    }

    return finalResult;

}


void MainWindow::on_newGame_clicked() {

    for(int i = 0; i < 9; i++) matrix[i] = 0;

    movesPlayed = winner = 0;
    gameFinished = false;

    for(int i = 0; i < 9; i++){
        QPushButton *button = (QPushButton*)getBlockFromPos(i);
        button->setText("");
        button->setEnabled(true);
        button->setStyleSheet("");
    }

    ui->newGame->setVisible(false);

    srand(clock());
    curPlayer = rand() % 2;
    changeChanceLabel();

    if( ! curPlayer ){
        ui->chanceLabel->repaint();
        int result = computersMove();
        handleInput(getBlockFromPos(result), result);
    }

}


void MainWindow::on_resetGame_clicked() {

    youCount = computerCount = 0;

    ui->yourScore->setText("You : 0");
    ui->computerScore->setText("Computer : 0");

    ui->newGame->setVisible(false);
    ui->resetGame->setVisible(false);

    on_newGame_clicked();

}


// paint the winning set of blocks
void MainWindow::paintWinnerTrack(){

    // check rows
    for(int r = 0; r < 9; r += 3){
        if( matrix[r] != 0 &&
            matrix[r] == matrix[r + 1] && matrix[r] == matrix[r + 2] ){
                getBlockFromPos(r)->setStyleSheet("background-color: #000000; color: #ffffff");
                getBlockFromPos(r + 1)->setStyleSheet("background-color: #000000; color: #ffffff");
                getBlockFromPos(r + 2)->setStyleSheet("background-color: #000000; color: #ffffff");
            }
    }

    // check columns
    for(int c = 0; c < 3; c++){
        if( matrix[c] != 0 &&
            matrix[c] == matrix[c + 3] && matrix[c] == matrix[c + 6] ){
                getBlockFromPos(c)->setStyleSheet("background-color: #000000; color: #ffffff");
                getBlockFromPos(c + 3)->setStyleSheet("background-color: #000000; color: #ffffff");
                getBlockFromPos(c + 6)->setStyleSheet("background-color: #000000; color: #ffffff");
            }
    }

    // check diagonal 1
    if( matrix[0] != 0 &&
        matrix[0] == matrix[4] && matrix[0] == matrix[8] ){
            getBlockFromPos(0)->setStyleSheet("background-color: #000000; color: #ffffff");
            getBlockFromPos(4)->setStyleSheet("background-color: #000000; color: #ffffff");
            getBlockFromPos(8)->setStyleSheet("background-color: #000000; color: #ffffff");
    }

    // check diagonal 2
    if( matrix[2] != 0 &&
        matrix[2] == matrix[4] && matrix[2] == matrix[6] ){
        getBlockFromPos(2)->setStyleSheet("background-color: #000000; color: #ffffff");
        getBlockFromPos(4)->setStyleSheet("background-color: #000000; color: #ffffff");
        getBlockFromPos(6)->setStyleSheet("background-color: #000000; color: #ffffff");
    }

}
