#include "character.h"

Character::Character() : pos(nullptr, -1, -1)
{

}

Character::Character(const Character& rhs) : characterName(rhs.characterName), maxHp(rhs.maxHp), startHandCardAmount(rhs.startHandCardAmount), handCardAmount(rhs.handCardAmount), pos(nullptr, -1, -1) {
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

QString Character::getName() const {
    return characterName;
}

void Character::setUp(const std::vector<int>& start) {
    startHandCardAmount = start.size();
    for (int i = 0; i < startHandCardAmount; ++i) {
        inHands.insert({start[i], true});
    }
}

Point2d Character::getPos() {
    return pos;
}

void Character::setPos(Point2d pos) {
    this->pos = pos;
}
