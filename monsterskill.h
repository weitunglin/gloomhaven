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
    int getCardId() const;
    int getAgile() const;
    QString getInfo() const;
    bool getReDeal() const;
    QString getMove() const;
    int getAttack() const;
    int getRange() const;
    int getHeal() const;
    int getShield() const;
    std::vector<std::pair<QString, QString>> getSkills() const;

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
    std::vector<std::pair<QString, QString>> skills;

signals:

};

#endif // MONSTERSKILL_H
