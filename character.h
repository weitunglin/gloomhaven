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
    void setPos(Point2d pos);
    Point2d getPos() const;
    void prepare();
    void setSelected(QString s);
    std::vector<int> getSelected() const;
    int getActionAgile() const;
    bool restable() const;
    void setStatus(int i);
    int getStatus() const;
    std::map<int, bool> inHands;
    Action getSelectedUp(int i) const;
    Action getSelectedDown(int i) const;
    Action getSelected(int index, int part) const;
    void setShield(int i);
    int getShield() const;
    int setHp(int i);
    int getHp() const;
    void move(int range);
    void attack(int value, int range);
    void setId(QString s);
    QString getId() const;
    void setAlive(bool b);
    bool getAlive() const;
    std::vector<CharacterSkill> getCards() const;
    CharacterSkill getCard(int i) const;

private:
    QString characterName;
    QString name;
    QString id;
    int maxHp;
    int hp;
    int shield;
    int startHandCardAmount;
    int handCardAmount;
    std::vector<CharacterSkill> cards;
    int status; // 0: sleep, 1: action
//    std::vector<std::pair<CharacterSkill, int /*0: up, 1: down*/>> selected;
    std::vector<int> selected;
    Point2d pos;
    bool alive;

signals:

};

#endif // CHARACTER_H
