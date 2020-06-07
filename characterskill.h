#ifndef CHARACTERSKILL_H
#define CHARACTERSKILL_H

#include <QObject>
#include <QDataStream>
#include <QTextStream>
#include <QString>
#include <iostream>
#include <vector>

#include "action.h"

class CharacterSkill
{
public:
    CharacterSkill();
    CharacterSkill(const CharacterSkill& rhs);
    friend QTextStream& operator>>(QTextStream& f, CharacterSkill& rhs);
    int getCardId() const;
    int getAgile() const;
    Action getUp() const;
    Action getDown() const;
    QString getInfo() const;

private:
    int cardId;
    int agile;
    Action up;
    Action down;

signals:

};

#endif // CHARACTERSKILL_H
