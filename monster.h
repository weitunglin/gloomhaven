#ifndef MONSTER_H
#define MONSTER_H

#include <QObject>
#include <QString>
#include <QTextStream>
#include <vector>
#include <map>

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
    void setPos(Point2d pos);
    Point2d getPos() const;
    void setSelected(int i);
    MonsterSkill getSelected() const;
    void setOnCourt(bool b);
    bool getOnCourt() const;
    void setShield(int i);
    int getShield() const;
    int healHp(int i);
    int setHp(int i);
    int getHp() const;
    MonsterInfo getInfo() const;
    std::map<int, bool>& getInHands();
    void disableActionCard();
    int getRealAttack() const;
    void setId(QString s);
    QString getId() const;
    void setAlive(bool b);
    bool getAlive() const;

private:
    QString monsterName;
    QString id;
    MonsterInfo normal;
    MonsterInfo elite;
    int hp;
    int shield;
    int twoCharacters;
    int threeCharacters;
    int fourCharacters;
    std::vector<MonsterSkill> cards;
    MonsterSkill selected;
    int type; // 0: noshow, 1: normal, 2: elite
    std::vector<MonsterInfo> info;
    Point2d pos;
    bool onCourt;
    std::map<int, bool> inHands;
    bool alive;

signals:

};

#endif // MONSTER_H
