#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QTimer>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QPoint>
#include <QMainWindow>
#include <QPushButton>
#include <QTimer>
#include <QTextEdit>
#include <QKeyEvent>
#include <QDebug>
#include <QObject>
#include <vector>
#include <iostream>
#include <QTime>
#include <fstream>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QTimer*timer;
    QTimer*timer1;
    int timerId;
    bool inGame;
    string whichOne;


protected://these methods are overriden
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);//what to do everytime,timer calls paint(*count the apples(variable keeps track of apples eaten))
    void keyPressEvent(QKeyEvent *);
    //void resizeEvent(QResizeEvent* evt) override;


private:
    Ui::MainWindow *ui;
    QGraphicsScene*scene;
    //QGraphicsScene* stage2;
    //QGraphicsScene* stage3;
    //QGraphicsScene*gameOverScene;
    //QGraphicsPixmapItem*ball;
    QGraphicsPixmapItem* dot;//body
    QGraphicsPixmapItem* background1;
    QGraphicsPixmapItem* head;
    QGraphicsPixmapItem* apple;
    QGraphicsPixmapItem* number;
    //QGraphicsPixmapItem* poo;
    QTime bt;
    QGraphicsTextItem* line2;


    vector<QGraphicsPixmapItem*> gdots;
    vector<QGraphicsPixmapItem*> poo;
    vector<QGraphicsPixmapItem*> topO;
    vector<QGraphicsPixmapItem*> bottomO;
    //array<QGraphicsPixmapItem*> gdots [400];
    int steps=0;
    bool off;
    //int okay;
    int hr,mn,sc;
    string control;
    string robot;

    QPushButton *button;
    fstream readit;
    fstream writeit;

//dimnsions of the game
      static const int B_WIDTH = 300;
      static const int B_HEIGHT = 300;
      static const int DOT_SIZE = 10;//dot size, moving by it
      static const int ALL_DOTS = 900;//greatest number of dots we could have,due to dimensions
      static const int RAND_POS = 29;
      static const int DELAY = 50;//*question answered



      int duration;
      int apples;
//timer, application stopwatch
      //methed called start
      int dots;//how long snak is
      int apple_x;
      int apple_y;
      int num_apple;
      int obs;
      int obs1;
      int obs2;

      int runin;
      int runinS;
      //int ui;
      int front_x;
      int front_y;
      int left_x;
      int left_y;
      int right_x;
      int right_y;
      int aboutto;


      string one;
      //QString line1;
      string line;
      string temp;
      string previous;
      int two;
      int three;
      int four;
      int five;
      int moveOn = 14;
      int nextX = 0;
      int nextY = 0;
      int stage;


      //arrays,worste case scenario
      //0 is always the head
      int x[ALL_DOTS];//BOTH: stores biggest snake possible
      int y[ALL_DOTS];
      int xobs[20];
      int yobs[20];
      int xobs2[20];
      int yobs2[20];


      //where the hell is this snake going,disable snake eating itself
      bool leftDirection;
      bool rightDirection;
      bool upDirection;
      bool downDirection;

      bool west;
      bool east;
      bool north;
      bool south;

      bool alreadyClicked = true;

      bool what;
      bool playingGame = true;

      //interface
      void loadImages();
      void countDown();
      void numberpic(int a);
      void chaseTheSnake();
      void initGame();//set everything up
      void locateApple();//put apple on screen
      void checkApple();//if we eaten it
      void checkCollision();//1. wall 2. beaten itslef
      void move();//everydot moves one position
      void doDrawing();//draws whole snake
      void gameOver(QPainter &);
      void goGetIt();
      bool aboutToCollide();
private slots:
    void tick();
    void pause();


    void on_checkBox_clicked();

    void on_checkBox_3_clicked();

    void on_checkBox_2_clicked();

public slots:
    void startGame();

};

#endif // MAINWINDOW_H
