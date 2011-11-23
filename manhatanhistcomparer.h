#ifndef MANHATANHISTCOMPARER_H
#define MANHATANHISTCOMPARER_H

#include "abstracthistcomparer.h"

#include <QString>

class ManhatanHistComparer : public AbstractHistComparer
{
public:
    uint operator ()(uint* h1, uint* h2, uint dimm) const;
};

#endif // MANHATANHISTCOMPARER_H
