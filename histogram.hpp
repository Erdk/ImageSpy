#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include <memory>

#include "img_db.hpp"
#include "comparers.hpp"

#include <QImage>

class Histogram
{
private:
    const uint colorLevels;
    void makeHistogram(QImage img);

public:
    Histogram();
    void createCollection(std::auto_ptr<ImgDB>& db, QStringList* dirs);
    QVector< int > compareHistograms (image_record* orig_hist,
                                      QVector< image_record* >* histograms,
                                      std::auto_ptr<AbstractHistComparer>& comp);
};

#endif // HISTOGRAM_H
