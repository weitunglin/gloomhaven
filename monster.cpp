#include "monster.h"

Monster::Monster(QObject *parent) : QObject(parent), pos(-1, -1)
{
}

Monster::Monster(const Monster& rhs) : monsterName(rhs.monsterName), twoCharacters(rhs.twoCharacters), threeCharacters(rhs.threeCharacters), fourCharacters(rhs.fourCharacters), type(rhs.type), pos(rhs.pos), onCourt(false) {
    for (size_t i = 0; i < rhs.cards.size(); ++i) {
        cards.push_back(MonsterSkill(rhs.cards[i]));
    }
    for (size_t i = 0; i < rhs.info.size(); ++i) {
        info.push_back(MonsterInfo{rhs.info[i].maxHp, rhs.info[i].attackDamage, rhs.info[i].attackRange});
    }
}

QTextStream& operator>>(QTextStream& f, Monster& rhs) {
    f >> rhs.monsterName;
    rhs.info.push_back(MonsterInfo());
    rhs.info.push_back(MonsterInfo());
    f >> rhs.info[0].maxHp >> rhs.info[0].attackDamage >> rhs.info[0].attackRange;
    f >> rhs.info[1].maxHp >> rhs.info[1].attackDamage >> rhs.info[1].attackRange;
    rhs.cards = std::vector<MonsterSkill>(6, MonsterSkill());
    for (int i = 0; i < 6; ++i) {
        f >> rhs.cards[i];
    }
    return f;
}

QString Monster::getName() const {
    return monsterName;
}

void Monster::setUp(int r, int c, int two, int three, int four) {
    pos.set(r, c);
    qDebug() << "monster assign pos";
    twoCharacters = two;
    threeCharacters = three;
    fourCharacters = four;
    for (size_t i = 0; i < cards.size(); ++i) {
        inHands.insert({i, true});
    }
//    switch(two) {
//    case 0:
//        twoCharacters = MonsterStatus::noshow;
//        break;
//    case 1:
//        twoCharacters = MonsterStatus::normal;
//        break;
//    case 2:
//        twoCharacters = MonsterStatus::elite;
//        break;
//    }
//    switch(three) {
//    case 0:
//        threeCharacters = MonsterStatus::noshow;
//        break;
//    case 1:
//        threeCharacters = MonsterStatus::normal;
//        break;
//    case 2:
//        threeCharacters = MonsterStatus::elite;
//        break;
//    }
//    switch(four) {
//    case 0:
//        fourCharacters = MonsterStatus::noshow;
//        break;
//    case 1:
//        fourCharacters = MonsterStatus::normal;
//        break;
//    case 2:
//        fourCharacters = MonsterStatus::elite;
//        break;
//    }
}

void Monster::setType(int t) {
    switch (t) {
    case 2:
        type = twoCharacters;
        break;
    case 3:
        type = threeCharacters;
        break;
    case 4:
        type = fourCharacters;
        break;
    }
    if (type == 1) {
        hp = normal.maxHp;
    } else if (type == 2) {
        hp = elite.maxHp;
    }
    shield = 0;
}

int Monster::getType() const {
    return type;
}

void Monster::setPos(Point2d pos) {
    this->pos = pos;
}

Point2d Monster::getPos() const {
    return pos;
}

void Monster::setSelected(int i) {
    selected = cards[i];
}

MonsterSkill Monster::getSelected() const {
    return selected;
}

void Monster::setOnCourt(bool b) {
    onCourt = b;
}

bool Monster::getOnCourt() const {
    return onCourt;
}

void Monster::setShield(int i) {
    shield = i;
}

int Monster::getShield() const {
    return shield;
}

int Monster::healHp(int i) {
    hp += i;
    if (hp > getInfo().maxHp) {
        hp = getInfo().maxHp;
    }
    return hp;
}

MonsterInfo Monster::getInfo() const {
    if (type == 1) return info[0];
    else if (type == 2) return info[1];
    return MonsterInfo{0, 0, 0};
}

std::map<int, bool>& Monster::getInHands() {
    return inHands;
}

void Monster::disableActionCard() {
    inHands[selected.getCardId()] = false;
}

int Monster::getRealAttack() const {
    return getInfo().attackDamage + selected.getAttack();
}
