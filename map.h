#ifndef MAP_H
#define MAP_H

#include <QObject>
#include <QString>
#include <QTextStream>
#include <vector>
#include <iostream>
#include <list>

#include "point.h"

class Map : public QObject
{
    Q_OBJECT
public:
    enum class MapData {
        wall = 0,
        floor = 1,
        obstacle = 2,
        door = 3,
        opened_door = 4
    };
    explicit Map(QObject *parent = nullptr);
    ~Map();
    friend QTextStream& operator>>(QTextStream& f, Map& rhs);
    MapData get(int r, int c);
    QString mapFilename;
    Point2d *pos;
    int row;
    int col;
    std::vector<std::vector<MapData>> data;
    std::vector<Point2d> startPos;
    bool inBound(const Point2d& p);
    bool visible(const Point2d& p);

signals:

};

#endif // MAP_H
