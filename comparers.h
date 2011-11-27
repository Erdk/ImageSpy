#ifndef COMPARERS_H
#define COMPARERS_H

typedef unsigned int uint;

class AbstractHistComparer
{
public:
    virtual uint operator ()(uint* h1, uint* h2, uint dimm) = 0;
};

#include <QString>

class ManhatanHistComparer : public AbstractHistComparer
{
public:
    uint operator ()(uint* h1, uint* h2, uint dimm);
};


#endif // COMPARERS_H
