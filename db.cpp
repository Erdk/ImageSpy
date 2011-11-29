#include "db.h"
#include <iostream>

#include <QFile>
#include <QTextStream>

#include <QSqlError>
#include <QSqlQuery>
#include <QSqlResult>

#include <QStringList>
#include <QVectorIterator>

DB::~DB()
{
    foreach (hist_tuple* h, *histograms)
    {
        free(h);
    }

    delete histograms;
}

void DB::setRecord(QString baseDir, QString fileName, uint* table, uint dimmensions)
{
    hist_tuple* h = new hist_tuple(QString(baseDir + "/" + fileName), table, dimmensions);
    histograms->append(h);

    if (!dirs.contains(baseDir))
    {
        dirs << baseDir;
    }
}

QStringList DB::getFiles() const
{
    QStringList ret;
    QVector< hist_tuple* >::iterator i;
    for (i = histograms->begin(); i != histograms->end(); ++i)
    {
        ret << (*i)->filename;
    }

    return ret;
}
