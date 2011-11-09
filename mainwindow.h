#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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
    Ui::MainWindow *ui;

public slots:
    void addDirectory();
    void removeDirectory();

    void createCollection();
};

#endif // MAINWINDOW_H
