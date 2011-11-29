#ifndef HIST_TUPLE_H
#define HIST_TUPLE_H

#include <QString>

struct hist_tuple
{
    QString filename;
    uint* histogram;
    uint dimmension;
    uint distance;

    hist_tuple(QString fn, uint* h, uint dim, uint dist = 0) :
        filename(fn),
        histogram(h),
        dimmension(dim),
        distance(dist)
    { }

    void setVar(uint i, uint j, uint k, uint var);
    uint getVar(uint i, uint j, uint k) const;
};

#endif // HIST_TUPLE_H
