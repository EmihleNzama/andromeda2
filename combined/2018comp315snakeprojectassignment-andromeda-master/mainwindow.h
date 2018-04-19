#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QPushButton>
#include<QTimer>
#include <QTextEdit>
#include <QMainWindow>
#include "snake.h"

namespace Ui {
class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    //openNewWindow(Snake *game);
    ~MainWindow();
    QTimer *timer;
private:
    Ui::MainWindow *ui;
    bool off;
    //int okay;
    int hr,mn,sc;
    QPushButton *button;
private slots:
    void tick();
    void pause();
    //void on_pushButton_clicked();

public slots:
    void openNewWindow();
};

#endif // MAINWINDOW_H
