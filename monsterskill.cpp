#include "monsterskill.h"

MonsterSkill::MonsterSkill() : move(""), attack(0), range(0), heal(0), shield(0) {
}

MonsterSkill::MonsterSkill(const MonsterSkill& rhs) : info(rhs.info), cardId(rhs.cardId), agile(rhs.agile), reDeal(rhs.reDeal), move(rhs.move), attack(rhs.attack), range(rhs.range), heal(rhs.heal), shield(rhs.shield), skills(rhs.skills) {
}

QTextStream& operator>>(QTextStream& f, MonsterSkill& rhs) {
    f >> rhs.mname >> rhs.cardId >> rhs.agile;
    QString line = f.readLine();
    line = line.remove(0, 1);
    rhs.info = QString::fromStdString(line.toStdString().substr(0, line.length() - 2));
    QStringList list = line.split(" ");
    for (int i = 0; i <= list.length() / 2; i += 2) {
        qDebug() << list[i] << "," << list[i+1] << endl;
        rhs.skills.push_back({list[i], list[i+1]});
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

int MonsterSkill::getCardId() const {
    return cardId;
}

int MonsterSkill::getAgile() const {
    return agile;
}

QString MonsterSkill::getInfo() const {
    return info;
}

QString MonsterSkill::getMove() const {
    return move;
}

bool MonsterSkill::getReDeal() const {
    return reDeal;
}

int MonsterSkill::getHeal() const {
    return heal;
}

int MonsterSkill::getRange() const {
    return range;
}

int MonsterSkill::getAttack() const {
    return attack;
}

int MonsterSkill::getShield() const {
    return shield;
}

std::vector<std::pair<QString, QString>> MonsterSkill::getSkills() const {
    return skills;
}
