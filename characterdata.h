#ifndef CHARACTERDATA_H
#define CHARACTERDATA_H

#include <QObject>
#include <QDataStream>
#include <QTextStream>

#include "characterskill.h"

class CharacterData : public QObject
{
    Q_OBJECT
public:
    explicit CharacterData(QObject *parent = nullptr);
    friend QTextStream& operator>>(QTextStream& f, CharacterData& rhs);

private:
    int cardId;
    int agile;
    CharacterSkill up;
    CharacterSkill down;

signals:

};

#endif // CHARACTERDATA_H
