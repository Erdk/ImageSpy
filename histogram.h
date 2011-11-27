#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include "db.h"
#include "comparers.h"

#include <QStringList>

class Histogram
{
private:
    const uint colorLevels;
    void makeHistogram(QImage img);

public:
    Histogram();

    void createCollection(DB* db, QStringList* dirs);

    void doHistogram();

    QStringList compareHistograms (hist_tuple* orig_hist,
                                   QVector< hist_tuple* >* histograms,
                                   AbstractHistComparer* comp);
};

#endif // HISTOGRAM_H
