#include "characterskill.h"

CharacterSkill::CharacterSkill(QObject *parent) : QObject(parent)
{

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
