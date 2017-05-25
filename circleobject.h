#ifndef CIRCLEOBJECT_H
#define CIRCLEOBJECT_H

#include <QGraphicsEllipseItem>
#include<Box2D/Box2D.h>
#include<QGraphicsItem>
#include<QBrush>
#include<QTimer>
#include<QObject>
#include<QGraphicsScene>
#include"common.h"
#include"lightable.h"
#include"goal.h"

/**
 * the class of the main hero (protagonist) of the game
 * @brief The CircleObject class - circle, that can  move by physics in 2dBox
 * QGraphicsEllipseItem - as Item in scene for graphics
 * Lightable - as item, that can be lighting
 */
class CircleObject : public QObject, public QGraphicsEllipseItem, public Lightable
{
    Q_OBJECT
public:

    /**
     * @brief CircleObject - as QObject
     * @param parent
     */
    explicit CircleObject(QObject *parent = 0);

    /**
     * @brief CircleObject
     * @param world - the world for 2dBox physics
     * @param radius - the radius of the circle (in 2dBox coordinates)
     * @param initPos - the position on scene (in 2dBox coordinates)
     */
    CircleObject(b2World *world, qreal radius, QPointF initPos);

    ~CircleObject();

    /**
    * @brief advance the step of the game
    */
   void  advance(int);

   /**
    * @brief getLight - getting coordinates of center of lighting object
    * @return QPointF - coordinates of centr
    */
   QPointF getLight();

   b2Body* getBody();

   /**
    * @brief addGoal - adding Object for interact. When collides with him - execute Goal::releaseAction()
    * @param item - the interact object
    */
   void addGoal(Goal* item);

   /**
    * @brief isActive - return true
    * @return  always true
    */
   bool isActive();

signals:
   void goalAction();

public slots:

   /**
     * @brief upPressed - processing pressing UP
     */
    void upPressed();

    /**
     * @brief leftPressed - processing  pressing LEFT
     */
    void leftPressed();

    /**
     * @brief rightPressed - processing pressing RIGHT
     */
    void rightPressed();


    /**
     * @brief leftForce - forcing in LEFT direction by using 2dBox physics
     */
    void leftForce();

    /**
     * @brief rightForce - forcing in RIGHT direction by using 2dBox physics
     */
    void rightForce();


    /**
     * @brief upReleased - processing releasing UP
     */
    void upReleased();

    /**
     * @brief leftReleased - processing releasing LEFT
     */
    void leftReleased();

    /**
     * @brief rightReleased - processing releasing RIGHT
     */
    void rightReleased();

private:

    /**
     * @brief body - the 2dBox object of circle
     */
    b2Body *body;

    /**
     * @brief leftTimer - the timer for forcing in LEFT direction, while LEFT was pressed
     */
    QTimer *leftTimer;

    /**
     * @brief rightTimer - the timer for forcing in RIGHT direction, while RIGHT was pressed
     */
    QTimer *rightTimer;


    /**
     * @brief goals - the list of all interactive Objects
     */
    QList<Goal*> *goals;

    /**
     * @brief jump - can the hero jump now?
     */
    bool jump;

    /**
     * @brief action - interact hero with some Object now?
     */
    bool action;
};

#endif // CIRCLEOBJECT_H
