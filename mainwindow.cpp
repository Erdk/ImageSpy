#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QList>
#include <QFileDialog>
#include <QStringList>
#include <QStringListModel>
#include <QPixmap>
#include <QItemSelectionModel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    hi(new Histogram),
    selected_method(0),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    try
    {
        db = new DB();
    }
    catch (const char* ex)
    {
        this->~MainWindow();

        qDebug(ex);

        exit(1);
    }

    scene = new QGraphicsScene();
    scenePreview = new QGraphicsScene();

    ui->image_preview->setScene(scene);
    ui->similarPreview->setScene(scenePreview);
}

MainWindow::~MainWindow()
{
    delete db;
    delete hi;
    delete ui;
    delete scene;
    delete scenePreview;
}

void MainWindow::addDirectory()
{
    QString fileName = QFileDialog::getExistingDirectory(this, "Wybierz katalog", "/home/erdk");
    ui->folderList->addItem(new QListWidgetItem(fileName));
}

void MainWindow::removeDirectory()
{
    qDeleteAll(ui->folderList->selectedItems());
}

void MainWindow::createCollection()
{
    QStringList list;
    for (int i = 0; i < ui->folderList->count(); i++)
    {
        list << ui->folderList->item(i)->text();
    }

    hi->createCollection(db, &list);
    QStringList files = db->getFiles();
    QStringListModel* files_model = new QStringListModel();
    files_model->setStringList(files);

    ui->list_pictures->setModel(files_model);
}

void MainWindow::on_list_pictures_clicked(const QModelIndex &index)
{
    QString s = index.data().toString();
    QPixmap qpx = QPixmap(s).scaled(ui->image_preview->size(), Qt::KeepAspectRatio);

    scene->clear();
    scene->addPixmap(qpx);

    ui->image_preview->show();
}

void MainWindow::on_list_similar_clicked(const QModelIndex &index)
{
    QString s = index.data().toString();
    QPixmap qpx = QPixmap(s).scaled(ui->similarPreview->size(), Qt::KeepAspectRatio);

    scenePreview->clear();
    scenePreview->addPixmap(qpx);

    ui->similarPreview->show();
}

void MainWindow::on_searchButton_clicked()
{
    // this method compares histograms and shows 5 most similar to our main image
    // 1. get selected image index -> histogram
    // 2. compare to other images histograms by method selected in combobox
    // 3. sort from smallest to greatest
    // 4. show top 5

    AbstractHistComparer* ahc;

    qDebug(ui->methodList->itemText(selected_method).toAscii());
    switch(selected_method)
    {
    case 0:
        ahc = new ManhatanHistComparer();
        break;
    case  1:
        ahc = new EuklidesHistComparer();
        break;
    case 2:
        ahc = new CrossSectionHistComparer();
        break;
    case 3:
        ahc = new NormCorrelationHistComparer();
        break;
    }

    QItemSelectionModel* qism = ui->list_pictures->selectionModel();
    int row = qism->currentIndex().row();

    if (row > 0)
    {
        QStringList r = hi->compareHistograms(db->getHistogram(row),
                                              db->getHistograms(),
                                              ahc);
        QStringListModel* ret_model = new QStringListModel();
        ret_model->setStringList(r);

        QItemSelectionModel *m = ui->list_similar->selectionModel();
        ui->list_similar->setModel(ret_model);
        if (m != NULL)
        {
            delete m;
        }

        // updateing filelist
        QStringList files = db->getFiles();
        QStringListModel* files_model = new QStringListModel();
        files_model->setStringList(files);

        m = ui->list_pictures->selectionModel();
        ui->list_pictures->setModel(files_model);
        delete m;
    }

    delete ahc;
}

void MainWindow::on_methodList_currentIndexChanged(int index)
{
    selected_method = index;
}
