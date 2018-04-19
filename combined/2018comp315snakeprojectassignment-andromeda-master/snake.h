#ifndef SNAKE_H
#define SNAKE_H

#include <QWidget>
#include <QKeyEvent>
#include <bits/stdc++.h>
#include "mainwindow.h"
#include <QTime>
using namespace std;
//widget is a window we creating, snake inherits qtwidget
class Snake : public QWidget {

  public:
      Snake(QWidget *parent = 0);//multiple windows point to one, close one close all
      int timerId;
      bool inGame;

  protected://these methods are overriden
      void paintEvent(QPaintEvent *);
      void timerEvent(QTimerEvent *);//what to do everytime,timer calls paint(*count the apples(variable keeps track of apples eaten))
      void keyPressEvent(QKeyEvent *);

  private://members of the class
      QImage dot;//body
      QImage head;
      QImage apple;
      QTime bt;

//dimnsions of the game
      static const int B_WIDTH = 300;
      static const int B_HEIGHT = 300;
      static const int DOT_SIZE = 10;//dot size, moving by it
      static const int ALL_DOTS = 900;//greatest number of dots we could have,due to dimensions
      static const int RAND_POS = 29;
      static const int DELAY = 75;//*question answered

//timer, application stopwatch
      //methed called start
      int dots;//how long snak is
      int apple_x;
      int apple_y;
      int num_apple;

      int runin;
      int runinS;
      int ui;
      int front_x;
      int front_y;
      int left_x;
      int left_y;
      int right_x;
      int right_y;
      int aboutto;

      string one;
      string temp;
      string previous;
      int two;
      int three;
      int four;
      int five;

      //arrays,worste case scenario
      //0 is always the head
      int x[ALL_DOTS];//BOTH: stores biggest snake possible
      int y[ALL_DOTS];

      //where the hell is this snake going,disable snake eating itself
      bool leftDirection;
      bool rightDirection;
      bool upDirection;
      bool downDirection;

      bool what;
      bool playingGame = true;

      //interface
      void loadImages();
      void initGame();//set everything up
      void locateApple();//put apple on screen
      void checkApple();//if we eaten it
      void checkCollision();//1. wall 2. beaten itslef
      void move();//everydot moves one position
      void doDrawing();//draws whole snake
      void gameOver(QPainter &);
      void goGetIt();
      bool aboutToCollide();
};
#endif // SNAKE_H
