#ifndef DB_H
#define DB_H

#include <QList>
#include <QString>
#include <QVariant>
#include <QStringList>

#include <QVector>

#include <cstdlib>

//#include <QSqlDatabase>

class DB
{
private:
    QStringList filenames;
    QStringList dirs;
    QVector< uint* > histograms;
    QVector< uint > dimmension;

public:
    DB() { }
    ~DB();

    void setRecord(QString baseDir, QString fileName, uint* table, uint dimmensions);
    QStringList getFiles() { return filenames; }
};

#endif // DB_H
