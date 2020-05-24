#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QStyleOptionGraphicsItem>
#include <QThread>
#include <QTimer>
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
    void drawBlock(QGraphicsScene * scene, int r, int c, std::vector<Point2d>& traveled);
    bool inVision(Point2d p);
    void selectCharacterPos();
    void start();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    int itemWidth;
    int itemHeight;

public slots:
    void selectedChange();
    void nothing();
};
#endif // MAINWINDOW_H
