#include "common.h"

Common::Common()
{

}

qreal Common::fromB2(qreal value)
{
    return value*SCALE;
}

qreal Common::toB2(qreal value)
{
    return value/SCALE;
}
