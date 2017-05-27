#include "groundrect.h"
#include"common.h"
#include"QDebug"

qreal sqr2(qreal x)
{
    return x*x;
}
qreal absAngle(qreal x)
{
    if (x < 0) return -x;
    else return x;
}

GroundRect::GroundRect(b2World *world, QSizeF size, QPointF initPos, qreal angle, bool active)
    :QGraphicsRectItem(0)
{
    shadowActive = active;
    qreal newWidth = Common::fromB2(size.width()/2);
    qreal newHeight = Common::fromB2(size.height()/2);

    setRect(-newWidth,-newHeight,newWidth*2, newHeight*2);
    if (active == true)
    {
        setBrush(QBrush(Qt::gray));
    }
    else
    {
        setBrush(QBrush(QColor(96,159,223)));
    }
    setPos(Common::fromB2(initPos.x()),Common::fromB2(initPos.y()));
    setRotation(angle);

    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(initPos.x(),initPos.y());
    bodyDef.angle = 3.14*angle/180;

    angle = 3.14*angle/180;

    this->body = world->CreateBody(&bodyDef);

    b2PolygonShape shape;
    shape.SetAsBox(size.width()/2,size.height()/2);

    body->CreateFixture(&shape,0.0f);


   points = new QList<QPointF>;
    QPointF mas[4] = {QPointF(newWidth, newHeight),QPointF( -newWidth, newHeight),QPointF(newWidth, -newHeight),QPointF(-newWidth, -newHeight)};
     for (int i = 0; i < 4; i++)
     {
        qreal cosa = mas[i].x();
        qreal sina = mas[i].y();

        qreal newY = sin(angle)*cosa + cos(angle)*sina;
        qreal newX = cos(angle)*cosa - sin(angle)*sina;

        points->append(QPointF(newX + Common::fromB2(initPos.x()), (newY +Common::fromB2( initPos.y()))));
     }
}

GroundRect::~GroundRect()
{
    if (this->points != NULL)
    {
        delete points;
        points = NULL;
    }
}

QList<QPointF>* GroundRect::getPoints()
{
    return this->points;
}

bool GroundRect::isActive()
{
    return this->shadowActive;
}

QList<QPointF>* GroundRect::addShadow(QPointF light)
{
        int index1 = 0;
        int index2 = 0;
        qreal maxDelta = 0;
        QList<qreal> *angles = new QList<qreal>;

        foreach (QPointF point, *points)
        {
            QLineF line(light,point);
            angles->append(line.angle());
        }
        for (int i = 0; i < 3; i ++)
        {
            for (int j = i + 1; j < 4; j++)
            {
                qreal delta = absAngle(angles->at(i) - angles->at(j));
                if (delta > 180)
                {
                    delta = 360 - delta;
                }
                if (delta > maxDelta)
                {
                    maxDelta = delta;
                    index1 = i;
                    index2 = j;
                }
            }
        }
        QList<QPointF> *list = new QList<QPointF>;
        list->append(this->points->at(index1));
        list->append(this->points->at(index2));
        return list;
}

b2Body* GroundRect::getBody()
{
    return this->body;
}
