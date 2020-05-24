#ifndef MONSTERDATA_H
#define MONSTERDATA_H

#include <QObject>
#include <vector>

#include "monster.h"

class MonsterData : public QObject
{
    Q_OBJECT
public:
    explicit MonsterData(QObject *parent = nullptr);

protected:
    int monsterAmount;
    std::vector<Monster> monstersAll;

signals:

};

#endif // MONSTERDATA_H
