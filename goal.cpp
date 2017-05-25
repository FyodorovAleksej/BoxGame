#include "goal.h"
#include<qDebug>
Goal::Goal(QObject *parent) : QObject(parent)
{
    active = true;
}
Goal::Goal( QPointF initPos)
{
    this->active = true;
    setRect(-Common::fromB2(0.1f),-Common::fromB2(0.1f),Common::fromB2(2*0.1f),Common::fromB2(2*0.1f));
    setBrush(QBrush(Qt::red));
    setPos(Common::fromB2(initPos.x()),Common::fromB2(initPos.y()));
}

void Goal::releaseAction()
{
    if (active)
    {
    qDebug() << "goal action";
    timer = new QTimer(this);
    timer->singleShot(300,this,SLOT(stopActive()));
    emit activeSignal();
    active = false;
    }
}
void Goal::stopActive()
{
    this->active = true;
}
