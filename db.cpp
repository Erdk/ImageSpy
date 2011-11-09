#include "db.h"
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlResult>
#include <QStringList>

DB::DB()
{
    bool connectionStatus = false;
    db = QSqlDatabase::addDatabase("QSQLITE", "db");
    db.setDatabaseName("image_spy.sqlite");

    connectionStatus = db.open();

    if (!connectionStatus)
    {
        throw "No connection with database!";
    }

    if (db.tables().count() == 0)
    {
        initDB();
    }
    else
    {
        QSqlQuery q(db);
        q.exec("SELECT DISTINCT dir FROM obrazki");
        qDebug(q.lastError().text().toAscii());
        while (q.next())
        {
            dirList << q.value(0).toString();
        }
    }
}

DB::~DB()
{
    db.close();
}

void DB::initDB()
{
    QSqlQuery q(db);
    q.exec("CREATE TABLE obrazki(dir varchar(80),name varchar(80))");
}

void DB::setRecord(QString baseDir, QString fileName)
{
    QSqlQuery q(db);

    // first we check if we've got image in our database
    q.prepare("SELECT dir, name FROM obrazki WHERE dir = :dir AND name = :name");
    q.bindValue(":dir", baseDir);
    q.bindValue(":name", fileName);
    q.exec();

    // q.size == 0 means we don't have image in our database
    if (!q.size())
    {
        q.prepare("INSERT INTO obrazki(dir, name) VALUES (:dir, :name)");
        q.bindValue(":dir", baseDir);
        q.bindValue(":name", fileName);
        q.exec();
        qDebug("record set");
    }
    else
    {
        qDebug("image already in db");
    }
}

QList<QVariant> DB::getRecords()
{
    QList<QVariant> ret;
    QSqlQuery q(db);
    q.exec("SELECT * FROM obrazki");
    while(q.next())
    {
        ret.append(QVariant(q.value(0).toString() + q.value(1).toString()));
    }

    return ret;
}
