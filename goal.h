#ifndef GOAL_H
#define GOAL_H

#include <QGraphicsEllipseItem>
#include<Box2D/Box2D.h>
#include<QGraphicsEllipseItem>
#include<QBrush>
#include<QObject>
#include<QGraphicsScene>
#include<QTimer>
#include"common.h"

/**
 * @brief The Goal class - the class of interactive object
 * QGraphicsEllipseItem - this Object is Circle in QGraohicsScene
 */
class Goal : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    explicit Goal(QObject *parent = 0);

    /**
     * @brief Goal - create interactive Object
     * @param initPos - position of interactive Object
     */
    Goal(QPointF initPos);

    ~Goal();
    /**
     * @brief releaseAction - processing the interact
     */
    virtual void releaseAction();

protected:

    /**
     * @brief timer - block this object with some time after interact
     */
    QTimer* timer;

    /**
     * @brief active - this object is interacting now?
     */
    bool active;
signals:

    void activeSignal();
public slots:

    /**
     * @brief stopActive - reactivate this interactive object
     */
    virtual void stopActive();
private:
};

#endif // GOAL_H
