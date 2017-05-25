#ifndef GROUNDRECT_H
#define GROUNDRECT_H
#include <QGraphicsItem>
#include<QGraphicsRectItem>
#include<Box2D/Box2D.h>
#include<QBrush>
#include"shadowable.h"
#include<qmath.h>

/**
 * @brief The GroundRect class - the Rectangle with physics of 2dBox, Shadowable - can create shadows
 */
class GroundRect : public QGraphicsRectItem, public Shadowable
{
public:

    /**
     * @brief GroundRect - creating the Rectangle
     * @param world - the world of 2dBox physics
     * @param size - the size of this object
     * @param initPos - the position in Scene (in 2dBox coordinates)
     * @param angle - angle of this object
     * @param active - is active?
     */
    GroundRect(b2World *world,QSizeF size, QPointF initPos, qreal angle, bool active);
    ~GroundRect();

    /**
     * @brief getPoints - getting all 4 points of this Rectangle
     * @return - QList of all 4 points
     */
    QList<QPointF> *getPoints();

    /**
     * @brief isActive - can this object create shadows?
     * @return
     */
    bool isActive();

    /**
     * @brief addShadow - creating shadow
     * @param light - the position of lighting object
     * @return - the list of important points
     */
    QList<QPointF>* addShadow(QPointF light);

    b2Body* getBody();
private:

    /**
     * @brief body - 2dBox analog of this rectangle
     */
    b2Body *body;

    /**
     * @brief points - all points of this rectangle
     */
    QList<QPointF> *points;

    /**
     * @brief shadowActive - is active for shadows?
     */
    bool shadowActive;
};

#endif // GROUNDRECT_H
