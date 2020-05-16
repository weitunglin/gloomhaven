#include "characterdata.h"

CharacterData::CharacterData(QObject *parent) : QObject(parent)
{

}

QTextStream& operator>>(QTextStream& f, CharacterData& rhs) {
  f >> rhs.cardId >> rhs.agile;
  QString line = f.readLine();
  line.remove(0, 1);
  QString up(QString::fromStdString(line.toStdString().substr(0, line.indexOf('-'))));
  std::cout << up.toStdString() << std::endl;
  QString down(QString::fromStdString(line.toStdString().substr(line.indexOf('-') + 2, line.length() - 2 - line.indexOf('-'))));
  std::cout << down.toStdString() << std::endl;
  return f;
}
