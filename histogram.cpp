#include "histogram.h"

#include <QDir>
#include <QColor>
#include <QImage>
#include <cstdlib>

#include <iostream>

Histogram::Histogram() :
    colorLevels(16)
{
}

void Histogram::createCollection(DB* db, QStringList* dirs)
{
    db->cleanHistogramList(dirs);

    foreach(QString qs, *dirs)
    {
        // catalogue with psictures
        QDir qdir(qs);

        // which extensions will be accepted
        QStringList filters;
        filters << "*.jpg";
        filters << "*.jpeg";
        filters << "*.png";
        qdir.setNameFilters(filters);

        qdir.setFilter(QDir::Files | QDir::Readable);
        QFileInfoList fileInfo = qdir.entryInfoList();

        foreach (QFileInfo fi, fileInfo)
        {
            ImageState is = db->checkImageState(fi.fileName(), fi.absolutePath());

            // image not in DB
            if (is == NOTINDB)
            {
                uint* histogram;
                histogram = (uint*) malloc (colorLevels * colorLevels *
                                            colorLevels * sizeof(uint));

                memset (histogram, 0, colorLevels * colorLevels *
                        colorLevels * sizeof(uint));

                QImage qi(fi.absoluteFilePath());
                const uint height = qi.height();
                const uint width = qi.width();

                for (uint i = 0; i < height; i++)
                {
                    for (uint j = 0; j < width; j++)
                    {
                        // getting color from bitmap
                        QRgb rgb = qi.pixel(j, i);

                        // for each color channel
                        // getting color value
                        uint r = qRed(rgb);

                        // scaling value to our representation
                        // (for case, when there will be need for
                        //  more / less colors)
                        r /= (256 / colorLevels);

                        uint g = qGreen(rgb);
                        g /= (256 / colorLevels);

                        uint b = qBlue(rgb);
                        b /= (256 / colorLevels);

                        *(histogram +
                          r * colorLevels * colorLevels +
                          g * colorLevels +
                          b) += 1;
                    }
                }
                db->setRecord(fi.absolutePath(),
                              fi.fileName(),
                              histogram,
                              colorLevels);
            }
            else if (is == INDB)
            {
                // get image from DB
            }
        }
    }
}

// helper function for comparing histograms distances
bool sortHistTuples(const image_record* s1, const image_record* s2)
{
    return s1->distance < s2->distance;
}

// comparing histograms using chosen method (child of AbstractHistComparer
// and return list of most similar
QVector< int > Histogram::compareHistograms(image_record* orig_hist,
                                         QVector< image_record* >* histograms,
                                         AbstractHistComparer* comp)
{
    // vector of filenames to return
    QVector< int > ret;

    foreach (image_record* u, *histograms)
    {
        if (orig_hist != u)
        {
            uint ret = 0;
            uint dimm = u->dimmension;
            for (uint i = 0; i < dimm; i++)
            {
                for (uint j = 0; j < dimm; j++)
                {
                    for (uint k = 0; k < dimm; k++)
                    {
                        uint a = orig_hist->getVar(i, j, k);
                        uint b = u->getVar(i, j, k);
                        ret += std::abs((int)(a - b));
                    }
                }
            }

            u->distance = (*comp)(orig_hist, u);
            //u->distance = ret;
        }
        else
        {
            u->distance = 0;
        }
    }

    QVector< image_record* >* histograms_copy = new QVector< image_record* >(histograms->count());
    qCopy(histograms->begin(), histograms->end(), histograms_copy->begin());
    qSort(histograms->begin(), histograms->end(), sortHistTuples);

    for (int i = 1; i < 6 && i < histograms->size(); i++)
    {       
        ret << histograms_copy->indexOf(histograms->at(i));
    }

    qCopy(histograms_copy->begin(), histograms_copy->end(), histograms->begin());
    delete histograms_copy;
    return ret;
}
