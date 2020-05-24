#ifndef MONSTER_H
#define MONSTER_H

#include <QObject>
#include <QString>
#include <QTextStream>
#include <vector>

#include "monsterskill.h"
#include "point.h"

typedef struct monsterInfo {
    int maxHp;
    int attackRange;
    int attackDamage;
} MonsterInfo;


class Monster : public QObject
{
enum class MonsterStatus {
    noshow = 0,
    normal = 1,
    elite = 2
};
    Q_OBJECT
public:
    explicit Monster(QObject *parent = nullptr);
    Monster(const Monster& rhs);
    friend QTextStream& operator>>(QTextStream& f, Monster& rhs);
    QString getName() const;
    void setUp(Point2d p, int two, int three, int four);

private:
    QString monsterName;
    MonsterInfo normal;
    MonsterInfo elite;
    MonsterStatus twoCharacters;
    MonsterStatus threeCharacters;
    MonsterStatus fourCharacters;
    std::vector<MonsterSkill> cards;
    Point2d* pos;

signals:

};

#endif // MONSTER_H
