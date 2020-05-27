#ifndef MAP_H
#define MAP_H

#include <QObject>
#include <QString>
#include <QTextStream>
#include <vector>
#include <iostream>
#include <list>

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
        opened_door = 4
    };
    explicit Map();
    ~Map();
    friend QTextStream& operator>>(QTextStream& f, Map& rhs);
    int getRow() const;
    int getCol() const;
    Point2d getPos() const;

protected:
    MapData get(int r, int c);
    void readMap(QTextStream& f);
    QString mapFilename;
    Point2d pos;
    int row;
    int col;
    std::vector<std::vector<MapData>> data;
    std::vector<Point2d> startPos;
    bool inBound(const Point2d& p);
    bool visible(const Point2d& p);
    int characterAmountOnCourt;
    std::vector<Character> characters;
    std::vector<Monster> monsters;
    void startPosSelectable();
    int t = 0;

signals:

};

#endif // MAP_H
