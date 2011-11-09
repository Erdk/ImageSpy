#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    hi(new Histogram),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    try
    {
        db = new DB();
    }
    catch (const char* ex)
    {
        db = NULL;
        qDebug(ex);
    }

    if (db)
    {
        QStringList* dirList = db->getDirList();
        if (dirList->count() > 0)
        {
            ui->listWidget->addItems(*dirList);
        }
    }
}

MainWindow::~MainWindow()
{
    delete db;
    delete ui;
}

void MainWindow::addDirectory()
{
    QString fileName = QFileDialog::getExistingDirectory(this, "Wybierz katalog", "/home/erdk");
    ui->listWidget->addItem(new QListWidgetItem(fileName));
}

void MainWindow::removeDirectory()
{
    qDeleteAll(ui->listWidget->selectedItems());
}

void MainWindow::createCollection()
{
    QList<QString> list;
    for (int i = 0; i < ui->listWidget->count(); i++)
    {
        list.push_back(ui->listWidget->item(i)->text());
    }

    hi->createCollection(db, list);
}
