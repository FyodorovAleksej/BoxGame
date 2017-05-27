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
#include "interactavable.h"

/**
 * @brief The Goal class - the class of interactive object
 * QGraphicsEllipseItem - this Object is Circle in QGraohicsScene
 */
class Goal : public QObject, public Interactavable
{
    Q_OBJECT
public:
    explicit Goal(QObject* parent = 0);
    /**
     * @brief Goal - create interactive Object
     * @param initPos - position of interactive Object
     */
    Goal(QPointF initPos);

    /**
      @brief ~Goal - deleting this interactive object
      */
    ~Goal();

    /**
     * @brief releaseAction - processing the interact
     */
    void releaseAction();

signals:

    /**
     * @brief activeSignal - the signal of activation this interactive object
     */
    void activeSignal();

public slots:

    /**
     * @brief stopActive - reactivate this interactive object
     */
    void stopActive();
};

#endif // GOAL_H
