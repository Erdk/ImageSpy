#ifndef DB_H
#define DB_H

#include <QList>
#include <QString>
#include <QVariant>
#include <QStringList>

#include <QVector>

#include <cstdlib>

struct hist_tuple
{
    QString filename;
    uint* histogram;
    uint dimmension;
    uint distance;

    hist_tuple(QString fn, uint* h, uint dim, uint dist = 0) :
        filename(fn),
        histogram(h),
        dimmension(dim),
        distance(dist)
    { }

    void setVar(uint i, uint j, uint k, uint var);
    uint getVar(uint i, uint j, uint k) const;
};

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
