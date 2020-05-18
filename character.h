#ifndef CHARACTER_H
#define CHARACTER_H

#include <QObject>
#include <QDataStream>
#include <QTextStream>
#include <QString>
#include <vector>

#include "characterskill.h"

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

signals:

};

#endif // CHARACTER_H
