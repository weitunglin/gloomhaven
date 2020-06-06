#include "characterskill.h"

CharacterSkill::CharacterSkill()
{

}

CharacterSkill::CharacterSkill(const CharacterSkill& rhs) : cardId(rhs.cardId), agile(rhs.agile), up(rhs.up), down(rhs.down) {
}

void CharacterSkill::setUp(QString s) {
//    QTextStream ss(&s);
//    std::cout << "string:" << s.toStdString() << std::endl;
//    QString key;
//    int value;
//    do {
//        ss >> key >> value;
//        if (key == "" && value == 0) break;
//        std::cout << "key:" << key.toStdString() << ",value:" << value << std::endl;
//        skills.push_back({key, value});
//    } while (!ss.atEnd());
}

QTextStream& operator>>(QTextStream& f, CharacterSkill& rhs) {
    f >> rhs.cardId >> rhs.agile;
    QString line = f.readLine();
    line.remove(0, 1);
    QString up(QString::fromStdString(line.toStdString().substr(0, line.indexOf('-'))));
    rhs.up.setUp(up);
    //  std::cout << up.toStdString() << std::endl;
    QString down(QString::fromStdString(line.toStdString().substr(line.indexOf('-') + 2, line.length() - 2 - line.indexOf('-'))));
    rhs.down.setUp(down);
    //  std::cout << down.toStdString() << std::endl;
    return f;
}

int CharacterSkill::getCardId() const {
    return cardId;
}

int CharacterSkill::getAgile() const {
    return agile;
}

Action CharacterSkill::getUp() const {
    return up;
}

Action CharacterSkill::getDown() const {
    return down;
}

QString CharacterSkill::getInfo() const {
    return up.toString() + "+" + down.toString();
}
