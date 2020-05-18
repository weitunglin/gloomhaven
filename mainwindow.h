#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <iostream>
#include <vector>
#include <algorithm>

#include "gloomhaven.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Gloomhaven* game;
    void showMap();
    void drawBlock(QGraphicsScene * scene, int r, int c, std::vector<Point2d>& traveled, int itemWidth, int itemHeight);
    bool inVision(Point2d p);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
