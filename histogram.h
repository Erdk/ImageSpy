#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include "db.h"

class Histogram
{
private:
    void makeHistogram(QImage img);

public:
    Histogram();

    void createCollection(DB* db, QList<QString>& dirs);

    void doHistogram();
};

#endif // HISTOGRAM_H
