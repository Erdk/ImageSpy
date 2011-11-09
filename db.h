#ifndef DB_H
#define DB_H

#include <QList>
#include <QString>
#include <QVariant>
#include <QStringList>
#include <QtSql/QSqlDatabase>

class DB
{
private:
    QStringList dirList;
    QSqlDatabase db;

    void initDB();

public:
    DB();
    ~DB();

    QStringList* getDirList() { return &dirList; }
    QList<QVariant> getRecords();
    void setRecord(QString baseDir, QString fileName);
};

#endif // DB_H
