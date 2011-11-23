#include "db.h"
#include <iostream>

#include <QFile>
#include <QTextStream>

#include <QSqlError>
#include <QSqlQuery>
#include <QSqlResult>

#include <QStringList>

DB::~DB()
{
    foreach (uint* h, histograms)
    {
        free(h);
    }
}

void DB::setRecord(QString baseDir, QString fileName, uint* table, uint dimmensions)
{
    filenames << QString(baseDir + "/" + fileName);
    histograms.append(table);
    dimmension.append(dimmensions);
    if (!dirs.contains(baseDir))
    {
        dirs << baseDir;
    }
}
