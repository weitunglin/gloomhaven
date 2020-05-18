#ifndef ACTION_H
#define ACTION_H

#include <QObject>
#include <QTextStream>
#include <QString>
#include <iostream>
#include <vector>

class Action : public QObject
{
    Q_OBJECT
public:
    explicit Action(QObject *parent = nullptr);
    void setUp(QString s);
//    friend QTextStream& operator>>(QTextStream& f, Action&);

private:
    std::vector<std::pair<QString, int>> skills;

signals:

};

#endif // ACTION_H
