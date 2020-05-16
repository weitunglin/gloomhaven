#include "characterskill.h"

CharacterSkill::CharacterSkill(QObject *parent) : QObject(parent)
{

}

void CharacterSkill::setUp(QString s) {
    QTextStream ss(&s);
//    std::cout << "string:" << s.toStdString() << std::endl;
    QString key;
    int value;
    do {
        ss >> key >> value;
        if (key == "" && value == 0) break;
        std::cout << "key:" << key.toStdString() << ",value:" << value << std::endl;
        skills.push_back({key, value});
    } while (!ss.atEnd());
}
