#include "gloomhaven.h"

Gloomhaven::Gloomhaven(QWidget *parent) : QWidget(parent), CharacterData(), MonsterData()
{

}

Gloomhaven::Gloomhaven(QWidget *parent, QString cFilename, QString mFilename, int mode) : QWidget(parent), CharacterData(), MonsterData()
{
    characterFilename = cFilename;
    monsterFilename = mFilename;
    debugMode = mode;
    /* process character file input */
    QFile characterFile(":/files/" + characterFilename);
    trace(characterFilename.toStdString());
    if (characterFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        std::cout << "open file " << characterFilename.toStdString() << std::endl;
        QTextStream f(&characterFile);
        QString line = f.readLine();
        characterAmount = line.toInt();
        trace(characterAmount);
        charactersAll = std::vector<Character>(characterAmount);
        for (int i = 0; i < characterAmount; ++i) {
            f >> charactersAll[i];
        }
    }
    characterFile.close();
    /* process monster file input */
    QFile monsterFile(":/files/" + monsterFilename);
    trace(monsterFilename.toStdString());
    if (monsterFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        std::cout << "open file " << monsterFilename.toStdString() << std::endl;
        QTextStream f(&monsterFile);
        QString amount = f.readLine();
        monsterAmount = amount.toInt();
        monstersAll = std::vector<Monster>(monsterAmount);
        for (int i = 0; i < monsterAmount; ++i) {
            f >> monstersAll[i];
        }
    }
    /* process pregame data */
    preGameInput();
}

Gloomhaven::~Gloomhaven() {
    delete map;
}

void Gloomhaven::preGameInput() {
    map = new Map();
    /* get the input of the character data */
    QInputDialog *inputDialog = new QInputDialog(this);
    inputDialog->adjustSize();
    QString string, mapData;
    bool ok = false;
    do {
        string = inputDialog->getMultiLineText(this, "請輸入出場角色數量", "出場角色數量及卡牌:", "2\nbrute 0 1 2 3 4 5\nbrute 2 3 4 5 6 7", &ok, inputDialog->windowFlags());
    } while (!ok);
    if (!string.isEmpty()) {
        QStringList list = string.split("\n");
        map->characterAmountOnCourt = list.front().toInt();
        list.pop_front();
        for (int i = 0; i < map->characterAmountOnCourt; ++i) {
            QStringList c = list.front().split(" ");
            QString name = c.front();
            c.pop_front();
            map->characters.push_back(Character(*(find_if(charactersAll.begin(), charactersAll.end(), [name](const Character& u) {
                return u.getName() == name;
            }))));
            std::vector<int> startCards;
            for (QString i: c) {
                startCards.push_back(i.toInt());
                std::cout << i.toInt() << " ";
            }
            std::cout << std::endl;
            map->characters[i].setUp(startCards);
            list.pop_front();
        }
        std::cout << string.toStdString() << std::endl;
    }
    /* get the input of the map data */
    do {
        mapData = inputDialog->getText(this, "請輸入地圖資料", "地圖資料：", QLineEdit::Normal, "map1.txt", &ok, inputDialog->windowFlags());
    } while (!ok);
    if (!mapData.isEmpty()) {
        std::cout << mapData.toStdString() << std::endl;
        mapFilename = mapData;
    }
    QFile file(":/files/" + mapFilename);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        std::cout << "open file " << mapFilename.toStdString() << std::endl;
        QTextStream f(&file);
        f >> *map;
        /* get the monster on the map input */
        int mcount;
        f >> mcount;
        std::cout << mcount << std::endl;
        for (int i = 0; i < mcount; ++i) {
            QString mname;
            qint32 r, c, two, three, four;
            f >> mname >> c >> r >> two >> three >> four;
            map->monsters.push_back(Monster(*find_if(monstersAll.begin(), monstersAll.end(), [mname](const Monster& u) {
                return u.getName() == mname;
            })));
            map->monsters.end()->setUp(Point2d{nullptr, r, c}, two, three, four);
            std::cout << r << "," << c << "->" << mname.toStdString() << std::endl;
        }
    }
    file.close();
    delete inputDialog;
}

void Gloomhaven::loop() {
//    mainwindow->selectCharacterPos();
    // foreach character select cards or sleep
    // monsters random a card each
    // sort the agile value (both characters and monsters)
    // do the actions by sort result
    // (actions) => character: a card's up and another's down
    // (actions) => monster: a skill
    // 結算 (check the dead condition, see if door's open, ... so on)
//    map->characters[0].attack(5, 3, map->monster);

}
