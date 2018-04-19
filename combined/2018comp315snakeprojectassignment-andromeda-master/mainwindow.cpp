#include <QApplication>
#include <QPainter>
#include <QTime>
#include "snake.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <sstream>
#include <string>

using namespace std ;

MainWindow::MainWindow(QWidget *parent) ://contructor(mainwindow function belongs to main window class)
    QMainWindow(parent),//0 by default
    ui(new Ui::MainWindow)//ui = to what is inside(initialize constant attributes)
{
    ui->setupUi(this);//sets everything bases on properties(fonts,allignements etc)
    timer = new QTimer(this);//pointer, empty

    connect(timer, SIGNAL(timeout()), this, SLOT(tick()));//macro(connect(define connect)shortend code)1.source of timer 2.signal(timeout) 3.find this object 4.when this timer starts start another event(macros(Signal,slot))
    off = true;//timer is off now
    hr = 0, mn = 0, sc = 0;
    button = new QPushButton(this);//everytime we drag something in design
    button->setFixedSize(100,40);
    ui->verticalLayout->addWidget(button,0,Qt::AlignHCenter);
    //everytime button is clicked
    connect(button,SIGNAL(clicked()),this, SLOT(pause()));
    connect(button,SIGNAL(clicked()), this, SLOT(openNewWindow()));
    //properties of the button
    button->setIcon(QIcon("./play.ico"));
    button->setIconSize(QSize(100,40));//icon diff size fro m button
}

MainWindow::~MainWindow()
{
    delete ui;//delete everything in the heirarchy
}

void MainWindow::tick(){

    if(timer->isActive()){

        sc++;
        if(sc==60){
            mn++;
            sc=0;
        }
        if(mn==60){
            hr++;
            mn=0;
        }
        if(hr==24)
            hr=0;

        std::stringstream ss;//concatenate strings and numbers
        if(hr<10)
            ss<<0<<hr<<":";//single digits add a
        else
            ss<<hr<<":";
        if(mn<10)
            ss<<0<<mn<<":";
        else
            ss<<mn<<":";
        if(sc<10)
            ss<<0<<sc;
        else
            ss<<sc;
        QString qs(ss.str().c_str());//go to label you draged and drop and put this
        ui->label->setText(qs);
    }
}

void MainWindow::pause(){
    if(off){
        timer->start(1000);
        off=!off;
        button->setIcon(QIcon("./pause.ico"));
        button->setIconSize(QSize(100,40));
    }
    else{
        if(timer->isActive()){
            timer->stop();
            button->setIcon(QIcon("./play.ico"));
            button->setIconSize(QSize(100,40));
        }
        else{
            timer->start(1000);
            button->setIcon(QIcon("./pause.ico"));
            button->setIconSize(QSize(100,40));
        }
    }
}


void MainWindow::openNewWindow()
{
    this->close();
    Snake *game = new Snake;
    game->show();
    //game->inGame = false;



}

