#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsScene>
#include <QMainWindow>
#include <QModelIndex>

#include "db.h"
#include "histogram.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    DB* db;
    Histogram* hi;
    QGraphicsScene* scene;
    Ui::MainWindow *ui;

private slots:
    void addDirectory();
    void removeDirectory();

    void createCollection();
    void on_list_pictures_clicked(const QModelIndex &index);
    void on_pushButton_clicked();
};

#endif // MAINWINDOW_H
