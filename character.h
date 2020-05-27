#ifndef CHARACTER_H
#define CHARACTER_H

#include <QObject>
#include <QDataStream>
#include <QTextStream>
#include <QString>
#include <QInputDialog>
#include <QListWidget>
#include <QListWidgetItem>
#include <QDebug>
#include <vector>
#include <map>
#include <algorithm>

#include "characterskill.h"
#include "point.h"

class Character
{
public:
    Character();
    Character(const Character& rhs);
    friend QTextStream& operator>>(QTextStream& f, Character& rhs);
    Character& operator=(Character rhs);
    QString getName() const;
    void setUp(const std::vector<int>& start);
    Point2d getPos() const;
    void setPos(Point2d pos);
    void prepare();
    void setSelected(QString s);
    bool restable() const;
    std::map<int, bool> inHands;

private:
    QString characterName;
    QString name;
    int maxHp;
    int startHandCardAmount;
    int handCardAmount;
    std::vector<CharacterSkill> cards;
    int status; // 0: action, 1: sleep
//    std::vector<std::pair<CharacterSkill, int /*0: up, 1: down*/>> selected;
    std::vector<int> selected;
    Point2d pos;
    void move(int range);
    void attack(int value, int range);

signals:

};

#endif // CHARACTER_H
