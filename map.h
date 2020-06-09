#ifndef MAP_H
#define MAP_H

#include <QObject>
#include <QString>
#include <QTextStream>
#include <vector>
#include <iostream>
#include <list>
#include <math.h>

#include "point.h"
#include "character.h"
#include "monster.h"

class Map
{
public:
    enum class MapData {
        wall = 0,
        floor = 1,
        obstacle = 2,
        door = 3,
        opened_door = 4,
        character = 5,
        monster = 6
    };
    explicit Map();
    ~Map();
    friend QTextStream& operator>>(QTextStream& f, Map& rhs);
    int getRow() const;
    int getCol() const;
    Point2d getPos() const;
    MapData get(int r, int c) const;
    MapData get(Point2d pos) const;
    bool validMove(Point2d p, const QString& s) const;
    bool invision(const Point2d& p1, const Point2d& p2) const;

protected:
    void readMap(QTextStream& f);
    QString mapFilename;
    Point2d pos;
    int row;
    int col;
    std::vector<std::vector<MapData>> data;
    std::vector<Point2d> startPos;
    bool inBound(const Point2d& p) const;
    bool visible(const Point2d& p);
    int characterAmountOnCourt;
    std::vector<Character> characters;
    std::vector<Monster> monsters;
    int t = 0; // count for start position selection
    bool openDoor;
    void startPosSelectable();

signals:

};

#endif // MAP_H
