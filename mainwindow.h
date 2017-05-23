#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QWidget>
#include<QMainWindow>
#include <Box2D/Box2D.h>
#include<QGraphicsScene>
#include<QGraphicsItem>
#include<QTimer>
#include<QGraphicsLineItem>
#include<QKeyEvent>
#include"circleobject.h"
#include"groundrect.h"
#include"scene.h"
#include"common.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow     *ui;
    Scene      *scene;     // Объявляем графическую сцену
    QTimer* frameTimer;
    b2World* world;
};

#endif // MAINWINDOW_H
