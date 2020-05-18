#ifndef GLOOMHAVEN_H
#define GLOOMHAVEN_H

#include <QWidget>
#include <QFile>
#include <QTextStream>
#include <QDataStream>
#include <QInputDialog>
#include <QString>
#include <string>
#include <iostream>

#include "character.h"
#include "characterdata.h"
#include "map.h"

#define trace(x) { std::cout << #x << ": " << x << std::endl; }

class Gloomhaven : public QWidget, CharacterData
{
public:
    explicit Gloomhaven(QWidget *parent = nullptr);
    Gloomhaven(QWidget *parent = nullptr, QString cFilename = "character1.txt", QString mFilename = "monster1.txt", int mode = 0);
    void preGameInput();
    Map *map;

protected:
    QString characterFilename;
    QString monsterFilename;
    QString mapFilename;
    int debugMode;
    int monsterAmount;

signals:

};

#endif // GLOOMHAVEN_H
