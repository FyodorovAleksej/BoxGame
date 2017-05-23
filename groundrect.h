#ifndef GROUNDRECT_H
#define GROUNDRECT_H
#include <QGraphicsItem>
#include<QGraphicsRectItem>
#include<Box2D/Box2D.h>
#include<QBrush>
#include"circleobject.h"
#include"shadowable.h"
#include<qmath.h>
class GroundRect : public QGraphicsRectItem, public Shadowable
{
public:
    GroundRect(b2World *world,QSizeF size, QPointF initPos, qreal angle);
    ~GroundRect();

    QList<QPointF> *getPoints();
    void setHero(CircleObject *hero);
    CircleObject* getHero();

    bool isActive();
    QList<QPointF>* addShadow(QPointF light);
private:
    b2Body *body;
    QList<QPointF> *points;

    CircleObject *hero;
    bool shadowActive;
};

#endif // GROUNDRECT_H
