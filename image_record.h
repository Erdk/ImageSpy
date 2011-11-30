#ifndef HIST_TUPLE_H
#define HIST_TUPLE_H

#include <QString>

enum ImageState
{
    INDB,    // there's image's histogram in database ready to be fetched
    NOTINDB, // no trace of image at all
    INVALID  // image in invalid state, don't do anything
};

struct image_record
{
    QString filename;
    QString basedir;
    uint*   histogram;
    uint    dimmension;
    uint    distance;

    image_record(QString fn, QString bd, uint* h, uint dim, uint dist = 0) :
        filename(fn),
        basedir(bd),
        histogram(h),
        dimmension(dim),
        distance(dist)
    { }

    void setVar(uint i, uint j, uint k, uint var);
    uint getVar(uint i, uint j, uint k) const;
};

#endif // HIST_TUPLE_H
