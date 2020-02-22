#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// QPushButton
#include <QtWidgets/QPushButton>
#include <string>

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QPushButton *buttonArray[81];
    int activeButton = -1;
    int matrix[9][9];

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    bool bruteForce(int row, int col);
    bool validEntry(int num, int row, int col);
    bool existsInRow(int num, int row);
    bool existsInColumn(int num, int col);
    bool existsInSubGrid(int num, int row, int col);
    QString getCSS(int row, int col);

public slots:
    void gridClick(int);
    void handleEntry(int);

private slots:
    void on_resetButton_clicked();
    void on_solveButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
