#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include <QObject>
#include <QList>
#include <QFileDialog>
#include <QStringList>
#include <QStringListModel>
#include <QPixmap>
#include <QItemSelectionModel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    hi(new Histogram),
    ui(new Ui::MainWindow),
    selected_method(0) {
    ui->setupUi(this);
    try {
        db.reset(new ImgDB());
    }
    catch (const char* ex) {
        this->~MainWindow();

        qDebug(ex);

        exit(1);
    }

    scene = new QGraphicsScene();
    scenePreview = new QGraphicsScene();

    ui->imagePreview->setScene(scene);
    ui->similarPreview->setScene(scenePreview);
}

MainWindow::~MainWindow() {
    delete ui;
    delete scene;
    delete scenePreview;
}

void MainWindow::addDirectory() {
    QString fileName = QFileDialog::getExistingDirectory(this, "Wybierz katalog", QDir::homePath());
    ui->folderList->addItem(new QListWidgetItem(fileName));
}

void MainWindow::removeDirectory() {
    qDeleteAll(ui->folderList->selectedItems());
    createCollection();

    scene->clear();
    scenePreview->clear();

    ui->similarPictureList->setModel(NULL);
}

void MainWindow::createCollection() {
    QStringList list;
    for (int i = 0; i < ui->folderList->count(); i++)
        list << ui->folderList->item(i)->text();

    hi->createCollection(db, &list);
    QStringList files = db->getFiles();
    QStringListModel* files_model = new QStringListModel();
    files_model->setStringList(files);

    ui->pictureList->setModel(files_model);
}

// action which show image in preview area
void MainWindow::on_pictureList_clicked(const QModelIndex &index) {
    image_record* ir = db->getHistogram(index.row());
    QString s = ir->basedir + "/" + ir->filename;
    s = QDir::toNativeSeparators(s);
    QPixmap qpx = QPixmap(s).scaled(ui->imagePreview->size(), Qt::KeepAspectRatio);

    scene->clear();
    scene->addPixmap(qpx);

    ui->imagePreview->show();
}

// action which show image in similar preview area
// BUG: figure out hiding additional info in model and presenting it by
// widget
// for now: dirty hack
void MainWindow::on_similarPictureList_clicked(const QModelIndex &index) {
    QString s = QDir::toNativeSeparators(index.data().toString());
    QPixmap qpx = QPixmap(s).scaled(ui->similarPreview->size(), Qt::KeepAspectRatio);

    scenePreview->clear();
    scenePreview->addPixmap(qpx);

    ui->similarPreview->show();
}

void MainWindow::on_searchButton_clicked() {
    // this method compares histograms and shows 5 most similar to our main image
    // 1. get selected image index -> histogram
    // 2. compare to other images histograms by method selected in combobox
    // 3. sort from smallest to greatest
    // 4. show top 5

    std::auto_ptr<AbstractHistComparer> ahc;

    switch(selected_method) {
        case 0:
            ahc.reset(new ManhatanHistComparer());
            break;
        case  1:
            ahc.reset(new EuklidesHistComparer());
            break;
        case 2:
            ahc.reset(new CrossSectionHistComparer());
            break;
        case 3:
            ahc.reset(new NormCorrelationHistComparer());
            break;
        case 4:
            ahc.reset(new MediumLumaHistComparer());
            break;
        case 5:
            ahc.reset(new VarianceHistComparer());
            break;
        case 6:
            ahc.reset(new JeffreyHistComparer());
            break;
        case 7:
            ahc.reset(new KullbackHistComparer());
            break;
        case 8:
            ahc.reset(new ChiHistComparer());
    }

    QItemSelectionModel* qism = ui->pictureList->selectionModel();
    int row = qism->currentIndex().row();

    if (row >= 0) {
        QVector<int> r = hi->compareHistograms(db->getHistogram(row),
                                               db->getHistograms(),
                                               ahc);
        QStringList qsl;
        for (int i = 0; i < r.count(); i++) {
            image_record* ir = db->getHistogram(r.at(i));
            qsl << QString("%1/%2").arg(ir->basedir).arg(ir->filename);
        }

        QStringListModel* ret_model = new QStringListModel();
        ret_model->setStringList(qsl);

        QItemSelectionModel *m = ui->similarPictureList->selectionModel();
        ui->similarPictureList->setModel(ret_model);
        if (m != NULL)
            delete m;
    }
}

void MainWindow::on_methodList_currentIndexChanged(int index) {
    selected_method = index;
}
