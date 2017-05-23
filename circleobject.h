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

class CircleObject : public QObject, public QGraphicsEllipseItem, public Lightable
{
    Q_OBJECT
public:
    explicit CircleObject(QObject *parent = 0);
    CircleObject(b2World *world, qreal radius, QPointF initPos);
    ~CircleObject();

   void  advance(int);
   QPointF getLight();
signals:

public slots:
    void upPressed();
    void leftPressed();
    void rightPressed();

    void leftForce();
    void rightForce();

    void upReleased();
    void leftReleased();
    void rightReleased();

private:
    b2Body *body;

    QTimer *leftTimer;
    QTimer *rightTimer;

    qreal leftForceCustom;
    qreal rightForceCustom;

    bool jump = true;
};

#endif // CIRCLEOBJECT_H
