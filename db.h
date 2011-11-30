#ifndef DB_H
#define DB_H

#include <QString>
#include <QVector>
#include <QStringList>

#include <QSqlDatabase>

#include "image_record.h"

class DB
{
private:
    QSqlDatabase              db;
    QStringList               dirs;
    QVector< image_record* >* histograms;

public:
    DB();
    ~DB();

    // for Histogram to access Images database
    void setRecord(QString baseDir, QString fileName, uint* table, uint dimmensions);
    image_record* getRecord(QString baseDir, QString fileName);

    // for Histogram, to check image state
    ImageState checkImageState(QString filename, QString baseDir);

    // for MainWindow, to get list of current images
    QStringList getFiles() const;

    image_record* getHistogram(uint index) const { return histograms->at(index); }

    QVector< image_record* >* getHistograms() const { return histograms; }

    void cleanHistogramList(QStringList* validDirs);
};

#endif // DB_H
