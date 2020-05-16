#ifndef GLOOMHAVEN_H
#define GLOOMHAVEN_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QDataStream>
#include <string>
#include <iostream>

#include "character.h"

#define trace(x) { std::cout << #x << ": " << x << std::endl; }

class Gloomhaven : public QObject
{
    Q_OBJECT
public:
    explicit Gloomhaven(QObject *parent = nullptr);
    Gloomhaven(QObject *parent = nullptr, std::string cFilename = "character1.txt", std::string mFilename = "monster1.txt", int mode = 0);

private:
    std::vector<Character> characters;
    std::string characterFilename;
    std::string monsterFilename;
    std::string mapFilename;
    int debugMode;
    int characterAmount;
    int monsterAmount;

signals:

};

#endif // GLOOMHAVEN_H
