#include "monster.h"

Monster::Monster(QObject *parent) : QObject(parent)
{
}

Monster::Monster(const Monster& rhs) : monsterName(rhs.monsterName), normal(rhs.normal), elite(rhs.elite) {
    for (size_t i = 0; i < rhs.cards.size(); ++i) {
        cards.push_back(MonsterSkill(rhs.cards[i]));
    }
}

QTextStream& operator>>(QTextStream& f, Monster& rhs) {
    f >> rhs.monsterName;
    f >> rhs.normal.maxHp >> rhs.normal.attackDamage >> rhs.normal.attackRange;
    f >> rhs.elite.maxHp >> rhs.elite.attackDamage >> rhs.elite.attackRange;
    rhs.cards = std::vector<MonsterSkill>(6);
    for (int i = 0; i < 6; ++i) {
        f >> rhs.cards[i];
    }
    return f;
}

QString Monster::getName() const {
    return monsterName;
}

void Monster::setUp(Point2d p, int two, int three, int four) {
    pos = new Point2d(p);
    switch(two) {
    case 0:
        twoCharacters = MonsterStatus::noshow;
        break;
    case 1:
        twoCharacters = MonsterStatus::normal;
        break;
    case 2:
        twoCharacters = MonsterStatus::elite;
        break;
    }
    switch(three) {
    case 0:
        threeCharacters = MonsterStatus::noshow;
        break;
    case 1:
        threeCharacters = MonsterStatus::normal;
        break;
    case 2:
        threeCharacters = MonsterStatus::elite;
        break;
    }
    switch(four) {
    case 0:
        fourCharacters = MonsterStatus::noshow;
        break;
    case 1:
        fourCharacters = MonsterStatus::normal;
        break;
    case 2:
        fourCharacters = MonsterStatus::elite;
        break;
    }
}
