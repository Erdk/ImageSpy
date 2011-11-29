#ifndef COMPARERS_H
#define COMPARERS_H

#include "hist_tuple.h"

class AbstractHistComparer
{
public:
    virtual uint operator ()(hist_tuple* h1, hist_tuple* h2) = 0;
};

class ManhatanHistComparer : public AbstractHistComparer
{
public:
    uint operator ()(hist_tuple* h1, hist_tuple* h2);
};

class EuklidesHistComparer : public AbstractHistComparer
{
public:
    uint operator ()(hist_tuple* h1, hist_tuple* h2);
};

class CosinusHistComparer : public AbstractHistComparer
{
public:
    uint operator ()(hist_tuple* h1, hist_tuple* h2);
};

class CrossSectionHistComparer : public AbstractHistComparer
{
public:
    uint operator ()(hist_tuple* h1, hist_tuple* h2);
};

class NormCorrelationHistComparer : public AbstractHistComparer
{
public:
    uint operator ()(hist_tuple* h1, hist_tuple* h2);
};


#endif // COMPARERS_H
