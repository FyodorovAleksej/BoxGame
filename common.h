#ifndef COMMON_H
#define COMMON_H
#include <QtGlobal>

/**
  @brief SCALE - the scale coordinates of 2dBox/QGraphicsScene
  */
#define SCALE 100

class Common
{
public:
    Common();

    /**
     * @brief fromB2 - transform coordinates from 2dBox to QGraphicsScene
     * @param value - coordinates in 2dBox system
     * @return  - coordinates in QGraphicsScene system
     */
    static qreal fromB2(qreal value);

    /**
     * @brief toB2 - transform coordinates from QGraphicsScene to 2dBox system
     * @param value - coordinates in QGraphicsScene system
     * @return - coordinates in 2dBox system
     */
    static qreal toB2(qreal value);
};

#endif // COMMON_H
