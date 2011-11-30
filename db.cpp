#include "db.h"
#include <iostream>

#include <QFile>
#include <QTextStream>

#include <QSqlError>
#include <QSqlQuery>
#include <QSqlResult>

#include <QStringList>
#include <QVectorIterator>

DB::DB() : histograms(new QVector< image_record* >())
{

}

DB::~DB()
{
    foreach (image_record* h, *histograms)
    {
        free(h);
    }

    delete histograms;
}

void DB::setRecord(QString baseDir, QString fileName, uint* table, uint dimmensions)
{
    image_record* h = new image_record(fileName, baseDir, table, dimmensions);
    histograms->append(h);

    if (!dirs.contains(baseDir))
    {
        dirs << baseDir;
    }
}

// TODO: stub
image_record* DB::getRecord(QString baseDir, QString fileName)
{
    return NULL;
}

QStringList DB::getFiles() const
{
    QStringList ret;
    QVector< image_record* >::iterator i;
    for (i = histograms->begin(); i != histograms->end(); ++i)
    {
        ret << (*i)->filename;
    }

    return ret;
}

// function checking whetaher we've got image in database and it's baseDir
// is in current diretories list
// TODO: stub
ImageState DB::checkImageState(QString filename, QString baseDir)
{
    foreach (image_record* i, *histograms)
    {
        if (i->filename.compare(filename) == 0 && i->basedir.compare(baseDir) == 0)
            return INDB;
    }

    return NOTINDB;
}

void DB::cleanHistogramList(QStringList *validDirs)
{
    for (int i = histograms->count() - 1; i >= 0; i--)
    {
        if (!validDirs->contains(histograms->at(i)->basedir))
        {
            histograms->remove(i);
        }
    }
}
