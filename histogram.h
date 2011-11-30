#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include "db.h"
#include "comparers.h"

#include <QImage>

class Histogram
{
private:
    const uint colorLevels;
    void makeHistogram(QImage img);

public:
    Histogram();
    void createCollection(DB* db, QStringList* dirs);
    QVector< int > compareHistograms (image_record* orig_hist,
                                      QVector< image_record* >* histograms,
                                      AbstractHistComparer* comp);
};

#endif // HISTOGRAM_H
