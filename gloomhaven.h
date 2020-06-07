#ifndef GLOOMHAVEN_H
#define GLOOMHAVEN_H

#include <QMainWindow>
#include <QWidget>
#include <QFile>
#include <QTextStream>
#include <QDataStream>
#include <QInputDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QStyleOptionGraphicsItem>
#include <QAbstractItemView>
#include <QPushButton>
#include <QString>
#include <QtDebug>
#include <string>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <random>
#include <math.h>

#include "character.h"
#include "characterdata.h"
#include "monster.h"
#include "monsterdata.h"
#include "map.h"
#include "ui_gloomhaven.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Gloomhaven;
}
QT_END_NAMESPACE

#define trace(x) { std::cout << #x << ": " << x << std::endl; }

class Gloomhaven : public QMainWindow, public CharacterData, public MonsterData, public Map
{
    Q_OBJECT

public:
    explicit Gloomhaven(QWidget *parent = nullptr);
    Gloomhaven(QString cFilename = "character1.txt", QString mFilename = "monster1.txt", int mode = 0);
    ~Gloomhaven();
    void preGameInput();
    void loop();
    void showMap();
    void drawBlock(QGraphicsScene* scene, int r, int c, std::vector<Point2d>& traveled);
    bool inVision(Point2d p);
    void selectCharacterPos();
    void start();
    void setFileData(QString cFilename = "character1.txt", QString mFilename = "monster1.txt", int mode = 0);
    void selectAction(int i);
    void characterPrepare();
    void monsterPrepare();
    void actionByAgile();
    void cleanStatus();
    void checkGameStatus();
    void updateStatus();

protected:
    Ui::Gloomhaven *ui;
    QGraphicsScene *scene;
    int itemWidth;
    int itemHeight;
    QString characterFilename;
    QString monsterFilename;
    QString mapFilename;
    int debugMode;
    int monsterAmount;
    int t2; // count for select action
    int round;
    int isCharacter(char c) const;

signals:
    void endGame(QString s);

public slots:
    void selectedChange();
    void nothing();
//    void handleSelectActions();
    void on_confirmButton_released();
    void scrollChanged();

private slots:
    void on_confirmButton_2_released();
};

#endif // GLOOMHAVEN_H
