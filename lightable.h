#ifndef LIGHTABLE_H
#define LIGHTABLE_H
#include<QPointF>

/**
 * @brief The Lightable class - the lightable object
 */
class Lightable
{
public:
    Lightable();

    /**
     * @brief getLight - getting center of light
     * @return coordinates of center (in QGraphicsScene coordintes)
     */
    virtual QPointF getLight() = 0;

    /**
     * @brief isActive - is ON?
     * @return ON?
     */
    virtual bool isActive() = 0;
};

#endif // LIGHTABLE_H
