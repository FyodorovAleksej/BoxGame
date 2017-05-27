#include "lamp.h"
#include <QDebug>
Lamp::Lamp(QObject* parent):QObject(parent)
{
}


Lamp::Lamp(qreal radius, QPointF initPos, bool on)
{
    setRect(-Common::fromB2(radius),-Common::fromB2(radius),Common::fromB2(2*radius),Common::fromB2(2*radius));
    this->radius = radius;
    if (on)
    {
        setBrush(QBrush(Qt::yellow));
    }
    else
    {
        setBrush(QBrush(Qt::gray));
    }
    active = on;
    setPos(Common::fromB2(initPos.x()),Common::fromB2(initPos.y()));
}

Lamp::~Lamp()
{
    if (this->timer != NULL)
    {
        timer = NULL;
    }
}

QPointF Lamp::getLight()
{
    return this->pos();
}

bool Lamp::isOn()
{
    return this->active;
}
void Lamp::releaseAction()
{
    if (ready)
    {
        active = !active;
        if (active)
        {
            setBrush(Qt::yellow);
        }
        else
        {
            setBrush(Qt::gray);
        }
        this->update();
        this->timer = new QTimer(this);
        this->ready = false;
        timer->singleShot(300,this, SLOT(stopActive()));
        // qDebug() << "lamp Action";
    }
}

void Lamp::stopActive()
{
    this->ready = true;
}
bool Lamp::isActive()
{
    return active;
}
