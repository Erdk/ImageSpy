#include "histogram.h"

#include <QDir>

Histogram::Histogram()
{
}

void Histogram::createCollection(DB* db, QList<QString>& dirs)
{
    foreach(QString qs, dirs)
    {
        qDebug("W Histogram::createCollection");
        QDir qdir(qs);
        QStringList filters;
        filters << "*.jpg" << "*.png";
        qdir.setNameFilters(filters);
        qdir.setFilter(QDir::Files | QDir::Readable);
        QFileInfoList fileInfo = qdir.entryInfoList();
        foreach (QFileInfo fi, fileInfo)
        {
            qDebug(fi.fileName().toAscii());
            db->setRecord(fi.absolutePath(), fi.fileName());
        }
    }
}
