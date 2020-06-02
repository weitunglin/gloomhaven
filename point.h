#ifndef POINT2D_H
#define POINT2D_H

#include <QObject>
#include <QDebug>
#include <QPointF>
#include <QPoint>

class Point2d
{
public:
    Point2d();
    Point2d(int r = -1, int c = -1);
    Point2d(const Point2d& rhs);
    ~Point2d();
    void set(int r, int c);
    void setY(int r);
    void setX(int c);
    int getY() const;
    int getX() const;
    Point2d& operator=(Point2d rhs);
    friend bool operator==(const Point2d& u, const Point2d& v);
    friend bool operator!=(const Point2d& u, const Point2d& v);
    friend Point2d operator-(const Point2d& u, const Point2d& v);
    friend QDebug operator<<(QDebug d, const Point2d& rhs);
    QPointF toQPointF();
    const QPointF toQPointF() const;
    QPoint toQPoint();
    const QPoint toQPoint() const;
    friend int getRange(const Point2d& p1, const Point2d& p2);

private:
    int y;
    int x;

signals:

};

#endif // POINT2D_H
