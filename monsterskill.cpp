#include "monsterskill.h"

MonsterSkill::MonsterSkill(QObject *parent) : QObject(parent)
{

}

MonsterSkill::MonsterSkill(const MonsterSkill& rhs) : cardId(rhs.cardId), agile(rhs.agile), reDeal(rhs.reDeal), move(rhs.move), attack(rhs.attack), range(rhs.range), heal(rhs.heal), shield(rhs.shield) {
}

QTextStream& operator>>(QTextStream& f, MonsterSkill& rhs) {
    f >> rhs.mname >> rhs.cardId >> rhs.agile;
    QString line = f.readLine();
    line = line.remove(0, 1);
    QStringList list = line.split(" ");
    for (int i = 0; i <= list.length() / 2; i += 2) {
        std::cout << list[i].toStdString() << "," << list[i+1].toStdString() << std::endl;
        if (list[i] == "move") rhs.move = list[i+1];
        else if (list[i] == "attack") rhs.attack = list[i+1].toInt();
        else if (list[i] == "range") rhs.range = list[i+1].toInt();
        else if (list[i] == "heal") rhs.heal = list[i+1].toInt();
        else if (list[i] == "shield") rhs.shield = list[i+1].toInt();
    }
    if (list.last() == "r") rhs.reDeal = true;
    else rhs.reDeal = false;
    std::cout << "reDeal: " << list.last().toStdString() << std::endl;
    return f;
}
