#ifndef ACTION_H
#define ACTION_H

#include <QObject>
#include <QTextStream>
#include <QString>
#include <QDebug>
#include <iostream>
#include <vector>

class Action
{
public:
    Action();
    Action(const Action& rhs);
    void setUp(QString s);
//    friend QTextStream& operator>>(QTextStream& f, Action&);
    QString toString() const;
    std::vector<std::pair<QString, int>> getSkills();

private:
    std::vector<std::pair<QString, int>> skills;
    QString detail;

signals:

};

#endif // ACTION_H
