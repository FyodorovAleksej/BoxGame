#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QGraphicsSceneMouseEvent>
#include <QDebug>
#include<QGraphicsDropShadowEffect>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    world = new b2World(b2Vec2(0.00f,10.00f));
    scene = new Scene(0,0,8,6,world);
    ui->centralWidget->showFullScreen();
    ui->graphicsView->setScene(scene);  /// Устанавливаем графическую сцену в graphicsView
    scene->setSceneRect(scene->itemsBoundingRect());
    ui->graphicsView->setSceneRect(scene->sceneRect());
    scene->addRect(scene->sceneRect());

    scene->addGround(new GroundRect(world,QSizeF(4, 0.3), QPointF(2, 1), 15));
    scene->addGround(new GroundRect(world,QSizeF(4, 0.1), QPointF(6, 2), -10));
    scene->addGround(new GroundRect(world,QSizeF(4, 0.1), QPointF(2, 3), 15));
    scene->addGround(new GroundRect(world,QSizeF(4, 0.1), QPointF(6, 4), -10));
    scene->addGround(new GroundRect(world,QSizeF(8, 0.1), QPointF(4,5.95), 0));
    scene->addGround(new GroundRect(world,QSizeF(0.1, 1), QPointF(0.05, 5.5), 0));


    scene->setHero(new CircleObject(world,0.2,QPointF(Common::toB2(200.00f),Common::toB2(0.00f))));
    scene->addHero(scene->getHero());

    scene->setFocusItem(scene->getHero());

    frameTimer = new QTimer(this);
    connect(frameTimer, SIGNAL(timeout()),scene, SLOT (advance()));
    frameTimer->start(1000/60);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete scene;
    delete world;
}


