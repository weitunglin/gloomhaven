#include "characterskill.h"

CharacterSkill::CharacterSkill(QObject *parent) : QObject(parent)
{

}

QTextStream& operator>>(QTextStream& f, CharacterSkill& rhs) {
  QString line = f.readLine();
  line.remove(0, 1);

  std::cout << line.toStdString() << std::endl;
//  int value;
//  f >> key;
//  while (key != "-") {
//     f >> value;
//     rhs.skills.push_back({key, value});
//     f >> key;
//  }
  return f;
}
