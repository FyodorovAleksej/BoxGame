#ifndef SCENE_H
#define SCENE_H
#include<QGraphicsScene>
#include"circleobject.h"
#include"shadowable.h"
#include"groundrect.h"
#include"lightable.h"
#include"common.h"
#include"QKeyEvent"
#include"QDebug"

class Scene: public QGraphicsScene
{
    Q_OBJECT
public:
    Scene(qreal x, qreal y, qreal width, qreal high,b2World* world);
    CircleObject *getHero();
    void setHero(CircleObject* hero);

    QList<Shadowable*>* getShadowList();
    QList<Lightable*>* getLightList();

    void addGround(GroundRect* rect);
    void addHero(CircleObject* hero);

    QGraphicsLineItem* createLine(QPointF light, QPointF point);
    QGraphicsPolygonItem* createShadow(QGraphicsLineItem* line1, QGraphicsLineItem* line2);
public slots:
    void advance();

private:
    QList<QPointF> *pointsList;
    QList<QGraphicsItem*> *lineList;
    b2World* world;
     CircleObject *hero;
     QList<Shadowable*> *shadowableList;
     QList<Lightable*> *lightableList;

     bool active = false;

    // QGraphicsScene interface
protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
};

#endif // SCENE_H
