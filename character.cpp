#include "character.h"

Character::Character() : pos(-1, -1)
{

}

Character::Character(const Character& rhs) : characterName(rhs.characterName), maxHp(rhs.maxHp), startHandCardAmount(rhs.startHandCardAmount), handCardAmount(rhs.handCardAmount), pos(-1, -1) {
    for (size_t i = 0; i < rhs.cards.size(); ++i) {
        cards.push_back(CharacterSkill(rhs.cards[i]));
    }
}

QTextStream& operator>>(QTextStream& f, Character& rhs) {
  f >> rhs.characterName >> rhs.maxHp >> rhs.startHandCardAmount;
  f >> rhs.handCardAmount;
  rhs.cards = std::vector<CharacterSkill>(rhs.handCardAmount);
  for (int i = 0; i < rhs.handCardAmount; ++i) {
    f >> rhs.cards[i];
  }
  return f;
}

Character& Character::operator=(Character rhs) {
    std::swap(characterName, rhs.characterName);
    std::swap(maxHp, rhs.maxHp);
    std::swap(startHandCardAmount, rhs.startHandCardAmount);
    std::swap(handCardAmount, rhs.handCardAmount);
    std::swap(pos, rhs.pos);
    std::swap(cards, rhs.cards);
    return *this;
}

QString Character::getName() const {
    return characterName;
}

void Character::setUp(const std::vector<int>& start) {
    startHandCardAmount = start.size();
    for (int i = 0; i < startHandCardAmount; ++i) {
        inHands.insert({start[i], true});
    }
}

Point2d Character::getPos() const {
    return pos;
}

void Character::setPos(Point2d pos) {
    this->pos = pos;
}

void Character::prepare() {

}

void Character::setSelected(QString s) {
    s.remove(s.length() - 1, 1);
    qDebug() << s;
    QList<QString> list = s.split(" ");
    if (list.size() == 1) {
        status = 1;
        return;
    }
    status = 0;
    selected.clear();
    for (const auto& i: list) {
        qDebug() << i.toInt();
        selected.push_back(i.toInt());
    }
}

bool Character::restable() const {
    int cnt = 0;
    for (const auto& i: inHands) {
        if (i.second == false) ++cnt;
    }
    return cnt >= 2;
}
