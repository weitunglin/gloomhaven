#ifndef CHARACTERDATA_H
#define CHARACTERDATA_H

#include <QObject>
#include <QDataStream>
#include <QTextStream>
#include <QString>

#include "character.h"

class CharacterData : public QObject
{
    Q_OBJECT
public:
    explicit CharacterData(QObject *parent = nullptr);
    friend QTextStream& operator>>(QTextStream& f, CharacterData& rhs);

protected:
    int characterAmount;
    std::vector<Character> characters;

signals:

};

#endif // CHARACTERDATA_H
