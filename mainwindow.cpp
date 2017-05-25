#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QGraphicsSceneMouseEvent>
#include <QDebug>
#include<QGraphicsDropShadowEffect>

void MainWindow::loadLevel1()
{
    qDebug() << "level 1";
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
    this->mainGoal = goal;
    connect(this->mainGoal, SIGNAL(activeSignal()), this, SLOT(loadLevel3()));
}
void MainWindow::loadLevel3()
{
    qDebug() << "level 3";
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
    this->mainGoal = goal;

    connect(this->mainGoal, SIGNAL(activeSignal()), this, SLOT(loadLevel4()));
}
void MainWindow::loadLevel4()
{
    qDebug() << "level 4";
    scene->clearShadows();

    scene->addGround(new GroundRect(world,QSizeF(1,0.25f ), QPointF(0, 3), 0, false));
    scene->addGround(new GroundRect(world,QSizeF(0.25,2.0f ), QPointF(-2.125, 2.5f), 0, false));
    scene->addGround(new GroundRect(world,QSizeF(0.25f,2.0f ), QPointF(2.125, 2.5f), 0, false));
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
    this->mainGoal = goal;
    connect(this->mainGoal, SIGNAL(activeSignal()), this, SLOT(loadLevel5()));
}
void MainWindow::loadLevel5()
{

    scene->clearShadows();
    scene->clear();
}
void MainWindow::loadLevel6()
{

    foreach(b2Body* body, scene->getBodies())
    {
        world->DestroyBody(body);
    }
    scene->clear();
}
void MainWindow::loadLevel7()
{

    foreach(b2Body* body, scene->getBodies())
    {
        world->DestroyBody(body);
    }
    scene->clear();
}
void MainWindow::loadLevel8()
{

    foreach(b2Body* body, scene->getBodies())
    {
        world->DestroyBody(body);
    }
    scene->clear();
}
void MainWindow::loadLevel9()
{

    foreach(b2Body* body, scene->getBodies())
    {
        world->DestroyBody(body);
    }
    scene->clear();
}
void MainWindow::loadLevel10()
{

    foreach(b2Body* body, scene->getBodies())
    {
        world->DestroyBody(body);
    }
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


