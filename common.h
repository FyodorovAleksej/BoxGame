#ifndef COMMON_H
#define COMMON_H
#include <QtGlobal>

#define SCALE 100

class Common
{
public:
    Common();
    static qreal fromB2(qreal value);
    static qreal toB2(qreal value);
};

#endif // COMMON_H
