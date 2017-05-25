#ifndef SCENE_H
#define SCENE_H
#include<QGraphicsScene>
#include <Box2D/Box2D.h>
#include"circleobject.h"
#include"shadowable.h"
#include"groundrect.h"
#include"lightable.h"
#include"common.h"
#include"lamp.h"
#include"QKeyEvent"
#include"QDebug"
#include <QMutex>
#include <QMainWindow>
#include"goal.h"

/**
 * @brief The Scene class - the scene of the main window
 */
class Scene: public QGraphicsScene
{
    Q_OBJECT
public:

    /**
     * @brief Scene - creating the Scene
     * @param x - the left top.x
     * @param y - the left top.y
     * @param width - width of the scene
     * @param high - high of the scene
     * @param world - the 2dBox analog for physics
     */
    Scene(qreal x, qreal y, qreal width, qreal high,b2World* world);
    ~Scene();

    void clearShadows();

    /**
     * @brief getHero - getting protagonist of this game
     * @return - CircleObject* hero
     */
    CircleObject *getHero();

    /**
     * @brief setHero - setting protagonist of this game
     * @param hero - CircleObject* hero
     */
    void setHero(CircleObject* hero);

    /**
     * @brief getShadowList - getting the list of all shadowable objects
     * @return - QList of shadowable* objects
     */
    QList<Shadowable*>* getShadowList();

    /**
     * @brief getLightList - getting the list of all lightable objects
     * @return - QList of Lightable* objects
     */
    QList<Lightable*>* getLightList();

    QList<b2Body*>  getBodies();

    /**
     * @brief addGround - adding block
     * @param rect - the shadowable rectangle
     */
    void addGround(GroundRect* rect);

    /**
     * @brief addHero - adding protagonist
     * @param hero - the protagonist
     */
    void addHero(CircleObject* hero);

    /**
     * @brief addLamp - adding interactive Lamp
     * @param light - object of lamp
     */
    void addLamp(Lamp* light);

    /**
     * @brief addGoal - adding some interactive Object
     * @param goal - some interactive object
     */
    void addGoal(Goal* goal);

    /**
     * @brief createLine - creating line for shadow
     * @param light - the coordinates of light point
     * @param point - the coorinates of important point
     * @return - the line after point
     */
    QGraphicsLineItem* createLine(QPointF light, QPointF point);

    /**
     * @brief createShadow - creating polygon (shadow) by using 2 lines
     * @param line1 - first line
     * @param line2 - second line
     * @return * 4 points -polygon (shadow)
     */
    QGraphicsPolygonItem* createShadow(QGraphicsLineItem* line1, QGraphicsLineItem* line2);


signals:
    void restartSignal();
    void exitSignal();

public slots:
    /**
     * @brief advance - the step of the game
     */
    void advance();

private:
    /**
     * @brief pointsList - the list of all important points for all shadows
     */
    QList<QPointF> *pointsList;

    /**
     * @brief lineList - the list of all lines
     */
    QList<QGraphicsItem*> *lineList;

    /**
     * @brief world - the world for 2dBox physics
     */
    b2World* world;

    /**
      * @brief hero - the protagonist
      */
     CircleObject *hero;




     /**
      * @brief shadowableList - all objects, that can be creating shadow
      */
     QList<Shadowable*> *shadowableList;

     /**
      * @brief lightableList - all lightable objects
      */
     QList<Lightable*> *lightableList;

     /**
      * @brief bodyes - all 2dBox physics bodies on the scene
      */
     QList<b2Body*> *bodyes;

     QList<QGraphicsItem*> *otherItems;

     /**
      * @brief active - shadows is active?
      */
     bool active;

     QMutex* mutex;

    // QGraphicsScene interface
protected:

     /**
     * @brief keyPressEvent - processing pressing keyboard
     * @param event - the event for processing
     */
    void keyPressEvent(QKeyEvent *event);

    /**
     * @brief keyReleaseEvent - processing releasing keyboard
     * @param event - the event for processing
     */
    void keyReleaseEvent(QKeyEvent *event);
};

#endif // SCENE_H
