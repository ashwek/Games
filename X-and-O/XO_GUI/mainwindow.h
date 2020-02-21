#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    bool curPlayer, gameFinished;
    int *matrix, movesPlayed, winner;
    int youCount, computerCount;

private slots:

    void on_block0_clicked();
    void on_block1_clicked();
    void on_block2_clicked();
    void on_block3_clicked();
    void on_block4_clicked();
    void on_block5_clicked();
    void on_block6_clicked();
    void on_block7_clicked();
    void on_block8_clicked();
    void on_newGame_clicked();
    void on_resetGame_clicked();

    void changeChanceLabel();
    void handleInput(MainWindow *, int pos);
    MainWindow *getBlockFromPos(int);
    int computersMove();
    int checkGameState();
    void endGame();
    void disableAllBlocks();
    void enableEmptyBlocks();
    void sleep(int);
    std::vector<int> minimax(bool, int);
    void paintWinnerTrack();

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
