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

GroundRect::GroundRect(b2World *world, QSizeF size, QPointF initPos, qreal angle)
    :QGraphicsRectItem(0)
{
    this->shadowActive = false;

    qreal newWidth = Common::fromB2(size.width()/2);
    qreal newHeight = Common::fromB2(size.height()/2);

    QPointF mas1[4] = {QPointF(newWidth, newHeight),QPointF( -newWidth, newHeight),QPointF(newWidth, -newHeight),QPointF(-newWidth, -newHeight)};
    for (int  i = 0; i < 4; i++)
    {
         //qDebug() << "before rotate x - " <<  mas1[i].x() + Common::fromB2(initPos.x()) << "; y - " << mas1[i].y() + Common::fromB2(initPos.y()) << endl;
    }
    //qDebug() << endl;
    setRect(-newWidth,-newHeight,newWidth*2, newHeight*2);
    setBrush(QBrush(Qt::gray));
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
    qreal radius = sqrt(sqr2(newWidth) + sqr2(newHeight));
    //qDebug() << "radius - " << radius << "\n\n";
    QPointF mas[4] = {QPointF(newWidth, newHeight),QPointF( -newWidth, newHeight),QPointF(newWidth, -newHeight),QPointF(-newWidth, -newHeight)};
     for (int i = 0; i < 4; i++)
     {
        qreal cosa = mas[i].x();
        qreal sina = mas[i].y();

        qreal newY = sin(angle)*cosa + cos(angle)*sina;
        qreal newX = cos(angle)*cosa - sin(angle)*sina;

        //qDebug() << "\nnew sin - " << sin(angle)*cosa + cos(angle)*sina << "\n";
        points->append(QPointF(newX + Common::fromB2(initPos.x()), (newY +Common::fromB2( initPos.y()))));

        //qDebug() << "after rotate: x - " << newX + Common::fromB2(initPos.x()) << "; y - " << newY + Common::fromB2(initPos.y()) << endl;
     }
}
GroundRect::~GroundRect()
{
    body->GetWorld()->DestroyBody(body);
}
QList<QPointF>* GroundRect::getPoints()
{
    return this->points;
}
CircleObject* GroundRect::getHero()
{
    return this->hero;
}
void GroundRect::setHero(CircleObject *hero)
{
    this->hero = hero;
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
            //qDebug() << "size of points for shadow - " << points->size();
            qreal y = point.y() - light.y();
            qreal x = point.x() - light.x();
            qreal tang = y/x;
            qreal angle = atan(absAngle(tang));
            if (x < 0 && y < 0)
            {
                angle += 3.14/2;
            }
            if (x < 0 && y >= 0)
            {
                angle += 3.14;
            }
            if (x >= 0 && y >= 0)
            {
                angle += 3.14*3/2;
            }
            angles->append(angle);
             //qDebug() << "angle for shadow - " << angle;
        }
        for (int i = 0; i < 3; i ++)
        {
            for (int j = i + 1; j < 4; j++)
            {
                qreal delta = absAngle(angles->at(i) - angles->at(j));
                //qDebug() << "delta - " << delta;
                if (delta > 3.14)
                {
                    delta = 3.14*2 - delta;
                }
                if (delta > maxDelta)
                {
                    maxDelta = delta;
                    index1 = i;
                    index2 = j;
                }
            }
            //qDebug() << "index1 - " << index1 << "; index2 - " << index2;
        }
        QList<QPointF> *list = new QList<QPointF>;
        list->append(this->points->at(index1));
        list->append(this->points->at(index2));
        return list;
}
