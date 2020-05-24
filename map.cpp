#include "map.h"

Map::Map(QObject *parent) : QObject(parent)
{
}

Map::~Map() {
    delete pos;
}

QTextStream& operator>>(QTextStream& f, Map& rhs) {
    /* get the map info */
    std::cout << "---Map---" << std::endl;
    f >> rhs.row >> rhs.col;
    std::cout << "Col:" << rhs.col << ", Row:" << rhs.row << std::endl;
    rhs.data = std::vector<std::vector<Map::MapData>>(rhs.row, std::vector<Map::MapData>(rhs.col));
    f.read(1);
    for (int i = 0; i < rhs.row; ++i) {
        for (int j = 0; j < rhs.col; ++j) {
            int x = f.read(1).toInt();
            rhs.data[i][j] = Map::MapData(x);
        }
        f.read(1);
    }
    for (int i = 0; i < 4; ++i) {
        qint32 r, c;
        f >> c >> r;
        rhs.startPos.push_back(Point2d{nullptr, r, c});
    }
    rhs.pos = new Point2d(*(rhs.startPos.begin()));
    return f;
}

Map::MapData Map::get(int r, int c) {
    return data[r][c];
}

//bool Map::visible(const Point2d& p) {

//}

bool Map::inBound(const Point2d &p) {
    if (p.getX() >= 0 && p.getX() < col && p.getY() >= 0 && p.getY() < row) return true;
    else return false;
}
