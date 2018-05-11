#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QApplication>
#include <QPainter>
#include <QThread>
#include <QTime>
#include <sstream>
#include <string>
#include <sstream>
#include <string>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QKeyEvent>
#include <QDebug>
#include <QObject>
#include <vector>
#include <iostream>
#include <fstream>

//vector<QGraphicsPixmapItem*> gdots(300);
//vector<QGraphicsPixmapItem*> poo(100);
//vector<QGraphicsPixmapItem*> topO(80);
//vector<QGraphicsPixmapItem*> bottomO(80);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);
    //ui->myGraphicsView->setBackgroundBrush(Qt::red);
    //this->centralWidget()->setStyleSheet("background-image:url(\"4k.jpg\")" );
    //centralWidget()->setStyleSheet("background-image:url(\"4k.jpg\")" );
    //this->setStyleSheet("MainWindow{background-image:url(\"grass.jpg\")}");
    //ui->groupBox->setStyleSheet("color: white");
    //ui->checkBox->setStyleSheet("bacground-color: white");
    //ui->groupBox->setStyleSheet("background-image:url(\"tb.png\")");
    //ui->graphicsView->setStyleSheet("background: transparent");
    //const int w=ui->graphicsView->width();
    //const int h=ui->graphicsView->height();
    ui->label->setStyleSheet("bacground-color: white");
    ui->graphicsView->setSceneRect(0,0,300,300);
    //ui->graphicsView->resize(400,400);
    //ball=new QGraphicsPixmapItem(QPixmap("./ball.jpg"));
    //scene->addItem(ball);
    button = new QPushButton(this);//everytime we drag something in design
    button->setFixedSize(151,51);
    button->move(1050,320);
    //button->move(870,320);
    //ui->verticalLayout->addWidget(button,0,Qt::AlignHCenter);
    //everytime button is clicked
    //connect(button,SIGNAL(clicked()),this, SLOT(pause()));
    connect(button,SIGNAL(clicked()), this, SLOT(startGame()));
    //connect(this, SIGNAL(keyPress(QKeyEvent *));
    //properties of the button
    //button->setIcon(QIcon("./play.ico"));

    QFont font = this->button->font();
    font.setPointSize(19);
    font.setFamily("font-family: TeX Gyre Bonum Bold Italic");
    button->setFont(font);
    button->setText("PLAY");

    this->button->setStyleSheet("background-color: rgb(0, 0, 0);color: rgb(255, 255, 255);");
    //this->button->setStyleSheet("font-family: TeX Gyre Bonum Bold Italic");
    //this->button->setStyleSheet("font-color: white");
    //button->setIconSize(QSize(100,40));//icon diff size fro m button
    button->setEnabled(false);
    timer = new QTimer(this);
    //connect(timer,SIGNAL(timeout()),this,SLOT(tick()));
    timer->start(1000);


    //Snake constructor
    setStyleSheet("background-color:white;");
    leftDirection = false;
    rightDirection = true;//alwasys starts right
    upDirection = false;
    downDirection = false;
    temp = "rightDirection";
    previous = temp;
    inGame = true;//game should already be playing at run
    one = "rightDirection";
    //two = one;

    west = true;
    east = false;
    north = false;
    south = false;

    resize(B_WIDTH, B_HEIGHT);
    loadImages();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::loadImages() {
    if(stage == 0){
        dot=new QGraphicsPixmapItem(QPixmap("./nike.jpg"));
    }
    else{
        dot=new QGraphicsPixmapItem(QPixmap("./sec.png"));
    }
    head=new QGraphicsPixmapItem(QPixmap("./head.png"));
    if(whichOne == "run"){
    apple=new QGraphicsPixmapItem(QPixmap("./mouse.png"));
    }
    else{
       apple=new QGraphicsPixmapItem(QPixmap("./apple.png"));
    }
    //scene->addItem(new QGraphicsPixmapItem(QPixmap("./dot.png")));
    scene->addItem(dot);
    scene->addItem(head);
    scene->addItem(apple);
}

void MainWindow::initGame() {
    QTime bt;
    bt.start();
    dots = 12 ;//length of snake
    gdots.push_back(new QGraphicsPixmapItem(QPixmap("./dot.png")));
    gdots.push_back(new QGraphicsPixmapItem(QPixmap("./dot.png")));
    gdots.push_back(new QGraphicsPixmapItem(QPixmap("./dot.png")));
    gdots.push_back(new QGraphicsPixmapItem(QPixmap("./dot.png")));
    gdots.push_back(new QGraphicsPixmapItem(QPixmap("./dot.png")));
    gdots.push_back(new QGraphicsPixmapItem(QPixmap("./dot.png")));
    gdots.push_back(new QGraphicsPixmapItem(QPixmap("./dot.png")));
    gdots.push_back(new QGraphicsPixmapItem(QPixmap("./dot.png")));
    gdots.push_back(new QGraphicsPixmapItem(QPixmap("./dot.png")));
    gdots.push_back(new QGraphicsPixmapItem(QPixmap("./dot.png")));
    gdots.push_back(new QGraphicsPixmapItem(QPixmap("./dot.png")));
    gdots.push_back(new QGraphicsPixmapItem(QPixmap("./dot.png")));
    poo.push_back(new QGraphicsPixmapItem(QPixmap("./orange.png")));

    if(stage == 1){
        for(int j = 0; j <= 10; j++){

            topO.push_back(new QGraphicsPixmapItem(QPixmap("./orange.png")));
            bottomO.push_back(new QGraphicsPixmapItem(QPixmap("./orange.png")));
        }
    }
    num_apple = 0;

    if(stage == 2){
        xobs[0] = 0;
        obs = 0;
        yobs[0] = 0;
    }

    if(stage ==1){
        obs1 = 10;
        obs2 = 10;
    }

//start of snake
    for (int z = 0; z < dots; z++) {//from head (z=0)
        x[z] = 200- z * 10;//position of snake, other part of the snake
        y[z] = 50;//position of snakebt.elapsed();
    }
    if(stage == 1){
        for (int n=0; n < obs1; n++){
            xobs[n] = 150 + (n *10);
            yobs[n] = 100;
        }

        for (int n= 0; n < obs2; n++){
            xobs2[n] = 150 + (n * 10);
            yobs2[n] = 250;
        }
    }
    locateApple();//place apple on screen, randomley
    timerId = startTimer(DELAY);//everytimer has ID
}

void MainWindow::paintEvent(QPaintEvent *e) {

    Q_UNUSED(e);//#DEFINE Q_UNUSED(C++ code)

    doDrawing();
}

void MainWindow::doDrawing() {

    QPainter qp(this);//each painter knows where it is

    //paint only if we busy
    if (inGame) {

        apple->setPos(apple_x , apple_y);
        scene->addItem(apple);
        //apple->setFlag(QGraphicsItem::ItemIsMovable);
        //qp.drawImage(apple_x, apple_y, apple);//draw image of apple
        if(stage == 2){
            for(int n = 0;n < obs;n++){
                poo[n]->setPos(xobs[n],yobs[n]);
                scene->addItem(poo[n]);
            }
        }
        if(stage == 1){
            for(int n = 0;n < obs1;n++){
                topO[n]->setPos(xobs[n],yobs[n]);
                scene->addItem(topO[n]);
                //cout<<"topo"<<xobs[n]<<endl;

                bottomO[n]->setPos(xobs2[n],yobs2[n]);
                scene->addItem(bottomO[n]);
                //cout<<"bottomo"<<xobs[n]<<endl;

            }
        }
        //draw entire snake
        for (int z = 0; z < dots; z++) {
            if (z == 0) {
                head->setPos(x[z] , y[z]);
                scene->addItem(head);
                //head->setFlag(QGraphicsItem::ItemIsMovable);

            } else {
                gdots[z]->setPos(x[z] , y[z]);
                scene->addItem(gdots[z]);
                //dot->setFlag(QGraphicsItem::ItemIsMovable);

            }
        }


    } else {
        if((num_apple <= moveOn) && stage <= 2){
            moveOn += 10;
            //countDown();
            nextX +=400;
            scene->setSceneRect(nextX,nextY,300,300);
            gdots.clear();
            poo.clear();
            stage++;
            num_apple = 0;
            loadImages();
            inGame = true;
            initGame();


        }
        else{
            nextX+=400;
        gameOver(qp);//when game is over(gmae over)

        }
    }
}

void MainWindow::gameOver(QPainter &qp){//*game over in how many seconds
    if(stage == 2){
        scene->setSceneRect(0,400,300,300);
        line2 = new QGraphicsTextItem(("WELL DONE YOU MADE IT TO THE END"));
        line2->setPos(0,400);
        scene->addItem(line2);
    }
    else{
        scene->setSceneRect(0,400,300,300);
        line2 = new QGraphicsTextItem(("Game Over"));
        line2->setPos(0,400);
        scene->addItem(line2);
    }
    //ui->graphicsView->setScene(gameOverScene);

    //scene->clear();
    /*
    gameOverScene = new QGraphicsScene(0,0,1000,400);
    ui->graphicsView->setScene(gameOverScene);
    gameOverScene->setSceneRect(0,0,1000,400);
    gameOverScene->addText("Game Over");
    readit.open("./Scores.txt");
    if(readit){
        while(getline(readit,line)){
            std::stringstream ss;
            ss<<line;

            QString line1(ss.str().c_str());
            gameOverScene->addText(line1);

            //line2 = new QGraphicsTextItem();
            //QGraphicsTextItem line2  = this->scene()->addText(line);
            //line2 = new QGraphicsTextItem(message);
            //line2 = "ey ya";
            //scene->addText(line2);

        }
        readit.close();
    }
    */
    //runinS = QString::number(runin);
//    QString message = "Game over in " +QString::number(bt.elapsed()/1000) + " second(s)";
//    QString message3 = QString::number(num_apple)+ " apple(s) eaten!";
//    QFont font("Courier", 12, QFont::DemiBold);
//    QFontMetrics fm(font);//do calculatio with the fint
//    int textWidth = fm.width(message);//calculate width of font, to fit in screen
//   // int textWidth2 = fm.width(message2);
//    int textWidth3 = fm.width(message3);
//    qp.setFont(font);
//    int h = height();//location of paint
//    int w = width();

//    //work from middle of window
//    qp.translate(QPoint(w/2, h/2));
//    qp.drawText(-textWidth/2, 0, message);//start of the text behind the middle
//    qp.drawText(-textWidth3/2, 30, message3);
}

void MainWindow::checkApple() {//collided with apple o not

    if ((x[0] == apple_x) && (y[0] == apple_y)) {//head and apple on same coordinate
        if(stage == 2){
            xobs[obs] = x[1];
            yobs[obs] = y[1];
            poo.push_back(new QGraphicsPixmapItem(QPixmap("./orange.png")));
        }
        //obs++;
        dots++;//add body
        gdots.push_back(new QGraphicsPixmapItem(QPixmap("./dot.png")));
        locateApple();//plant another apple
        num_apple++;
        if(num_apple == moveOn){
            inGame = false;
        }
        ui->label_4->setText(QString::number(num_apple));

    }
}

void MainWindow::move() {//moving the head, in direction of keypress,rest of body move in order(seond move to last position of head etc.

    for (int z = dots; z > 0; z--) {//start from tail
        x[z] = x[(z - 1)];//move each to next position
        y[z] = y[(z - 1)];
    }
    if(stage == 1){
    for (int n = obs1; n> 0; n--){
        xobs[n] = xobs[(n-1)];// move each to the next posotion
        yobs[n] = yobs[(n-1)];

        xobs2[n] = xobs2[(n-1)];// move each to the next posotion
        yobs2[n] = yobs2[(n-1)];
    }
}
    if(whichOne == "robot" || whichOne == "run"){
        goGetIt();
    }
    if(stage == 1){
    chaseTheSnake();
    //cout<<"JSNJKDVBJKSDBVJKBJKNSDVJBNSDJKVNSDJKVBJKSDVBJKSBF";
    }
    //for head to follow the keys pressed
    if (leftDirection) {
        x[0] -= DOT_SIZE;
        front_x = x[0] - 10;
        front_y = y[0];
        left_x = x[0];
        left_y = y[0] + 10;
        right_x = x[0];
        right_y = y[0] -10;
    }

    if (rightDirection) {
        x[0] += DOT_SIZE;
        front_x = x[0] + 10;
        front_y = y[0];
        left_x = x[0];
        left_y = y[0] - 10;
        right_x = x[0];
        right_y = y[0] +10;
    }

    if (upDirection) {
        y[0] -= DOT_SIZE;
        front_y = y[0] - 10;
        front_x = x[0];
        left_x = x[0] - 10;
        left_y = y[0];
        right_x = x[0] + 10;
        right_y = y[0];
    }

    if (downDirection) {
        y[0] += DOT_SIZE;
        front_y = y[0] + 10;
        front_x = x[0];
        left_x = x[0] + 10;
        left_y = y[0];
        right_x = x[0] - 10;
        right_y = y[0];
    }
    if (west) {
        xobs[0] -= DOT_SIZE;
        xobs2[0] -= DOT_SIZE;
    }
    if(stage == 1){
    if (east) {
        xobs[0] += DOT_SIZE;
        xobs2[0] += DOT_SIZE;
    }
    if (north) {
        yobs[0] -= DOT_SIZE;
    }
    if (south) {
        yobs[0] += DOT_SIZE;
    }
    }
}


void MainWindow::checkCollision() {//if snake is dead
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
        if(whichOne == "robot" || whichOne == "run"){
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
    }
if(stage == 2){
    for (int z = obs; z > 0; z--) {//check at any part of the obstacle

        if ((x[0] == xobs[z]) && (y[0] == yobs[z])) {//start at 4 cause impossible to bite neck below 3
            inGame = false;//end game
            //runin =(uint)bt.elapsed();
        }
        if((front_x == xobs[z]) && (front_y == yobs[z])){
            aboutto = 1;
            //cout << "crash///////////////////////////////////////////////////////happen"<< endl;
        }
        if((left_x == xobs[z]) && (left_y == yobs[z])){
            two = 1;
        }
        if((right_x == xobs[z]) && (right_y == yobs[z])){
            two = 1;
        }
        //cout << "frontx: "<<front_x<< " fronty:"<< front_y<<" obs_x:"<<xobs[z]<<" obs_y:"<<yobs[z]<<endl;

        /*
        if((right_x == apple_x) && (right_y == apple_y)){
            three = 1;
        }
        if((left_x == apple_x) && (left_y == apple_y)){
            three = 1;
        }*/

        //body on the right but there is no body on the left
        if(((left_x != xobs[z]) && (left_y != yobs[z]))  && ((right_x == xobs[z]) && (right_y == yobs[z])) &&( ((left_x == apple_x) && (left_y < apple_y)) || ((left_y == apple_y) && (left_x < apple_x)))){

            four = 1;
        }
        //body on the left but there is no body on the right
        else if(((left_x == xobs[z]) && (left_y == yobs[z])) && ((right_x != x[z]) && (right_y != yobs[z])) &&( ((right_x == apple_x) && (right_y > apple_y)) || ((right_y == apple_y) && (right_x > apple_x))  ) ){

            five = 1;
        }
    }
}
if(stage == 1){
    for (int z = obs1; z > 0; z--) {//check at any part of the obstacle

        if (((x[0] == xobs[z]) && (y[0] == yobs[z])) || ((x[0] == xobs2[z]) && (y[0] == yobs2[z]))) {//start at 4 cause impossible to bite neck below 3
            inGame = false;//end game
            //runin =(uint)bt.elapsed();
        }
        if(((front_x == xobs[z]) && (front_y == yobs[z])) || ((front_x == xobs2[z]) && (front_y == yobs2[z]))){
            aboutto = 1;

        }
        if(((left_x == xobs[z]) && (left_y == yobs[z])) || ((left_x == xobs2[z]) && (left_y == yobs2[z]))){
            two = 1;

        }
        if(((right_x == xobs[z]) && (right_y == yobs[z])) || ((right_x == xobs2[z]) && (right_y == yobs2[z]))){
            two = 1;

        }

        //body on the right but there is no body on the left
        if(((left_x != xobs[z]) && (left_y != yobs[z]))  && ((right_x == xobs[z]) && (right_y == yobs[z])) &&( ((left_x == apple_x) && (left_y < apple_y)) || ((left_y == apple_y) && (left_x < apple_x)))){

            four = 1;
        }
        //body on the left but there is no body on the right
        else if(((left_x == xobs[z]) && (left_y == yobs[z])) && ((right_x != x[z]) && (right_y != yobs[z])) &&( ((right_x == apple_x) && (right_y > apple_y)) || ((right_y == apple_y) && (right_x > apple_x))  ) ){

            five = 1;
        }
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

void MainWindow::locateApple() {//random position of apple

    QTime time = QTime::currentTime();
    qsrand((uint) time.msec());

    int r = qrand() % RAND_POS;//random position 0-29
    apple_x =(r * DOT_SIZE);//random x

    r = qrand() % RAND_POS;
    apple_y = (r * DOT_SIZE);//random y
}

void MainWindow::timerEvent(QTimerEvent *e) {

    Q_UNUSED(e);

    if (inGame) {

        checkApple();//if apple is eaten
        checkCollision();//if theres colision
        move();//continue moving
    }

    repaint();//change window graphics,repaint
}


void MainWindow::goGetIt(){
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

        if(x[0] < B_WIDTH/2){
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

        if (x[0] < B_WIDTH/2){
            rightDirection = true;
            downDirection = false;
            upDirection = false;//o
            leftDirection = false;
            one = "rightDirection";
        }else{
chaseTheSnake();
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

        if (y[0] < B_WIDTH/2){
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

        if (y[0] < B_WIDTH/2){
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



}
void MainWindow::keyPressEvent(QKeyEvent *e) {

    int key = e->key();//key pressed in that event, e is a pointer, pointing to key pressed
    if(whichOne == "control"){
    if ((key == Qt::Key_A) && (!rightDirection)) {//continue in direction unless another buton pressed
        leftDirection = true;
        upDirection = false;
        downDirection = false;
    }

    if ((key == Qt::Key_D) && (!leftDirection)) {
        rightDirection = true;
        upDirection = false;
        downDirection = false;
    }

    if ((key == Qt::Key_W) && (!downDirection)) {
        upDirection = true;
        rightDirection = false;
        leftDirection = false;
    }

    if ((key == Qt::Key_S) && (!upDirection)) {
        downDirection = true;
        rightDirection = false;
        leftDirection = false;
    }

    }
    else if(whichOne == "run"){

        if ((key == Qt::Key_A)) {
            apple_x -= 10;

        }

        if ((key == Qt::Key_D)) {
            apple_x += 10;

        }

        if ((key == Qt::Key_W)) {
            apple_y -= 10;

        }

        if ((key == Qt::Key_S)) {
            apple_y += 10;

        }

    }
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
            //killTimer(timerId);
            //playingGame = false;
        }
        else{
            timer->start(1000);
            button->setIcon(QIcon("./pause.ico"));
            button->setIconSize(QSize(100,40));
            //timerId = startTimer(DELAY);
            //playingGame = true;
        }
    }

}
void MainWindow::startGame(){
    if(alreadyClicked){initGame();}
    alreadyClicked = false;
    if(playingGame){

        killTimer(timerId);
        playingGame = false;
        button->setText("PLAY");

    }
    else{
        timerId = startTimer(DELAY);
        playingGame = true;
        button->setText("PAUSE");
    }

}

void MainWindow::on_checkBox_clicked()
{
    //if all are unchecked
    if(!ui->checkBox->isChecked() && !ui->checkBox_2->isChecked() && !ui->checkBox_3->isChecked()){
        button->setEnabled(false);
    }
    //if you just turned this on switch off all others
    else if(ui->checkBox_2->isChecked() && ui->checkBox->isChecked() && ui->checkBox_3->isChecked()){
        ui->checkBox_3->setChecked(false);
        ui->checkBox_2->setChecked(false);
        button->setEnabled(true);
        whichOne = "robot";
        //robot = "";

    }
    else if(ui->checkBox->isChecked() && (ui->checkBox_2->isChecked() || ui->checkBox_3->isChecked())){
        ui->checkBox_3->setChecked(false);
        ui->checkBox_2->setChecked(false);
        button->setEnabled(true);
        whichOne = "robot";
        //robot = "";
    }
    else if(!ui->checkBox_2->isChecked() && ui->checkBox->isChecked() && !ui->checkBox_3->isChecked()){
        button->setEnabled(true);
        whichOne = "robot";
        //robot = "";
    }

}

void MainWindow::on_checkBox_3_clicked()
{
    //if all are unchecked
    if(!ui->checkBox->isChecked() && !ui->checkBox_2->isChecked() && !ui->checkBox_3->isChecked()){
        button->setEnabled(false);
    }
    //if you just turned this on switch off all others
    else if(ui->checkBox_2->isChecked() && ui->checkBox->isChecked() && ui->checkBox_3->isChecked()){
        ui->checkBox->setChecked(false);
        ui->checkBox_2->setChecked(false);
        button->setEnabled(true);
        whichOne = "run";
        //robot = "";
    }
    else if(ui->checkBox_3->isChecked() && (ui->checkBox_2->isChecked() ||  ui->checkBox->isChecked())){
        ui->checkBox->setChecked(false);
        ui->checkBox_2->setChecked(false);
        button->setEnabled(true);
        whichOne = "run";
        //robot = "";
    }
    else if(!ui->checkBox_2->isChecked() && !ui->checkBox->isChecked() && ui->checkBox_3->isChecked()){
        button->setEnabled(true);
        whichOne = "run";
        //robot = "";
    }


}

void MainWindow::on_checkBox_2_clicked()
{
    //if all are unchecked
    if(!ui->checkBox->isChecked() && !ui->checkBox_2->isChecked() && !ui->checkBox_3->isChecked()){
        button->setEnabled(false);
    }
    //if you just turned this on switch off all others
    else if(ui->checkBox_2->isChecked() && ui->checkBox->isChecked() && ui->checkBox_3->isChecked()){
        ui->checkBox->setChecked(false);
        ui->checkBox_3->setChecked(false);
        button->setEnabled(true);
        whichOne = "control";
        //robot = "";
    }
    else if(ui->checkBox_2->isChecked() && (ui->checkBox_3->isChecked() ||  ui->checkBox->isChecked())){
        ui->checkBox->setChecked(false);
        ui->checkBox_3->setChecked(false);
        button->setEnabled(true);
        whichOne = "control";
        //robot = "";
    }
    else if(ui->checkBox_2->isChecked() && !ui->checkBox->isChecked() && !ui->checkBox_3->isChecked()){
        button->setEnabled(true);
        whichOne = "control";
        //robot = "";
    }

}
void MainWindow::countDown(){
    int a = 5;
    QThread::usleep(1000);
    while(a <=0){
        QThread::usleep(1000);
        numberpic(a);
        a--;
    }

}
void MainWindow::numberpic(int a){
    number=new QGraphicsPixmapItem(QPixmap("./c.png"));
    scene->addItem(number);
}

void MainWindow::chaseTheSnake(){
    if((west && xobs[0]> 50)||(west && xobs2[0]> 50)){
        north= false;
        south = false;
        east = false;
        west = true;
    }else if((west && xobs[0]== 50)||(west && xobs2[0]== 50)){
        north= false;
        south = false;
        east = true;
        west = false;
    }else if((west && xobs[0]<250)||(west && xobs2[0]<250)){
        north= false;
        south = false;
        east = true;
        west = false;
    }else if((east && xobs[0]==250)||(east && xobs2[0]==250)){
        north= false;
        south = false;
        east = false;
        west = true;
    }
}




