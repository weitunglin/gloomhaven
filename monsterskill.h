#ifndef MONSTERSKILL_H
#define MONSTERSKILL_H

#include <QObject>
#include <QString>
#include <QTextStream>
#include <QDebug>
#include <vector>
#include <iostream>

class MonsterSkill
{
public:
    MonsterSkill();
    MonsterSkill(const MonsterSkill& rhs);
    friend QTextStream& operator>>(QTextStream& f, MonsterSkill& rhs);
    int getAgile() const;
    QString getInfo() const;

private:
    QString mname;
    QString info;
    int cardId;
    int agile;
    bool reDeal;
    QString move;
    int attack;
    int range;
    int heal;
    int shield;

signals:

};

#endif // MONSTERSKILL_H
