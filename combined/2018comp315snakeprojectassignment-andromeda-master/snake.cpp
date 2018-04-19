#include <QPainter>
#include <QTime>
#include "snake.h"
#include "mainwindow.h"

Snake::Snake(QWidget *parent) : QWidget(parent) {

    //constructor
    setStyleSheet("background-color:grey;");
    leftDirection = false;
    rightDirection = true;//alwasys starts right
    upDirection = false;
    downDirection = false;
    temp = "rightDirection";
    previous = temp;
    inGame = true;//game should already be playing at run
    one = "rightDirection";
    //two = one;
    resize(B_WIDTH, B_HEIGHT);
    QTime bt;
    loadImages();
    initGame();
}

void Snake::loadImages() {
    dot.load(":/images/dot.png");
    head.load(":/images/head.png");
    apple.load(":/images/apple.png");
}

void Snake::initGame() {
    bt.start();
    dots = 15;//length of snake
    num_apple = 0;

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
    QString message = "Game Over "+ QString::number(bt.elapsed()/1000) + " Seconds "+QString::number(num_apple)+ " Apples eaten!";
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
        num_apple++;

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
        front_x = x[0] - 10;
        left_x = x[0];
        left_y = y[0] + 10;
        right_x = x[0];
        right_y = y[0] -10;
    }

    if (rightDirection) {
        x[0] += DOT_SIZE;
        front_x = x[0] + 10;
        left_x = x[0];
        left_y = y[0] - 10;
        right_x = x[0];
        right_y = y[0] +10;
    }

    if (upDirection) {
        y[0] -= DOT_SIZE;
        front_y = y[0] - 10;
        left_x = x[0] - 10;
        left_y = y[0];
        right_x = x[0] + 10;
        right_y = y[0];
    }

    if (downDirection) {
        y[0] += DOT_SIZE;
        front_y = y[0] + 10;
        left_x = x[0] + 10;
        left_y = y[0];
        right_x = x[0] - 10;
        right_y = y[0];
    }
}


void Snake::checkCollision() {//if snake is dead
    aboutto = 0;
    two = 0;
    three = 0;
    four = 0;
    five = 0;
    for (int z = dots; z > 0; z--) {//check at any part of the body

        if ((z > 4) && (x[0] == x[z]) && (y[0] == y[z])) {//start at 4 cause impossible to bite neck below 3
            inGame = false;//end game
            //runin =(uint)bt.elapsed();
        }
        if((z > 4) && (front_x == x[z]) && (front_y == y[z])){
            aboutto = 1;
        }
        if((z > 4) && (left_x == x[z]) && (left_y == y[z])){
            two = 1;
        }
        if((z > 4) && (right_x == x[z]) && (right_y == y[z])){
            two = 1;
        }
        if((z > 4) && (right_x == apple_x) && (right_y == apple_y)){
            three = 1;
        }
        if((z > 4) && (left_x == apple_x) && (left_y == apple_y)){
            three = 1;
        }
        //body on the right but there is no body on the left
        if((z > 4) && ((left_x != x[z]) && (left_y != y[z]))  && ((right_x == x[z]) && (right_y == y[z])) &&( ((left_x == apple_x) && (left_y < apple_y)) || ((left_y == apple_y) && (left_x < apple_x)))){

            four = 1;
        }
        //body on the left but there is no body on the right
        else if((z > 4) && ((left_x == x[z]) && (left_y == y[z])) && ((right_x != x[z]) && (right_y != y[z])) &&( ((right_x == apple_x) && (right_y > apple_y)) || ((right_y == apple_y) && (right_x > apple_x))  ) ){

            five = 1;
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
    apple_x =(r * DOT_SIZE);//random x

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

    if(aboutto == 1){

        if(previous == "leftDirection"){upDirection = false;rightDirection= false;leftDirection =true;downDirection =false;}
        else if (previous == "upDirection"){upDirection = true;rightDirection= false;leftDirection =false;downDirection =false;}
        else if (previous == "downDirection"){upDirection = false;rightDirection= false;leftDirection =false;downDirection =true;}
        else if(previous == "rightDirection"){upDirection = false;rightDirection= true;leftDirection =false;downDirection =false;}
        if(one != temp){

            previous = temp;
            temp = one;
        }
        aboutto = 0;
    }
    else if((four == 1 || five == 1) || two ==1){
        return;
    }

    else {

    /* snake is on the right of the apple, snake is moving horizintally and snake is above the apple*/
    if((x[0] > apple_x) && (rightDirection ) && (y[0] < apple_y) ){

        upDirection = false;
        rightDirection= false;
        leftDirection =false;
        downDirection =true;
        one = "downDirection";



        /* snake is on the right of the apple, snake is moving horizintally and snake is below the apple*/
     }else if( (x[0] > apple_x) && (rightDirection) && (y[0] > apple_y) ){

            downDirection = false;
            upDirection = true;
            leftDirection = false;
            rightDirection = false;
            one = "upDirection";

     /* snake is on the left of the apple, snake is moving horizintally and snake is above the apple*/
     }else if((x[0] < apple_x) && ( leftDirection) && (y[0] < apple_y) ){

            upDirection = false;
            rightDirection= false;
            leftDirection =false;
            downDirection = true;
            one = "downDirection";

      }else if ((x[0] < apple_x) && ( leftDirection) && (y[0] > apple_y) ){

            downDirection = false;
            upDirection = true;
            leftDirection = false;
            rightDirection = false;
            one ="upDirection";

        }

    if(one != temp){
        previous = temp;
        temp = one;
    }


    /* snake is on the left of apple and above apple , moving vertically */
    if((x[0] < apple_x) && (y[0] < apple_y) && (upDirection) ){

            rightDirection= true;
            upDirection = false;
            leftDirection =false;
            downDirection =false;
            one = "rightDirection";

    /* snake is on the left of apple and below apple , moving vertically */
     }else if ((x[0] < apple_x) && (y[0] > apple_y) && (downDirection) ){

            leftDirection = false;
            downDirection = false;
            upDirection = false;
            rightDirection = true;
            one = "rightDirection";

    /* snake is on the right of apple and above apple , moving vertically */
    }else if((x[0] > apple_x) && (upDirection) && (y[0] < apple_y)){

            rightDirection= false;
            upDirection = false;
            leftDirection =true;
            downDirection =false;
            one = "leftDirection";

    /* snake is on the right of apple and below apple , moving vertically */
     }else if((x[0] > apple_x) && (downDirection) && (y[0] > apple_y)){

            leftDirection = true;
            downDirection = false;
            upDirection = false;
            rightDirection = false;
            one = "leftDirection";


    }


    if(one != temp){
        previous = temp;
        temp = one;
    }

    /*same x-axis, snake is above the apple, snake moving downward */
    if((x[0] == apple_x) && (y[0] < apple_y) && downDirection ){

        rightDirection = false;
        downDirection = true;
        upDirection = false;
        leftDirection = false;
        one = "downDirection";
    /* same x-axis, snake is above apple, snake is moving upward*/
    }else if((x[0] == apple_x) && (y[0] < apple_y) && upDirection){

        if(x[0] < 150){
            rightDirection = true;
            downDirection = false;//o
            upDirection = false;
            leftDirection = false;
            one = "rightDirection";
        }else{

            rightDirection = false;
            downDirection = false;//o
            upDirection = false;
            leftDirection = true;
            one = "leftDirection";
        }

    /* same x-axis, snake is above apple, moving horizontally*/
    }else if ((x[0] == apple_x) && (y[0] < apple_y) && (rightDirection || leftDirection) ){
        rightDirection = false;
        downDirection = true;//o
        upDirection = false;
        leftDirection = false;
        one = "downDirection";
    }

    if(one != temp){
        previous = temp;
        temp = one;
    }

    /* same x-axis , snake is below apple , moving upwards*/
    if((x[0] == apple_x) && (y[0] > apple_y) && upDirection ){

        rightDirection = false;
        downDirection = false;
        upDirection = true;
        leftDirection = false;
        one = "upDirection";

    }/* same x-axis , snake is below apple , moving downwards*/
    else if((x[0] == apple_x) && (y[0] > apple_y) && downDirection){

        if (x[0] < 150){
            rightDirection = true;
            downDirection = false;
            upDirection = false;//o
            leftDirection = false;
            one = "rightDirection";
        }else{

            rightDirection = false;
            downDirection = false;
            upDirection = false;
            leftDirection = true;
            one = "leftDirection";
        }
    /* same x-axis , snake is below apple , moving horizontally*/
   }else if((x[0] == apple_x) && (y[0] > apple_y) && (rightDirection || leftDirection) ){

        rightDirection = false;
        downDirection = false;//o
        upDirection = true;
        leftDirection = false;
        one = "upDirection";


}
    if(one != temp){
        previous = temp;
        temp = one;
    }
    /** Snake/ apple on the same y-axis, snake on the left of the apple,
     * snake towards left*/
    if((y[0] == apple_y) && (x[0] < apple_x) && leftDirection ){

        if (y[0] < 150){
            rightDirection = false;
            downDirection = true;
            upDirection = false;
            leftDirection = false;
            one = "downDirection";
        }else{
            rightDirection = false;
            downDirection = false;
            upDirection = true;
            leftDirection = false;
            one = "upDirection";
        }

    /* same y-axis , snake is on the left of apple , moving towards apple (right)*/
    }else if((y[0] == apple_y) && (x[0] < apple_x) && rightDirection){

        rightDirection = true;//o
        downDirection = false;
        upDirection = false;
        leftDirection = false;
        one = "rightDirection";

    }
    /* same y-axis , snake is on the right of apple , moving away from apple (right)*/
    else if((y[0] == apple_y) && (x[0] > apple_x) && rightDirection ){\

        if (y[0] < 150){
            rightDirection = false;
            downDirection = true;
            upDirection = false;
            leftDirection = false;
            one = "downDirection";
        }else{
            rightDirection = false;
            downDirection = false;
            upDirection = true;
            leftDirection = false;
            one = "upDirection";
        }
    /* same y-axis , snake is on the right of apple , moving towards apple (left)*/
    }else if((y[0] == apple_y) && (x[0] > apple_x) && leftDirection){

        rightDirection = false;
        downDirection = false;
        upDirection = false;
        leftDirection = true;//o
        one = "leftDirection";

    }else if((y[0] == apple_y) && (x[0]<apple_x) && (upDirection || downDirection)){

        rightDirection = true;
        downDirection = false;
        upDirection = false;
        leftDirection = false;
        one = "rightDirection";


    }else if((y[0] == apple_y) && (x[0]>apple_x) && (upDirection || downDirection)){

         rightDirection = false;
         downDirection = false;
         upDirection = false;
         leftDirection = true;//o
         one = "leftDirection";
    }
    if(one != temp){
        previous = temp;
        temp = one;
    }


}


























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



//bool Snake::aboutToCollide(){
//    for (int z = dots; z > 0; z--) {//check at any part of the body

//        //if (((z > 4) && ((x[0] += DOT_SIZE) == x[z])) && (((y[0] +=DOT_SIZE) == y[z]) || (((x[0] -= DOT_SIZE) == x[z])) && ((y[0] -=DOT_SIZE) == y[z]))){//start at 4 cause impossible to bite neck below 3
//        if( ((z>4) && (x[0]+=20 == x[z]) && (y[0] -= 20 == y[z])) || ((z >4) && (x[0] -= 20 == x[z]) && (y[0] += 20 == y[z])) )  {
//            return true;//end game
//            //runin =(uint)bt.elapsed();
//        }

//    }
//    return false;
//}

void Snake::keyPressEvent(QKeyEvent *e) {

    int key = e->key();//key pressed in that event, e is a pointer, pointing to key pressed

    if ((key == Qt::Key_Space)) {
        if(playingGame){
            killTimer(timerId);
            playingGame = false;
        }
        else{
            timerId = startTimer(DELAY);
            playingGame = true;
        }
    }

    QWidget::keyPressEvent(e);
}
/*
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
