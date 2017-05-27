#ifndef INTERACTAVABLE_H
#define INTERACTAVABLE_H

#include <QObject>
#include<QTimer>
#include"common.h"
#include<QGraphicsItem>

class Interactavable :  public QGraphicsEllipseItem
{public:

    /**
     * @brief releaseAction - processing the interact
     */
    virtual void releaseAction() = 0;

protected:

    /**
     * @brief timer - block this object with some time after interact
     */
    QTimer* timer;

    /**
     * @brief active - this object is interacting now?
     */
    bool active;
};

#endif // INTERACTAVABLE_H
