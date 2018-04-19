
#include <QApplication>
#include "snake.h"
//#include "snakeC.h"
#include <iostream>
#include "mainwindow.h"
using namespace std ;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Snake window;//contructore
    MainWindow window;
    //window.setWindowTitle("Snake");//title to snake(at the top)
    window.show();

    return a.exec();
}
