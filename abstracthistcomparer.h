#ifndef ABSTRACTHISTCOMPARER_H
#define ABSTRACTHISTCOMPARER_H

typedef unsigned int uint;

class AbstractHistComparer
{
public:
    virtual uint operator ()(uint* h1, uint* h2, uint dimm) = 0;
};

#endif // ABSTRACTHISTCOMPARER_H
