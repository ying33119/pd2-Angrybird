#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "button.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Enable the event Filter
    qApp->installEventFilter(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showEvent(QShowEvent *)
{
    // Setting the QGraphicsScene
    scene = new QGraphicsScene(0,0,width(),ui->graphicsView->height());
    ui->graphicsView->setScene(scene);
    scene->setBackgroundBrush(QBrush(QImage(":/image/background.png")));
    // Create world
    world = new b2World(b2Vec2(0.0f, -9.8f));
    // Setting Size
    GameItem::setGlobalSize(QSizeF(32,18),size());

    start();

    // Timer
    connect(&timer,SIGNAL(timeout()),this,SLOT(tick()));
    connect(this,SIGNAL(quitGame()),this,SLOT(QUITSLOT()));
    timer.start(100/6);
}

void MainWindow::start()
{
    // Create ground (You can edit here)
    itemList.push_back(new Land(16.0f,1.5f,32.0f,3.0f,QPixmap(":/image/land.png").scaled(width(),height()/5.0),world,scene));
    itemList.push_back(new Land(3.5f,8.0f,1.0f,0.01f,QPixmap(":/image/slingshot.png").scaled(width()/12.0,height()/3.5),world,scene));
    itemList.push_back(new block(18.0f,5.0f,1.0f,&timer,QPixmap(":/image/stonesquare.png").scaled(height()/9.0,height()/9.0),world,scene));
    itemList.push_back(new block(18.0f,8.0f,1.0f,&timer,QPixmap(":/image/woodsquare.png").scaled(height()/9.0,height()/9.0),world,scene));
    itemList.push_back(new block(18.0f,11.0f,1.0f,&timer,QPixmap(":/image/stonesquare.png").scaled(height()/9.0,height()/9.0),world,scene));
    itemList.push_back(new block(21.0f,7.0f,1.0f,&timer,QPixmap(":/image/stonesquare.png").scaled(height()/9.0,height()/9.0),world,scene));
    itemList.push_back(new pig(21.0f,10.0f,1.0f,&timer,QPixmap(":/image/pig.png").scaled(height()/9.0,height()/9.0),world,scene));
    itemList.push_back(new block(24.0f,6.0f,1.0f,&timer,QPixmap(":/image/woodsquare.png").scaled(height()/9.0,height()/9.0),world,scene));
    itemList.push_back(new block(24.0f,9.0f,1.0f,&timer,QPixmap(":/image/stonesquare.png").scaled(height()/9.0,height()/9.0),world,scene));
    itemList.push_back(new block(24.0f,12.0f,1.0f,&timer,QPixmap(":/image/woodsquare.png").scaled(height()/9.0,height()/9.0),world,scene));
    itemList.push_back(new block(24.0f,14.0f,1.0f,&timer,QPixmap(":/image/stonesquare.png").scaled(height()/9.0,height()/9.0),world,scene));

    // Create bird (You can edit here)
    bird = new birdR(3.5f,9.5f,1.0f,&timer,QPixmap(":/image/birdR.png").scaled(height()/9.0,height()/9.0),world,scene);
    bird->setLinearVelocity(b2Vec2(0,0));
    birdList.push_back(bird);
}

bool MainWindow::eventFilter(QObject *, QEvent *event)
{
    // Hint: Notice the Number of every event!
   if(event->type() == QEvent::MouseButtonPress && bird->shot==false)
    {
        /* TODO : add your code here*/
        std::cout << "Press !" << std::endl;
        move = true;
        return true;
    }
   if(event->type() == QEvent::MouseMove && move == true && bird->shot==false)
    {
        /* TODO : add your code here */
        //std::cout << "Move !" << std::endl ;
        QPoint cursor = QCursor::pos();
        double x = cursor.x()*(bird->g_worldsize.width()/bird->g_windowsize.width())-16.5;
        double y = (bird->g_worldsize.height())-cursor.y()*((bird->g_worldsize.height()/bird->g_windowsize.height()))+8.5;
        bird->g_body->SetTransform(b2Vec2(x,y),0);
        bird->g_body->SetGravityScale(0);
        return true;
    }
    if(event->type() == QEvent::MouseButtonRelease && move == true && bird->shot==false)
    {
        /* TODO : add your code here */
        std::cout << "Release !" << std::endl ;
        bird->g_body->SetGravityScale(1);
        double x = bird->g_body->GetPosition().x;
        double y = bird->g_body->GetPosition().y;
        bird->setLinearVelocity(b2Vec2((3.5-x)*7,(8.0-y)*7));
        bird->shot = true;
        birdnum++;
        move = false;
        return true;
    }
    return false;
}

void MainWindow::keyPressEvent(QKeyEvent* event){
    if(event->key() == Qt::Key_A && bird->advanced == false){
        std::cout << "A !" << std::endl ;
        bird->advanced = true;
        bird->effect();
     }
}

void MainWindow::tick()
{
    world->Step(1.0/60.0,6,2);
    scene->update();
    if(bird->shot==true && waited==false && birdnum<4){
        QTimer::singleShot(3500, this, SLOT(createbird()));
        waited = true;
    }
    else if(bird->shot==true && waited==false && birdnum==4){
        QTimer::singleShot(2000, this, SLOT(createbird()));
        waited = true;
    }
}
void MainWindow::createbird(){
    switch(birdnum){
    case 1:
        bird = new birdX(3.5f,8.6f,1.0f,&timer,QPixmap(":/image/birdX.png").scaled(height()/12.0,height()/9.0),world,scene);
        bird->setLinearVelocity(b2Vec2(0,0));
        birdList.push_back(bird);
        waited = false;
        break;
    case 2:
        bird = new birdY(3.5f,8.6f,1.0f,&timer,QPixmap(":/image/birdY.png").scaled(height()/9.0,height()/9.0),world,scene);
        bird->setLinearVelocity(b2Vec2(0,0));
        birdList.push_back(bird);
        waited = false;
        break;
    case 3:
        bird = new birdB(3.5f,8.6f,1.0f,&timer,QPixmap(":/image/birdB.png").scaled(height()/9.0,height()/9.0),world,scene);
        bird->setLinearVelocity(b2Vec2(0,0));
        birdList.push_back(bird);
        waited = false;
        break;
    case 4:
        //create the start button
        startButton = new button(QString("RESTART"));
        startButton->setPos(110,200);
        connect(startButton, SIGNAL(clicked()), this, SLOT(restart()));
        scene->addItem(startButton);

        //create the exit button
        exitButton  = new button(QString("EXIT"));
        exitButton->setPos(220,200);
        connect(exitButton, SIGNAL(clicked()), this, SLOT(quit()));
        scene->addItem(exitButton);
    default:
        break;
    }
}
void MainWindow::quit(){
    emit quitGame();
}

void MainWindow::restart(){

    delete startButton;
    delete exitButton;

    waited = false;
    move = false;
    birdnum=0;
    foreach(GameItem *bird ,birdList){
        birdList.removeOne(bird);
        delete bird;
    }
    foreach(GameItem *item ,itemList){
        itemList.removeOne(item);
        delete item;
    }
    start();
}

/*void MainWindow::closeEvent(QCloseEvent *)
{
    // Close event
    emit quitGame();
}*/

void MainWindow::QUITSLOT()
{
    // For debug
    std::cout << "Quit Game Signal receive !" << std::endl ;
}
