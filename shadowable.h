#ifndef SHADOWABLE_H
#define SHADOWABLE_H
#include<QPointF>

/**
 * @brief The Shadowable class - class of objects, that can create shadows
 */
class Shadowable
{
public:
    Shadowable();

    /**
     * @brief isActive - can this object create shadows?
     * @return - can this object create shadows?
     */
    virtual bool isActive() = 0;

    /**
     * @brief addShadow - compute points, that was being important for creating shadow of this object from the current light
     * @param light - current point of Light
     * @return QList<QPointF>* - the list of important points for creating shadow
     */
    virtual QList<QPointF>* addShadow(QPointF light) = 0;
};

#endif // SHADOWABLE_H
