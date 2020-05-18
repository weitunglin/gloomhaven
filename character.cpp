#include "character.h"

Character::Character()
{

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
