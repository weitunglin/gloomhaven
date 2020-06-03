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

Map::MapData Map::get(int r, int c) const {
    return data[r][c];
}

Map::MapData Map::get(Point2d pos) const {
    return data[pos.getY()][pos.getX()];
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

bool Map::validMove(Point2d p, const QString &s) const {
    int x = p.getX(), y = p.getY();
    for (const auto& i: s) {
        if (i == 'w') {
            if (data[y-1][x] != MapData::floor) return false;
            --y;
        } else if (i == 's') {
            if (data[y+1][x] != MapData::floor) return false;
            ++y;
        } else if (i == 'a') {
            if (data[y][x-1] != MapData::floor) return false;
            --x;
        } else if (i == 'd') {
            if (data[y][x+1] != MapData::floor) return false;
            ++x;
        }
    }
    return true;
}

bool Map::invision(const Point2d &p1, const Point2d &p2) const {
//    float x = p2.getX() - p1.getX(), y = p2.getY() - p1.getY();
//    int step = fmax(fabs(x), fabs(y));
//    float dx = (x / step), dy = (y / step);

//    for (int i = 0; i < step + 1; ++i) {
//        int x1 = round(x) + p1.getX();    // 四捨五入
//        int y1 = round(y) + p1.getY();
//        // check if there is a wall
//        if (data[y1][x1] == MapData::wall) {
//            return false;
//        }
//        x += dx;
//        y += dy;
//    }
    return true;
}
