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
//            std::cerr << __FILE__
//                      << ":"
//                      << __LINE__
//                      << " "
//                      << fi.fileName().toStdString()
//                      << std::endl;

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

//            for (uint i = 0; i < colorLevels; i++)
//            {
//                for (uint j = 0; j < colorLevels; j++)
//                {
//                    for (uint k = 0; k < colorLevels; k++)
//                        std::cerr << "[" << i
//                                  << ":" << j
//                                  << ":" << k
//                                  << "](" << *(histogram +
//                                               i * colorLevels * colorLevels +
//                                               j * colorLevels +
//                                               k)
//                                  << ") ";
//                    std::cerr << std::endl;

//                        *(histogram +
//                          i * colorLevels * colorLevels +
//                          j * colorLevels +
//                          k) *= (262144 / (height * width));
//                }
//            }

            // TODO: create optimised histogram and store in db
            db->setRecord(fi.absolutePath(),
                          fi.fileName(),
                          histogram,
                          colorLevels);
        }
    }
}

bool sortHistTuples(const hist_tuple* s1, const hist_tuple* s2)
{
    return s1->distance < s2->distance;
}

QStringList Histogram::compareHistograms(hist_tuple* orig_hist,
                                         QVector< hist_tuple* >* histograms,
                                         AbstractHistComparer* comp)
{
    // vector of filenames to return
    QStringList ret;

    foreach (hist_tuple* u, *histograms)
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

           // u->distance = (*comp)(orig_hist->histogram, u->histogram, u->dimmension);
            u->distance = ret;
        }
        else
        {
            u->distance = 0;
        }
    }

    qSort(histograms->begin(), histograms->end(), sortHistTuples);

    for (int i = 1; i < 6 && i < histograms->size(); i++)
    {
        ret << histograms->at(i)->filename;
    }

    return ret;
}
