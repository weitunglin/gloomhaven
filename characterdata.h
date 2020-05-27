#ifndef CHARACTERDATA_H
#define CHARACTERDATA_H

#include <QObject>
#include <QDataStream>
#include <QTextStream>
#include <QString>

#include "character.h"

class CharacterData
{
public:
    CharacterData();
    friend QTextStream& operator>>(QTextStream& f, CharacterData& rhs);

protected:
    int characterAmount;
    std::vector<Character> charactersAll;

signals:

};

#endif // CHARACTERDATA_H
