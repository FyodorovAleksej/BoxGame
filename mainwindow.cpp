#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QGraphicsSceneMouseEvent>
#include <QDebug>
#include<QGraphicsDropShadowEffect>

void MainWindow::loadLevel1()
{
    qDebug() << "level 1";
    currentLevel = 1;
    scene->clearShadows();
    scene->setSceneRect(scene->itemsBoundingRect());
    ui->graphicsView->setSceneRect(scene->sceneRect());
    scene->addRect(scene->sceneRect());


    scene->addGround(new GroundRect(world,QSizeF(1,1 ), QPointF(0.5, 3.5), 15, true));
    scene->addGround(new GroundRect(world,QSizeF(0.5,0.5 ), QPointF(4.5, 4.5), 15, false));
    scene->addGround(new GroundRect(world,QSizeF(8, 0.1), QPointF(4,5.95), 0, true));
    scene->addGround(new GroundRect(world,QSizeF(0.1, 1), QPointF(0.05, 5.5), 0, false));

    this->hero = new CircleObject(world,0.2,QPointF(Common::toB2(200.00f),Common::toB2(0.00f)));
    scene->setHero(this->hero);
    scene->addHero(scene->getHero());

    Lamp* lamp = new Lamp(0.1,QPointF(Common::toB2(100.00f),Common::toB2(100.00f)),true);
    scene->addLamp(lamp);
    scene->getHero()->addGoal(lamp);

    Goal* goal = new Goal(QPointF(Common::toB2(150.00f), Common::toB2(200.00f)));
    scene->getHero()->addGoal(goal);
    scene->addGoal(goal);
    this->mainGoal = goal;

    connect(this->mainGoal, SIGNAL(activeSignal()), this, SLOT(loadLevel2()));
}


void MainWindow::loadLevel2()
{
    qDebug() << "level 2";

    currentLevel = 2;

    scene->clearShadows();

    scene->addGround(new GroundRect(world,QSizeF(4,0.5f ), QPointF(0, 3), 0, true));
    scene->addGround(new GroundRect(world,QSizeF(0.5f,2 ), QPointF(2.25, 2.25), 0, true));
    scene->addGround(new GroundRect(world,QSizeF(3, 0.1), QPointF(0, -2.0), 0, false));

    this->hero = new CircleObject(world,0.2,QPointF(Common::toB2(200.00f),Common::toB2(100.00f)));
    scene->setHero(this->hero);
    scene->addHero(scene->getHero());

    Goal* goal = new Goal(QPointF(0.0f,-2.2f));
    scene->getHero()->addGoal(goal);
    scene->addGoal(goal);

    //disconnect(this->mainGoal, SIGNAL(activeSignal()), this, SLOT(loadLevel2()));

    this->mainGoal = goal;
    connect(this->mainGoal, SIGNAL(activeSignal()), this, SLOT(loadLevel3()));
}
void MainWindow::loadLevel3()
{
    qDebug() << "level 3";
    currentLevel = 3;

    scene->clearShadows();

    scene->addGround(new GroundRect(world,QSizeF(4,0.5f ), QPointF(0, 3), 0, true));
    scene->addGround(new GroundRect(world,QSizeF(0.5f,2 ), QPointF(2.25, 2.25), 0, true));
    scene->addGround(new GroundRect(world,QSizeF(0.2f, 0.1), QPointF(4, -2.0), 0, true));

    this->hero = new CircleObject(world,0.2,QPointF(Common::toB2(200.00f),Common::toB2(100.00f)));
    scene->setHero(this->hero);
    scene->addHero(scene->getHero());

    Lamp* lamp = new Lamp(0.1f,QPointF(4.0f,-3.0f),true);
    scene->getHero()->addGoal(lamp);
    scene->addLamp(lamp);

    Goal* goal = new Goal(QPointF(10.0f,-1.0f));
    scene->getHero()->addGoal(goal);
    scene->addGoal(goal);
    //disconnect(this->mainGoal, SIGNAL(activeSignal()), this, SLOT(loadLevel3()));
    this->mainGoal = goal;

    connect(this->mainGoal, SIGNAL(activeSignal()), this, SLOT(loadLevel4()));
}
void MainWindow::loadLevel4()
{
    qDebug() << "level 4";
    currentLevel = 4;

    scene->clearShadows();

    scene->addGround(new GroundRect(world,QSizeF(1,0.25f ), QPointF(0, 3), 0, false));
    scene->addGround(new GroundRect(world,QSizeF(0.25,1.0f ), QPointF(-2.125, 2.75f), 0, false));
    scene->addGround(new GroundRect(world,QSizeF(0.25f,1.0f ), QPointF(2.125, 2.75f), 0, false));
    scene->addGround(new GroundRect(world,QSizeF(1.5f,0.25f ), QPointF(1.25, 3.00f), 0, true));
    scene->addGround(new GroundRect(world,QSizeF(1.5f, 0.25f), QPointF(-1.25, 3.00f), 0, true));
    scene->addGround(new GroundRect(world,QSizeF(3.00f, 0.25f), QPointF(0, 0.00f), 0, true));
    scene->addGround(new GroundRect(world,QSizeF(1.5f, 0.25f), QPointF(0, -4.00f), 0, false));

    this->hero = new CircleObject(world,0.2,QPointF(Common::toB2(200.00f),Common::toB2(100.00f)));
    scene->setHero(this->hero);
    scene->addHero(scene->getHero());

    Lamp* lamp = new Lamp(0.1f,QPointF(0.0f,3.3f),true);
    scene->getHero()->addGoal(lamp);
    scene->addLamp(lamp);

    Goal* goal = new Goal(QPointF(0.0f,-3.0f));
    scene->getHero()->addGoal(goal);
    scene->addGoal(goal);
    //disconnect(this->mainGoal, SIGNAL(activeSignal()), this, SLOT(loadLevel4()));
    this->mainGoal = goal;
    connect(this->mainGoal, SIGNAL(activeSignal()), this, SLOT(loadLevel5()));
}
void MainWindow::loadLevel5()
{
    qDebug() << "level 5";


    //disconnect(this->mainGoal, SIGNAL(activeSignal()), this, SLOT(loadLevel5()));
    currentLevel = 5;



    scene->clearShadows();
    scene->clear();
}
void MainWindow::loadLevel6()
{
    qDebug() << "level 6";
    currentLevel = 6;
    scene->clearShadows();
    scene->clear();
}
void MainWindow::loadLevel7()
{

    qDebug() << "level 7";
    currentLevel = 7;
    scene->clearShadows();
    scene->clear();
}
void MainWindow::loadLevel8()
{
    qDebug() << "level 8";
    currentLevel = 8;
    scene->clearShadows();
    scene->clear();
}
void MainWindow::loadLevel9()
{
    qDebug() << "level 9";
    currentLevel = 9;
    scene->clearShadows();
    scene->clear();
}
void MainWindow::loadLevel10()
{
    qDebug() << "level 10";
    currentLevel = 10;
    scene->clearShadows();
    scene->clear();
}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    world = new b2World(b2Vec2(0.00f,10.00f));
    scene = new Scene(0,0,8,6,world);
    ui->centralWidget->showFullScreen();
    ui->graphicsView->setScene(scene);  /// Устанавливаем графическую сцену в graphicsView
    currentLevel = 1;

    connect(scene, SIGNAL(exitSignal()), this, SLOT(exitSlot()));
    connect(scene, SIGNAL(restartSignal()), this, SLOT(restartSlot()));
    loadLevel1();

    frameTimer = new QTimer(this);
    connect(frameTimer, SIGNAL(timeout()),scene, SLOT (advance()));
    connect(frameTimer, SIGNAL(timeout()),this, SLOT (advance()));
    frameTimer->start(1000/60);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete scene;
    delete world;
}

void MainWindow::advance()
{
    this->ui->graphicsView->centerOn(hero->pos());
}

void MainWindow::exitSlot()
{
    this->close();
}

void MainWindow::restartSlot()
{
    switch(currentLevel)
    {
    case 1:
    {
        loadLevel1();
        break;
    }
    case 2:
    {
        loadLevel2();
        break;
    }
    case 3:
    {
        loadLevel3();
        break;
    }
    case 4:
    {
        loadLevel4();
        break;
    }
    case 5:
    {
        loadLevel5();
        break;
    }
    case 6:
    {
        loadLevel6();
        break;
    }
    case 7:
    {
        loadLevel7();
        break;
    }
    case 8:
    {
        loadLevel8();
        break;
    }
    case 9:
    {
        loadLevel9();
        break;
    }
    case 10:
    {
        loadLevel10();
        break;
    }
    default:
    {
        loadLevel1();
        break;
    }
    }
}


