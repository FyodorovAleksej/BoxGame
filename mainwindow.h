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

    void restartSlot();
    void exitSlot();
private:

    /**
     * @brief ui - the GUI elements of window
     */
    Ui::MainWindow     *ui;
    /**
     * @brief scene - scene for this window
     */
    Scene      *scene;

    /**
     * @brief frameTimer - timer for stepping game
     */
    QTimer* frameTimer;

    /**
     * @brief hero - the protagonist of this game
     */
    CircleObject* hero;

    /**
     * @brief mainGoal - the interactive object, that using as a end of the level
     */
    Goal* mainGoal;

    /**
     * @brief world - the 2dBox physic analog of all objects
     */
    b2World* world;

    /**
     * @brief currentLevel - the number of current level
     */
    int currentLevel;
};

#endif // MAINWINDOW_H
