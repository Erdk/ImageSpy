#include "db.h"
#include <iostream>

#include <QFile>
#include <QTextStream>

#include <QSqlError>
#include <QSqlQuery>
#include <QSqlResult>

#include <QStringList>
#include <QVectorIterator>

uint hist_tuple::getVar(uint i, uint j, uint k) const
{
    return *(histogram + i * dimmension * dimmension + j * dimmension + k);
}

void hist_tuple::setVar(uint i, uint j, uint k, uint var)
{
    *(histogram + i * dimmension * dimmension + j * dimmension + k) = var;
}

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
