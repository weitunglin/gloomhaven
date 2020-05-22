#ifndef CHARACTER_H
#define CHARACTER_H

#include <QObject>
#include <QDataStream>
#include <QTextStream>
#include <QString>
#include <vector>

#include "characterskill.h"
#include "point.h"

class Character
{
public:
    Character();
    friend QTextStream& operator>>(QTextStream& f, Character& rhs);  

private:
    QString characterName;
    int maxHp;
    int startHandCardAmount;
    int handCardAmount;
    std::vector<CharacterSkill> cards;
    int status; // 0: action, 1: sleep
    std::vector<std::pair<CharacterSkill, int /*0: up, 1: down*/>> selected;
    Point2d *pos;
    void move(int range);
    void attack(int value, int range);

signals:

};

#endif // CHARACTER_H
