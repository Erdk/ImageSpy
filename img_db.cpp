#include "img_db.hpp"
#include <iostream>

#include <QFile>
#include <QTextStream>

#include <QSqlError>
#include <QSqlQuery>
#include <QSqlResult>

#include <QStringList>
#include <QVectorIterator>

ImgDB::ImgDB() : histograms(new QVector< image_record* >()) { }

ImgDB::~ImgDB() {
    foreach (image_record* h, *histograms)
        free(h);

    delete histograms;
}

void ImgDB::setRecord(QString baseDir, QString fileName, uint* table, uint dimmensions) {
    image_record* h = new image_record(fileName, baseDir, table, dimmensions);
    histograms->append(h);

    if (!dirs.contains(baseDir))
        dirs << baseDir;
}

// TODO: stub
image_record* ImgDB::getRecord(QString baseDir, QString fileName) {
    return NULL;
}

QStringList ImgDB::getFiles() const {
    QStringList ret;
    QVector< image_record* >::iterator i;
    for (i = histograms->begin(); i != histograms->end(); ++i)
        ret << (*i)->filename;

    return ret;
}

// function checking wheteher we've got the image in database and it's baseDir
// is in current diretories list
// TODO: stub
ImageState ImgDB::checkImageState(QString filename, QString baseDir) {
    foreach (image_record* i, *histograms)
        if (i->filename.compare(filename) == 0 &&
                i->basedir.compare(baseDir) == 0)
            return INDB;

    return NOTINDB;
}

void ImgDB::cleanHistogramList(QStringList *validDirs) {
    for (int i = histograms->count() - 1; i >= 0; i--)
        if (!validDirs->contains(histograms->at(i)->basedir))
            histograms->remove(i);
}
