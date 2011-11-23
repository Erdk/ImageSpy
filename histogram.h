#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include "db.h"
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

    QVector<QString> compareHistograms (QString orig_filename, uint* hist_orig, uint dimmension,
                                        QVector< uint* > histograms, QStringList filenames, QString comparer);
};

#endif // HISTOGRAM_H
