#include "monsterskill.h"

MonsterSkill::MonsterSkill()
{

}

MonsterSkill::MonsterSkill(const MonsterSkill& rhs) : info(rhs.info), cardId(rhs.cardId), agile(rhs.agile), reDeal(rhs.reDeal), move(rhs.move), attack(rhs.attack), heal(rhs.heal), shield(rhs.shield) {
}

QTextStream& operator>>(QTextStream& f, MonsterSkill& rhs) {
    f >> rhs.mname >> rhs.cardId >> rhs.agile;
    QString line = f.readLine();
    line = line.remove(0, 1);
    rhs.info = QString::fromStdString(line.toStdString().substr(0, line.length() - 2));
    QStringList list = line.split(" ");
    for (int i = 0; i <= list.length() / 2; i += 2) {
        qDebug() << list[i] << "," << list[i+1] << endl;
        if (list[i] == "move") rhs.move = list[i+1];
        else if (list[i] == "attack") rhs.attack = list[i+1].toInt();
        else if (list[i] == "range") rhs.range = list[i+1].toInt();
        else if (list[i] == "heal") rhs.heal = list[i+1].toInt();
        else if (list[i] == "shield") rhs.shield = list[i+1].toInt();
    }
    if (list.last() == "r") rhs.reDeal = true;
    else rhs.reDeal = false;
    qDebug() << "reDeal: " << list.last() << endl;
    return f;
}

int MonsterSkill::getAgile() const {
    return agile;
}

QString MonsterSkill::getInfo() const {
    return info;
}
