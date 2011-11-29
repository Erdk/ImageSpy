#ifndef DB_H
#define DB_H

#include <QString>
#include <QVector>
#include <QStringList>

#include "hist_tuple.h"

class DB
{
private:
    QStringList dirs;
    QVector< hist_tuple* >* histograms;

public:
    DB() : histograms(new QVector< hist_tuple* >())
    { }
    ~DB();

    void setRecord(QString baseDir, QString fileName, uint* table, uint dimmensions);

    QStringList getFiles() const;
    hist_tuple* getHistogram(uint index) const { return histograms->at(index); }
    QVector< hist_tuple* >* getHistograms() const { return histograms; }
};

#endif // DB_H
