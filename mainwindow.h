#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QWidget>
#include<QMainWindow>
#include<QGraphicsScene>
#include<QGraphicsItem>
#include<QTimer>
#include<QGraphicsLineItem>
#include<QKeyEvent>
#include"circleobject.h"
#include"groundrect.h"
#include"scene.h"
#include"common.h"
#include"lamp.h"
#include"goal.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void advance();

    void loadLevel1();
    void loadLevel2();
    void loadLevel3();
    void loadLevel4();
    void loadLevel5();
    void loadLevel6();
    void loadLevel7();
    void loadLevel8();
    void loadLevel9();
    void loadLevel10();
private:
    Ui::MainWindow     *ui;
    /**
     * @brief scene - scene for this window
     */
    Scene      *scene;

    /**
     * @brief frameTimer - timer for stepping game
     */
    QTimer* frameTimer;

    CircleObject* hero;
    /**
     * @brief world - world for the 2dBox physics
     */

    Goal* mainGoal;

    b2World* world;
};

#endif // MAINWINDOW_H
