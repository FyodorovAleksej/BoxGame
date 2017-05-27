#include "common.h"

Common::Common()
{

}

/**
 * @brief Common::fromB2 - transforming coordinates from b2World
 * @param value
 * @return
 */
qreal Common::fromB2(qreal value)
{
    return value*SCALE;
}

/**
 * @brief Common::toB2 - transforming coordinates to b2World
 * @param value
 * @return
 */
qreal Common::toB2(qreal value)
{
    return value/SCALE;
}
