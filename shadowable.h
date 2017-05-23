#ifndef SHADOWABLE_H
#define SHADOWABLE_H
#include<QPointF>

class Shadowable
{
public:
    Shadowable();
    virtual bool isActive() = 0;
    virtual QList<QPointF>* addShadow(QPointF light) = 0;
};

#endif // SHADOWABLE_H
