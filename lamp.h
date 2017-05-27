#ifndef LAMP_H
#define LAMP_H

#include <QGraphicsEllipseItem>
#include<Box2D/Box2D.h>
#include<QGraphicsItem>
#include<QBrush>
#include<QObject>
#include<QGraphicsScene>
#include"common.h"
#include"lightable.h"
#include"interactavable.h"

/**
 * @brief The Lamp class - the interactive object, that can turn ON/OFF and create shadows for other objects
 */
class Lamp : public QObject, public Interactavable, public Lightable
{
    Q_OBJECT
public:
    explicit Lamp(QObject* parent = 0);

    /**
     * @brief Lamp - creating lamp
     * @param radius - the radius of this lamp
     * @param initPos - position of lamp
     * @param on - is ON?
     */
    Lamp(qreal radius, QPointF initPos, bool on);

    /**
      * @brief ~Lamp - deleting this interactive lamp
      */
    ~Lamp();

    /**
     * @brief getLight - getting coordinates of the center
     * @return - coordinates of center
     */
    QPointF getLight();

    /**
     * @brief isOn - is lamp was ON?
     * @return - lamp was ON?
     */
    bool isOn();

    /**
     * @brief isActive - isOn?
     * @return  isOn
     */
    bool isActive();

    /**
     * @brief releaseAction - processing interacting
     */
    void releaseAction();
signals:

public slots:

    /**
     * @brief stopActive - reactivate this interactive object
     */
    void stopActive();
private:

    /**
     * @brief ready - is ready to interact?
     */
    bool ready = true;

    /**
     * @brief radius - radius of Lamp
     */
    qreal radius;
};

#endif // LAMP_H
