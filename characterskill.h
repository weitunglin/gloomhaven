#ifndef CHARACTERSKILL_H
#define CHARACTERSKILL_H

#include <QObject>
#include <QDataStream>
#include <QTextStream>
#include <QString>
#include <iostream>
#include <vector>

class CharacterSkill : public QObject
{
    Q_OBJECT
public:
    explicit CharacterSkill(QObject *parent = nullptr);
    friend QTextStream& operator>>(QTextStream& f, CharacterSkill& rhs);

private:
    std::vector<std::pair<QString, int>> skills;

signals:

};

#endif // CHARACTERSKILL_H
