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

protected:
    int characterAmount;
    std::vector<Character> charactersAll;

signals:

};

#endif // CHARACTERDATA_H
