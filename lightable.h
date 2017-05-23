#ifndef LIGHTABLE_H
#define LIGHTABLE_H
#include<QPointF>

class Lightable
{
public:
    Lightable();
    virtual QPointF getLight() = 0;
};

#endif // LIGHTABLE_H
