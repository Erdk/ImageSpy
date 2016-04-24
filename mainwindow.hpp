#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsScene>
#include <QMainWindow>
#include <QModelIndex>

#include <memory>

#include "img_db.hpp"
#include "histogram.hpp"

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
    std::auto_ptr<ImgDB>          db;
    std::auto_ptr<Histogram>      hi;
    QGraphicsScene* scene;
    QGraphicsScene* scenePreview;
    Ui::MainWindow* ui;

    uint selected_method;

private slots:
    void addDirectory();
    void removeDirectory();

    void createCollection();
    void on_pictureList_clicked(const QModelIndex &index);
    void on_searchButton_clicked();
    void on_similarPictureList_clicked(const QModelIndex &index);
    void on_methodList_currentIndexChanged(int index);
};

#endif // MAINWINDOW_H
