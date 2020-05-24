#ifndef MONSTERSKILL_H
#define MONSTERSKILL_H

#include <QObject>
#include <QString>
#include <QTextStream>
#include <vector>
#include <iostream>

class MonsterSkill : public QObject
{
    Q_OBJECT
public:
    explicit MonsterSkill(QObject *parent = nullptr);
    MonsterSkill(const MonsterSkill& rhs);
    friend QTextStream& operator>>(QTextStream& f, MonsterSkill& rhs);

private:
    QString mname;
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
