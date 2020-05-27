#include "point.h"

Point2d::Point2d() : y(-1), x(-1) {

}

Point2d::Point2d(int r, int c) : y(r), x(c) {

}

Point2d::Point2d(const Point2d& rhs) : Point2d(rhs.y, rhs.x) {

}

Point2d::~Point2d() {

}

Point2d& Point2d::operator=(Point2d rhs) {
    std::swap(y, rhs.y);
    std::swap(x, rhs.x);
    return *this;
}

bool operator!=(const Point2d& u, const Point2d& v) {
    return !(u.x == v.x && u.y == v.y);
}

bool operator==(const Point2d& u, const Point2d& v) {
    return (u.x == v.x && u.y == v.y);
}

void Point2d::set(int r, int c) {
    y = r;
    x = c;
}

void Point2d::setY(int r) {
    y = r;
}

void Point2d::setX(int c) {
    x = c;
}

int Point2d::getY() const {
    return y;
}

int Point2d::getX() const {
    return x;
}
