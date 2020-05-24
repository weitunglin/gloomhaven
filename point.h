#ifndef POINT2D_H
#define POINT2D_H

#include <QObject>

class Point2d : public QObject
{
    Q_OBJECT
public:
    explicit Point2d(QObject *parent = nullptr);
    Point2d();
    Point2d(QObject *parent = nullptr, int r = 0, int c = 0);
    Point2d(const Point2d& rhs);
    ~Point2d();
    void set(int r, int c);
    void setY(int r);
    void setX(int c);
    int getY() const;
    int getX() const;
    Point2d& operator=(Point2d rhs);

private:
    int y;
    int x;

signals:

};

#endif // POINT2D_H
