#ifndef CHARACTER_H
#define CHARACTER_H

#include <QObject>
#include <QDataStream>
#include <QTextStream>
#include <QString>
#include <vector>

#include "characterdata.h"

class Character : public CharacterData
{
public:
    Character();
    friend QTextStream& operator>>(QTextStream& f, Character& rhs);

private:
    QString characterName;
    int maxHp;
    int startHandCardAmount;
    int handCardAmount;
    std::vector<CharacterData> cards;

signals:

};

#endif // CHARACTER_H
