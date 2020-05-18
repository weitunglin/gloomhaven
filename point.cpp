#include "point.h"

Point2d::Point2d(QObject *parent) : QObject(parent)
{

}

Point2d::Point2d(QObject *parent, int r, int c) : QObject(parent)
{
    y = r;
    x = c;
}

Point2d::Point2d(const Point2d& rhs) : Point2d(nullptr, rhs.y, rhs.x) {

}

Point2d::~Point2d() {

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
