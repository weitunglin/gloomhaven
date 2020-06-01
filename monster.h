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
    void setUp(int r, int c, int two, int three, int four);
    void setType(int t);
    int getType() const;
    Point2d getPos() const;
    void setSelected(int i);
    MonsterSkill getSelected() const;
    void setOnCourt(bool b);
    bool getOnCourt() const;

private:
    QString monsterName;
    MonsterInfo normal;
    MonsterInfo elite;
    int twoCharacters;
    int threeCharacters;
    int fourCharacters;
    std::vector<MonsterSkill> cards;
    MonsterSkill selected;
    int type;
    std::vector<MonsterInfo> info;
    Point2d pos;
    bool onCourt;

signals:

};

#endif // MONSTER_H
