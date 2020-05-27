#ifndef CHARACTERSKILL_H
#define CHARACTERSKILL_H

#include <QObject>
#include <QDataStream>
#include <QTextStream>
#include <QString>
#include <iostream>
#include <vector>

#include "action.h"

class CharacterSkill : public QObject
{
    Q_OBJECT
public:
    CharacterSkill(const CharacterSkill& rhs);
    explicit CharacterSkill(QObject *parent = nullptr);
    friend QTextStream& operator>>(QTextStream& f, CharacterSkill& rhs);
    void setUp(QString s);
    int getCardId() const;

private:
    bool available;
    int cardId;
    int agile;
    Action up;
    Action down;

signals:

};

#endif // CHARACTERSKILL_H
