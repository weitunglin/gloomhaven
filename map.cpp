#include "map.h"

Map::Map() : pos(-1, -1)
{
}

Map::~Map() {
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
        rhs.startPos.push_back(Point2d(r, c));
    }
    rhs.pos = Point2d(*(rhs.startPos.begin()));
    return f;
}

void Map::readMap(QTextStream& f) {
    /* get the map info */
    std::cout << "---Map---" << std::endl;
    f >> row >> col;
    std::cout << "Col:" << col << ", Row:" << row << std::endl;
    data = std::vector<std::vector<Map::MapData>>(row, std::vector<Map::MapData>(col));
    f.read(1);
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            int x = f.read(1).toInt();
            data[i][j] = Map::MapData(x);
        }
        f.read(1);
    }
    for (int i = 0; i < 4; ++i) {
        qint32 r, c;
        f >> c >> r;
        startPos.push_back(Point2d{r, c});
    }
    pos = Point2d(*(startPos.begin()));
}

Map::MapData Map::get(int r, int c) {
    return data[r][c];
}

int Map::getCol() const {
    return col;
}

int Map::getRow() const {
    return row;
}

Point2d Map::getPos() const {
    return pos;
}

//bool Map::visible(const Point2d& p) {

//}

bool Map::inBound(const Point2d &p) {
    if (p.getX() >= 0 && p.getX() < col && p.getY() >= 0 && p.getY() < row) return true;
    else return false;
}
