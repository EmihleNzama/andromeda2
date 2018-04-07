#include <QPainter>
#include <QTime>
#include "snake.h"

Snake::Snake(QWidget *parent) : QWidget(parent) {

    //constructor
    setStyleSheet("background-color:black;");
    leftDirection = false;
    rightDirection = true;//alwasys starts right
    upDirection = false;
    downDirection = false;
    inGame = true;//game should already be playing at run
    one = "rightDirection";
    //two = one;
    resize(B_WIDTH, B_HEIGHT);
    //QTime bt;
    loadImages();
    initGame();
}

void Snake::loadImages() {
    dot.load(":/images/dot.png");
    head.load(":/images/head.png");
    apple.load(":/images/apple.png");
}

void Snake::initGame() {
    //bt.start();
    dots = 3;//length of snake
//start of snake
    for (int z = 0; z < dots; z++) {//from head (z=0)
        x[z] = 200- z * 10;//position of snake, other part of the snake
        y[z] = 50;//position of snakebt.elapsed();
    }

    locateApple();//place apple on screen, randomley

    timerId = startTimer(DELAY);//everytimer has ID
}

void Snake::paintEvent(QPaintEvent *e) {

    Q_UNUSED(e);//#DEFINE Q_UNUSED(C++ code)

    doDrawing();
}

void Snake::doDrawing() {

    QPainter qp(this);//each painter knows where it is

    //paint only if we busy
    if (inGame) {

        qp.drawImage(apple_x, apple_y, apple);//draw image of apple

        //draw entire snake
        for (int z = 0; z < dots; z++) {
            if (z == 0) {
                qp.drawImage(x[z], y[z], head);
            } else {
                qp.drawImage(x[z], y[z], dot);
            }
        }

    } else {

        gameOver(qp);//when game is over(gmae over)
    }
}

void Snake::gameOver(QPainter &qp) {//*game over in how many seconds

    //runinS = QString::number(runin);
    QString message = "Game Over";
    //QString message = "Game Over";
    QFont font("Courier", 15, QFont::DemiBold);
    QFontMetrics fm(font);//do calculatio with the fint
    int textWidth = fm.width(message);//calculate width of font, to fit in screen

    qp.setFont(font);
    int h = height();//location of paint
    int w = width();

    //work from middle of window
    qp.translate(QPoint(w/2, h/2));
    qp.drawText(-textWidth/2, 0, message);//start of the text behind the middle
}

void Snake::checkApple() {//collided with apple o not

    if ((x[0] == apple_x) && (y[0] == apple_y)) {//head and apple on same coordinate

        dots++;//add body
        locateApple();//plant another apple
    }
}

void Snake::move() {//moving the head, in direction of keypress,rest of body move in order(seond move to last position of head etc.

    for (int z = dots; z > 0; z--) {//start from tail
        x[z] = x[(z - 1)];//move each to next position
        y[z] = y[(z - 1)];
    }
    goGetIt();
    //for head to follow the keys pressed
    if (leftDirection) {
        x[0] -= DOT_SIZE;
    }

    if (rightDirection) {
        x[0] += DOT_SIZE;
    }

    if (upDirection) {
        y[0] -= DOT_SIZE;
    }

    if (downDirection) {
        y[0] += DOT_SIZE;
    }
}


void Snake::checkCollision() {//if snake is dead

    for (int z = dots; z > 0; z--) {//check at any part of the body

        if ((z > 4) && (x[0] == x[z]) && (y[0] == y[z])) {//start at 4 cause impossible to bite neck below 3
            inGame = false;//end game
            //runin =(uint)bt.elapsed();
        }
    }

    //check if collision is with the window
    if (y[0] >= B_HEIGHT) {
        inGame = false;
        //runin = bt.elapsed();
    }

    if (y[0] < 0) {
        inGame = false;
       // runin = bt.elapsed();
    }

    if (x[0] >= B_WIDTH) {
        inGame = false;
        //runin = bt.elapsed();
    }

    if (x[0] < 0) {
        inGame = false;
        //runin = bt.elapsed();
    }

    if(!inGame) {
        killTimer(timerId);//stop the timer
    }
}

void Snake::locateApple() {//random position of apple

    QTime time = QTime::currentTime();
    qsrand((uint) time.msec());

    int r = qrand() % RAND_POS;//random position 0-29
    apple_x = (r * DOT_SIZE);//random x

    r = qrand() % RAND_POS;
    apple_y = (r * DOT_SIZE);//random y
}

void Snake::timerEvent(QTimerEvent *e) {

    Q_UNUSED(e);

    if (inGame) {

        checkApple();//if apple is eaten
        checkCollision();//if theres colision
        move();//continue moving
    }

    repaint();//change window graphics,repaint
}


void Snake::goGetIt(){

/*
    if(aboutToCollide()){
        if(one == "leftDirection"){upDirection = false;rightDirection= false;leftDirection =true;downDirection =false;}
        else if (one == "upDirection"){upDirection = true;rightDirection= false;leftDirection =false;downDirection =false;}
        else if (one == "downDirection"){upDirection = false;rightDirection= false;leftDirection =false;downDirection =true;}
        else{upDirection = false;rightDirection= true;leftDirection =false;downDirection =false;}
    }0) {

    else {*/

    if((x[0] > apple_x) && (rightDirection || leftDirection) ){
        if(y[0] < apple_y){
            upDirection = false;
            rightDirection= false;
            leftDirection =false;
            downDirection =true;

            if(rightDirection){
                one = "rightDirection";
            }else{
                one = "leftDirection";}
        }
        else{
            downDirection = false;
            upDirection = true;
            leftDirection = false;
            rightDirection = false;
        }

    }else if((x[0] < apple_x) && (rightDirection || leftDirection) ){
        if(y[0] < apple_y){
            upDirection = false;
            rightDirection= false;
            leftDirection =false;
            downDirection = true;
            if(rightDirection){
                one = "rightDirection";
            }else{
                one = "leftDirection";
            }

        }else{
            downDirection = false;
            upDirection = true;
            leftDirection = false;
            rightDirection = false;
        }

    }


    if((y[0] > apple_y) && (upDirection || downDirection) ){
        if(x[0] < apple_x){
            rightDirection= true;
            upDirection = false;
            leftDirection =false;
            downDirection =false;
            if(upDirection){
                one = "upDirection";
            }else{
                one = "downDirection";
            }

        }else{
            leftDirection = true;
            downDirection = false;
            upDirection = false;
            rightDirection = false;
        }

    }else if((y[0] < apple_y) && (upDirection || downDirection)){
        if(x[0] < apple_x){
            rightDirection= true;
            upDirection = false;
            leftDirection =false;
            downDirection =false;
            if(rightDirection){
                one = "upDirection";
            }else{
                one = "downDirection";
            }
        }else{
            leftDirection = true;
            downDirection = false;
            upDirection = false;
            rightDirection = false;
        }

    }



    if((x[0] == apple_x) && (y[0] < apple_y) && downDirection ){
        one = "downDirection";
        rightDirection = false;
        downDirection = true;
        upDirection = false;
        leftDirection = false;

    }else if((x[0] == apple_x) && (y[0] < apple_y) && upDirection){
        if(x[0] < 150){
            one = "upDirection";
            rightDirection = true;
            downDirection = false;//o
            upDirection = false;
            leftDirection = false;
        }else{
            one = "upDirection";
            rightDirection = false;
            downDirection = false;//o
            upDirection = false;
            leftDirection = true;
        }

    }else if ((x[0] == apple_x) && (y[0] < apple_y) && (rightDirection || leftDirection) ){
        rightDirection = false;
        downDirection = true;//o
        upDirection = false;
        leftDirection = false;
        if(leftDirection){
            one = "leftDirection";
        }else{
            one = "rightDirection";
        }
    }


    if((x[0] == apple_x) && (y[0] > apple_y) && upDirection ){
        one = "upDirection";
        rightDirection = false;
        downDirection = false;
        upDirection = true;
        leftDirection = false;

    }
    else if((x[0] == apple_x) && (y[0] > apple_y) && downDirection){
        if (x[0] < 150){
            one = "downDirection";
            rightDirection = true;
            downDirection = false;
            upDirection = false;//o
            leftDirection = false;
        }else{
            one = "downDirection";
            rightDirection = false;
            downDirection = false;
            upDirection = false;//o
            leftDirection = true;
        }

   }else if((x[0] == apple_x) && (y[0] > apple_y) && (rightDirection || leftDirection) ){
        rightDirection = false;
        downDirection = false;//o
        upDirection = true;
        leftDirection = false;
        if(leftDirection){
            one = "leftDirection";
        }else{
            one = "rightDirection";
        }

}
    /** Snake/ apple on the same y-axis, snake on the left of the apple,
     * snake towards left*/
    if((y[0] == apple_y) && (x[0] < apple_x) && leftDirection ){
        one = "leftDirection";
        if (y[0] < 150){
            rightDirection = false;
            downDirection = true;
            upDirection = false;
            leftDirection = false;
        }else{
            rightDirection = false;
            downDirection = false;
            upDirection = true;
            leftDirection = false;
        }


    }else if((y[0] == apple_y) && (x[0] < apple_x) && rightDirection){
        one = "rightDirection";
        rightDirection = true;//o
        downDirection = false;
        upDirection = false;
        leftDirection = false;

    }

    if((y[0] == apple_y) && (x[0] > apple_x) && rightDirection ){\
        one = "rightDirection";
        if (y[0] < 150){
            rightDirection = false;
            downDirection = true;
            upDirection = false;
            leftDirection = false;
        }else{
            rightDirection = false;
            downDirection = false;
            upDirection = true;
            leftDirection = false;
        }
    }else if((y[0] == apple_y) && (x[0] > apple_x) && leftDirection){
        one = "leftDirection";
        rightDirection = false;
        downDirection = false;
        upDirection = false;
        leftDirection = true;//o

    }

//}


























/**
    if((x[0] == 290)  && (y[0] == 0) && rightDirection==true){
        downDirection = true;
        rightDirection= false;
        leftDirection = false;
        upDirection = false;

    }
    if((x[0] == 290)  && (y[0] == 0) && upDirection==true){
        leftDirection = true;
        upDirection= false;
        downDirection = false;
        rightDirection = false;
    }
    if((x[0] == 0)  && (y[0] == 0) && leftDirection==true){
        downDirection = true;
        leftDirection= false;
        upDirection = false;
        rightDirection = false;
    }
    if((x[0] == 0)  && (y[0] == 0) && upDirection==true){
        rightDirection = true;
        upDirection= false;
        leftDirection = false;
        downDirection = false;
    }
    if((x[0] == 0)  && (y[0] == 290) && downDirection==true){
        rightDirection = true;
        downDirection= false;
        leftDirection = false;
        upDirection = false;
    }
    if((x[0] == 0)  && (y[0] == 290) && leftDirection==true){
        upDirection = true;
        leftDirection= false;
        rightDirection =false;
        downDirection=false;
    }
    if((x[0] == 290)  && (y[0] == 290) && rightDirection==true){
        upDirection = true;
        rightDirection= false;
        downDirection =false;
        leftDirection =false;
    }
    if((x[0] == 290)  && (y[0] == 290) && downDirection==true){
        leftDirection = true;
        downDirection= false;
        upDirection = false;
        rightDirection = false;
    }
    if((rightDirection) && (x[0] == 290)){
        downDirection = true;
        rightDirection = false;
        leftDirection =false;
        upDirection = false;

    }
    if((leftDirection) && (x[0] == 0)){
        downDirection = true;
        leftDirection = false;
        upDirection = false;
        rightDirection =false;

    }
    if((upDirection) && (y[0] == 0)){
        leftDirection = true;
        upDirection = false;
        downDirection =false;
        rightDirection =false;

    }
    if((downDirection) && (y[0] == 290)){
        rightDirection = true;
        downDirection = false;
        leftDirection =false;
        upDirection =false;

    }
**/



}



bool Snake::aboutToCollide(){
    for (int z = dots; z > 0; z--) {//check at any part of the body

        //if (((z > 4) && ((x[0] += DOT_SIZE) == x[z])) && (((y[0] +=DOT_SIZE) == y[z]) || (((x[0] -= DOT_SIZE) == x[z])) && ((y[0] -=DOT_SIZE) == y[z]))){//start at 4 cause impossible to bite neck below 3
        if( ((z>4) && (x[0]+=20 == x[z]) && (y[0] -= 20 == y[z])) || ((z >4) && (x[0] -= 20 == x[z]) && (y[0] += 20 == y[z])) )  {
            return true;//end game
            //runin =(uint)bt.elapsed();
        }

    }
    return false;
}
/*
void Snake::keyPressEvent(QKeyEvent *e) {

    int key = e->key();//key pressed in that event, e is a pointer, pointing to key pressed

    if ((key == Qt::Key_Left) && (!rightDirection)) {//continue in direction unless another buton pressed
        leftDirection = true;
        upDirection = false;
        downDirection = false;
    }

    if ((key == Qt::Key_Right) && (!leftDirection)) {
        rightDirection = true;
        upDirection = false;
        downDirection = false;
    }

    if ((key == Qt::Key_Up) && (!downDirection)) {
        upDirection = true;
        rightDirection = false;
        leftDirection = false;
    }0) {

    if ((key == Qt::Key_Down) && (!upDirection)) {
        downDirection = true;
        rightDirection = false;
        leftDirection = false;
    }

    QWidget::keyPressEvent(e);
}
*//*
if((x[0] > apple_x) && (downDirection) ){
    if(y[0] < apple_y){upDirection = false;rightDirection= true;leftDirection =false;downDirection =false;if(rightDirection){one = "rightDirection";}else{one = "leftDirection";}}
    else{downDirection = false;upDirection = false;leftDirection = true;rightDirection = false;}
}
else if((x[0] > apple_x) && (downDirection) ){
    if(y[0] < apple_y){upDirection = false;rightDirection= true;leftDirection =false;downDirection =false;if(rightDirection){one = "rightDirection";}else{one = "leftDirection";}}
    else{downDirection = false;upDirection = false;leftDirection = true;rightDirection = false;}
    }
else if(x[0] == apple_x && y[0] < apple_y && downDirection ){
    one = "downDirection";
    rightDirection = false;
    downDirection = false;
    upDirection = false;
    leftDirection = true;
}
else if((x[0] == apple_x) && (y[0] < apple_y) && !downDirection){
    one = "upDirection";
    rightDirection = false;
    downDirection = true;//o
    upDirection = false;
    leftDirection = false;
}


if((x[0] > apple_x) && (upDirection) ){
    if(y[0] < apple_y){upDirection = false;rightDirection= true;leftDirection =false;downDirection =false;if(rightDirection){one = "rightDirection";}else{one = "leftDirection";}}
    else{downDirection = false;upDirection = false;leftDirection = true;rightDirection = false;}
}
else if((x[0] > apple_x) && (upDirection) ){
    if(y[0] < apple_y){upDirection = false;rightDirection= true;leftDirection =false;downDirection =false;if(rightDirection){one = "rightDirection";}else{one = "leftDirection";}}
    else{downDirection = false;upDirection = false;leftDirection = true;rightDirection = false;}
}
else if(x[0] == apple_x && y[0] > apple_y && upDirection ){
    one = "upDirection";
    rightDirection = true;
    downDirection = false;
    upDirection = false;
    leftDirection = false;
}
else if((x[0] == apple_x) && (y[0] > apple_y) && !upDirection){
    one = "downDirection";
    rightDirection = false;
    downDirection = false;
    upDirection = true;//o
    leftDirection = false;
}


if((x[0] > apple_x) && (leftDirection) ){
    if(y[0] < apple_y){upDirection = true;rightDirection= false;leftDirection =false;downDirection =false;if(rightDirection){one = "rightDirection";}else{one = "leftDirection";}}
    else{downDirection = true;upDirection = false;leftDirection = false;rightDirection = false;}
}
else if((x[0] < apple_x) && (leftDirection) ){
    if(y[0] < apple_y){upDirection = true;rightDirection= false;leftDirection =false;downDirection =false;if(rightDirection){one = "rightDirection";}else{one = "leftDirection";}}
    else{downDirection = true;upDirection = false;leftDirection = false;rightDirection = false;}
}
else if(y[0] == apple_y && x[0] < apple_x && leftDirection ){
    one = "leftDirection";
    rightDirection = false;
    downDirection = false;
    upDirection = true;
    leftDirection = false;
}
else if((y[0] == apple_y) && (x[0] < apple_x) && !leftDirection){
    one = "rightDirection";
    rightDirection = true;//o
    downDirection = false;
    up0) {Direction = false;
    leftDirection = false;
}

if((x[0] > apple_x) && (rightDirection) ){
    if(y[0] < apple_y){upDirection = true;rightDirection= false;leftDirection =false;downDirection =false;if(rightDirection){one = "rightDirection";}else{one = "leftDirection";}}
    else{downDirection = true;upDirection = false;leftDirection = false;rightDirection = false;}
}
else if((x[0] < apple_x) && (rightDirection) ){
    if(y[0] < apple_y){upDirection = true;rightDirection= false;leftDirection =false;downDirection =false;if(rightDirection){one = "rightDirection";}else{one = "leftDirection";}}
    else{downDirection = true;upDirection = false;leftDirection = false;rightDirection = false;}
}
else if(y[0] == apple_y && x[0] > apple_x && rightDirection ){
    one = "rightDirection";
    rightDirection = false;
    downDirection = true;
    upDirection = false;
    leftDirection = false;
}
else if((y[0] == apple_y) && (x[0] > apple_x) && !rightDirection){
    one = "leftDirection";
    rightDirection = false;
    downDirection = false;
    upDirection = false;
    leftDirection = true;//o
}*/
