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
    openDoor = false;
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

bool Map::inBound(const Point2d &p) const {
    if (p.getX() >= 0 && p.getX() < col && p.getY() >= 0 && p.getY() < row) return true;
    else return false;
}

bool Map::validMove(Point2d p, const QString &s) const {
    int x = p.getX(), y = p.getY();
    for (const auto& i: s) {
        if (i == 'w') {
            if (data[y-1][x] == MapData::monster || data[y-1][x] == MapData::wall || data[y-1][x] == MapData::obstacle) return false;
            --y;
        } else if (i == 's') {
            if (data[y+1][x] == MapData::monster || data[y+1][x] == MapData::wall || data[y+1][x] == MapData::obstacle) return false;
            ++y;
        } else if (i == 'a') {
            if (data[y][x-1] == MapData::monster || data[y][x-1] == MapData::wall || data[y][x-1] == MapData::obstacle) return false;
            --x;
        } else if (i == 'd') {
            if (data[y][x+1] == MapData::monster || data[y][x+1] == MapData::wall || data[y][x+1] == MapData::obstacle) return false;
            ++x;
        }
    }
    if (data[y][x] != MapData::floor && data[y][x] != MapData::door) {
        return false;
    } else {
        auto c = std::find_if(characters.begin(), characters.end(), [=](const Character& u) {
            return u.getPos() == Point2d(y, x);
        });
        if (c == characters.end()) {
            return true;
        } else {
            return false;
        }
    }
}

bool Map::invision(const Point2d &p1, const Point2d &p2) const {
    double x, y, y2 = p2.getY(), x2 = p2.getX(), x1 = p1.getX(), y1 = p1.getY();
    for (x = x1; fabs(x2 - x) > 0.01f; x += p2.getX() > x ? 0.1f : -0.1f) {
        for (y = y1; fabs(y2 - y) > 0.01f; y += p2.getY() > y ? 0.1f : -0.1f) {
//            (x - x1) / (x2 - x1) = (y - y1) / (y2 - y1)
            if ((x - x1) / (x2 - x1) == (y - y1) / (y2 - y1)) {
                if (data[round(y)][round(x)] == Map::MapData::wall) {
                    qDebug() << y << x;
                    return false;
                }
            }
        }
    }
    return true;
}
