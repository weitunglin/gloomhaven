#include "gloomhaven.h"

Gloomhaven::Gloomhaven(QWidget *parent) : QWidget(parent), CharacterData()
{

}

Gloomhaven::Gloomhaven(QWidget *parent, QString cFilename, QString mFilename, int mode) : QWidget(parent), CharacterData()
{
    characterFilename = cFilename;
    monsterFilename = mFilename;
    debugMode = mode;
    QFile file(":/files/" + characterFilename);
    trace(characterFilename.toStdString());
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        std::cout << "open file " << characterFilename.toStdString() << std::endl;
        QTextStream f(&file);
        QString line = f.readLine();
        characterAmount = line.toInt();
        trace(characterAmount);
        characters = std::vector<Character>(characterAmount);
        for (int i = 0; i < characterAmount; ++i) {
            f >> characters[i];
        }
    }
    file.close();
    preGameInput();
}

void Gloomhaven::preGameInput() {
    QInputDialog *inputDialog = new QInputDialog(this);
    inputDialog->adjustSize();
    QString string, mapData;
    bool ok = false;
    do {
        string = inputDialog->getMultiLineText(this, "請輸入出場角色數量", "出場角色數量及卡牌:", "2\nbrute 0 1 2 3 4 5\nbrute 2 3 4 5 6 7", &ok, inputDialog->windowFlags());
    } while (!ok);
    if (!string.isEmpty()) {
        std::cout << string.toStdString() << std::endl;
    }
    do {
        mapData = inputDialog->getText(this, "請輸入地圖資料", "地圖資料：", QLineEdit::Normal, "map1.txt", &ok, inputDialog->windowFlags());
    } while (!ok);
    if (!mapData.isEmpty()) {
        std::cout << mapData.toStdString() << std::endl;
        mapFilename = mapData;
    }
    map = new Map();
    QFile file(":/files/" + mapFilename);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        std::cout << "open file " << mapFilename.toStdString() << std::endl;
        QTextStream f(&file);
        f >> *map;
    }
    delete inputDialog;
}

void Gloomhaven::loop() {
    // foreach character select cards or sleep
    // monsters random a card each
    // sort the agile value (both characters and monsters)
    // do the actions by sort result
    // (actions) => character: a card's up and another's down
    // (actions) => monster: a skill
    // 結算 (check the dead condition, see if door's open, ... so on)
//    map->characters[0].attack(5, 3, map->monster);
}
