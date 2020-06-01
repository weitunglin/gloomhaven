#include "gloomhaven.h"

Gloomhaven::Gloomhaven(QWidget *parent) :
    QMainWindow(parent), CharacterData(), MonsterData(), Map(), ui(new Ui::Gloomhaven) {
    ui->setupUi(this);
    ui->graphicsView->setAlignment(Qt::AlignAbsolute);
    ui->confirmButton->hide();
    ui->listWidget->hide();
    ui->labelBattleInfo->hide();
    round = 0;
}

Gloomhaven::~Gloomhaven() {
    delete ui;
}

void Gloomhaven::setFileData(QString cFilename, QString mFilename, int mode) {
    characterFilename = cFilename;
    monsterFilename = mFilename;
    debugMode = mode;
    /* process character file input */
    QFile characterFile(":/files/" + characterFilename);
    trace(characterFilename.toStdString());
    if (characterFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "open file " << characterFilename << endl;
        QTextStream f(&characterFile);
        QString line = f.readLine();
        characterAmount = line.toInt();
        trace(characterAmount);
        charactersAll = std::vector<Character>(characterAmount, Character());
        for (int i = 0; i < characterAmount; ++i) {
            f >> charactersAll[i];
        }
    }
    characterFile.close();
    /* process monster file input */
    QFile monsterFile(":/files/" + monsterFilename);
    trace(monsterFilename.toStdString());
    if (monsterFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "open file " << monsterFilename << endl;
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

void Gloomhaven::showMap() {
    QGraphicsScene* scene = new QGraphicsScene();
    qDebug() << "g view size: (" << 800 << "," << 600 << ")" << endl;
    itemWidth = 800 / col;
    itemHeight = 600 / row;
    qDebug() << "itemSize: (" << itemWidth << "," << itemHeight << ")" << endl;
    qDebug() << "start: (" << getPos().getY() << "," << getPos().getX() << ")" << endl;
    std::vector<Point2d> traveled;
    drawBlock(scene, getPos().getY(), getPos().getX(), traveled);
    QObject::connect(scene, SIGNAL(selectionChanged()), this, SLOT(selectedChange()));
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
}

void Gloomhaven::drawBlock(QGraphicsScene* scene, int r, int c, std::vector<Point2d> &traveled) {
    auto itTraveled = find_if(traveled.begin(), traveled.end(), [r, c](const Point2d& u) {
        if (u.getX() == c && u.getY() == r) return true;
        else return false;
    });
    if (itTraveled != traveled.end()) {
        return;
    }

    if (get(r, c) == Map::MapData::floor) {
        QImage image;
        auto itStart = find_if(startPos.begin(), startPos.end(), [r, c](const Point2d& u) {
            if (u.getX() == c && u.getY() == r) return true;
            else return false;
        });
        if (itStart != startPos.end()) {
            // with start
            if (t < (int)(characters.size())) {
                // with start and available
                image = QImage(":/images/map_floor_with_start.jpg");
            } else {
                // with start but occupied
                image = QImage(":/images/map_floor.jpg");
            }
        } else {
            image = QImage(":/images/map_floor.jpg");
        }
        if (image.isNull()) {
            // check for image error
            QMessageBox::information(this,"Image Open Failed","Error Displaying image");
            return;
        }
        QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(image).scaled(itemWidth - 2, itemHeight - 3));
        item->setPos(QPointF(c * itemWidth, r * itemHeight));
        item->setData(0, QVariant{QPointF{qreal(c), qreal(r)}});
        if (t < (int)(characters.size()) && itStart != startPos.end()) {
            auto itSelectable = std::find_if(characters.begin(), characters.end(), [r, c](const Character& u) {
                return u.getPos() == Point2d(r, c);
            });
            if (itSelectable == characters.end()) {
                item->setFlag(QGraphicsItem::ItemIsSelectable, true);
            }
        }
        // check if there is a character
        for (size_t i = 0; i < characters.size(); ++i) {
            if (characters[i].getPos().getY() == r && characters[i].getPos().getX() == c) {
                qDebug() << "found character" << endl;
                QPixmap p = item->pixmap();
                QPainter *painter = new QPainter(&p);
                painter->setPen(Qt::blue);
                painter->setFont(QFont("Arial", 30));
                painter->drawText(QRect(0, 0, itemWidth-2, itemHeight-2), Qt::AlignCenter, QString((int)i + 'A'));
                painter->end();
                delete painter;
                item->setPixmap(p);
            }
        }
        // check if there is a monster
        for (size_t i = 0; i < monsters.size(); ++i) {
//            qDebug() << monsters[i].getPos().getY() << monsters[i].getPos().getX() << monsters[i].getType();
            if ((monsters[i].getType() != 0) && monsters[i].getPos().getY() == r && monsters[i].getPos().getX() == c) {
                qDebug() << "found monster" << endl;
                monsters[i].setOnCourt(true);
                QPixmap p = item->pixmap();
                QPainter *painter = new QPainter(&p);
                painter->setPen(Qt::green);
                painter->setFont(QFont("Arial", 30));
                painter->drawText(QRect(0, 0, itemWidth-2, itemHeight-2), Qt::AlignCenter, QString((int)i + 'a'));
                painter->end();
                delete painter;
                item->setPixmap(p);
            }
        }
        scene->addItem(item);
//        qDebug() << "floor point: (" << r << "," << c << ")" << endl;
//        qDebug() << "(" << c * itemWidth << "," << r * itemHeight << endl;
    } else if (get(r, c) == Map::MapData::door) {
        QImage image(":/images/map_door.jpg");
        if (image.isNull()) {
            QMessageBox::information(this, "Image Viewer", "Error Displaying image");
            return;
        }
        QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(image).scaled(itemWidth - 2, itemHeight - 3));
        item->setPos((QPointF(c * itemWidth, r * itemHeight)));
        item->setData(0, QVariant{QPointF{qreal(c), qreal(r)}});
        scene->addItem(item);
        qDebug() << "floor point: (" << r << "," << c << ")" << endl;
        qDebug() << "(" << c * itemWidth << "," << r * itemHeight << endl;
    }
    traveled.push_back(Point2d(r, c));

    if (get(r, c) == Map::MapData::door || get(r, c) == Map::MapData::wall) {
        return;
    }
    Point2d p(r-1, c); // up
    if (inBound(p)) {
        auto it = find_if(traveled.begin(), traveled.end(), [p](const Point2d& u) {
            if (u.getX() == p.getX() && u.getY() == p.getY()) return true;
            else return false;
        });
        if (it == traveled.end()) {
            drawBlock(scene, r-1, c, traveled);
        }
    }
    p.set(r, c+1); // right
    if (inBound(p)) {
        auto it = find_if(traveled.begin(), traveled.end(), [p](const Point2d& u) {
            if (u.getX() == p.getX() && u.getY() == p.getY()) return true;
            else return false;
        });
        if (it == traveled.end()) {
            drawBlock(scene, r, c+1, traveled);
        }
    }
    p.set(r+1, c); // down
    if (inBound(p)) {
        auto it = find_if(traveled.begin(), traveled.end(), [p](const Point2d& u) {
            if (u.getX() == p.getX() && u.getY() == p.getY()) return true;
            else return false;
        });
        if (it == traveled.end()) {
            drawBlock(scene, r+1, c, traveled);
        }
    }
    p.set(r, c-1); // left
    if (inBound(p)) {
        auto it = find_if(traveled.begin(), traveled.end(), [p](const Point2d& u) {
            if (u.getX() == p.getX() && u.getY() == p.getY()) return true;
            else return false;
        });
        if (it == traveled.end()) {
            drawBlock(scene, r, c-1, traveled);
        }
    }
}

void Gloomhaven::preGameInput() {
    /* get the input of the character data */
    QInputDialog *inputDialog = new QInputDialog(this);
    inputDialog->adjustSize();
    QString string, mapData;
    bool ok = false;
    do {
        string = inputDialog->getMultiLineText(this, "請輸入出場角色數量", "出場角色數量及卡牌:", "2\nbrute 0 1 2 3 4 5\nbrute 2 3 4 5 6 7", &ok, inputDialog->windowFlags());
    } while (!ok || string.isEmpty());
    if (!string.isEmpty()) {
        QStringList list = string.split("\n");
        characterAmountOnCourt = list.front().toInt();
        list.pop_front();
        characters = std::vector<Character>(characterAmountOnCourt);
        for (int i = 0; i < characterAmountOnCourt; ++i) {
            QStringList c = list.front().split(" ");
            QString name = c.front();
            c.pop_front();
            Character ch(*(find_if(charactersAll.begin(), charactersAll.end(), [name](const Character& u) {
                return u.getName() == name;
            })));
            characters[i] = ch;
            std::vector<int> startCards;
            for (QString i: c) {
                startCards.push_back(i.toInt());
                qDebug() << i.toInt() << " ";
            }
            qDebug() << endl;
            characters[i].setUp(startCards);
            qDebug() << "inhand size: " << characters[i].inHands.size() << endl;
            list.pop_front();
        }
        qDebug() << string << endl;
    }
    /* get the input of the map data */
    do {
        mapData = inputDialog->getText(this, "請輸入地圖資料", "地圖資料：", QLineEdit::Normal, "map1.txt", &ok, inputDialog->windowFlags());
    } while (!ok || mapData.isEmpty());
    if (!mapData.isEmpty()) {
        qDebug() << mapData << endl;
        mapFilename = mapData;
    }
    QFile file(":/files/" + mapFilename);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "open file " << mapFilename << endl;
        QTextStream f(&file);
        readMap(f);
        /* get the monster on the map input */
        int mcount;
        f >> mcount;
        qDebug() << mcount << endl;
        for (int i = 0; i < mcount; ++i) {
            QString mname;
            qint32 r, c, two, three, four;
            f >> mname >> c >> r >> two >> three >> four;
            Monster m(*find_if(monstersAll.begin(), monstersAll.end(), [mname](const Monster& u) {
                return u.getName() == mname;
            }));
            m.setUp(r, c, two, three, four);
            m.setType(characterAmountOnCourt);
            monsters.push_back(m);
            qDebug() << monsters.back().getPos().getY() << "," << monsters.back().getPos().getX() << "->" << mname << ":" << monsters.back().getType() << endl;
        }
    }
    file.close();
}

void Gloomhaven::characterPrepare() {
    // step1: foreach character select cards or sleep
    // step2: monsters random a card each
    // step3: sort the agile value (both characters and monsters)
    // step4: do the actions by sort result
    // (actions) => character: a card's up and another's down
    // (actions) => monster: a skill
    // step5: 結算 (check the dead condition, see if door's open, ... so on)
    // map->characters[0].attack(5, 3, map->monster);
    ui->labelBattleInfo->setText("");
    ui->labelBattleInfo->show();
    t2 = 0;
    selectAction(t2);
}

void Gloomhaven::monsterPrepare() {
    ui->labelInstruction->setText("monster randomed a action card");
//    ui->labelBattleInfo->setText(ui->labelBattleInfo->toPlainText() + "monster random action card\n");
    int cnt = 0;
    struct Node {
        int value = -1;
    };
    std::map<QString, Node> seen;
    std::random_device rd;
    std::default_random_engine gen = std::default_random_engine(rd());
    std::uniform_int_distribution<int> dis(0, 5);
    qDebug() << "random";
    for (size_t i = 0; i < monsters.size(); ++i) {
        if (seen[monsters[i].getName()].value == -1) {
            ++cnt;
            seen[monsters[i].getName()].value = dis(gen);
            qDebug() << monsters[i].getName() << seen[monsters[i].getName()].value;
        }
        if (monsters[i].getOnCourt()) {
            monsters[i].setSelected(seen[monsters[i].getName()].value);
            ui->labelBattleInfo->setText(ui->labelBattleInfo->toPlainText() + "monster " + QString((int)i + 'a') + " picked no." + QString::number(seen[monsters[i].getName()].value) + " card\n");
        }
    }
    sortByAgile();
}

void Gloomhaven::sortByAgile() {
    ui->labelInstruction->setText("sort actions by agile");
    ui->labelBattleInfo->setText(ui->labelBattleInfo->toPlainText() + "round: " + QString::number(++round) + "\n");
    // sort
    std::vector<std::pair<char, int>> list;
    for (size_t i = 0; i < characters.size(); ++i) {
        if (characters[i].getStatus()) {
            list.push_back({i+'A', characters[i].getActionAgile()});
        }
    }
    for (size_t i = 0; i < monsters.size(); ++i) {
        if (monsters[i].getOnCourt()) {
            list.push_back({i+'a', monsters[i].getSelected().getAgile()});
        }
    }
    std::sort(list.begin(), list.end(), [](const std::pair<char, int>& u, const std::pair<char, int>& v) {
        return u.second < v.second;
    });
    for (size_t i = 0; i < list.size(); ++i) {
        for (size_t j = 0; j < list.size() && i != j; ++j) {
            if (list[i].second == list[j].second) {
                if (isCharacter(list[i].first) && isCharacter(list[j].first)) {
                    if (characters[list[i].first - 'A'].getSelected()[1] < characters[list[j].first - 'A'].getSelected()[1]) {
                        std::swap(list[i], list[j]);
                    } else if (characters[list[i].first - 'A'].getSelected()[1] == characters[list[j].first - 'A'].getSelected()[1]) {
                        if (list[i].first < list[j].first) {
                            std::swap(list[i], list[j]);
                        }
                    }
                }
            }
        }
    }
    QString s;
    for (const auto& i: list) {
        s += QString(i.first) + " " + QString::number(i.second);
        if (i.first >= 'A' && i.first <= 'Z') {
            for (const auto& j: characters[i.first - 'A'].getSelected()) {
                s += " " + QString::number(j);
            }
        } else if (i.first >= 'a' && i.first <= 'z') {
            s += " " + monsters[i.first - 'a'].getSelected().getInfo();
        }
        s += "\n";
    }
    ui->labelBattleInfo->setText(ui->labelBattleInfo->toPlainText() + s);
    QInputDialog *inputDialog = new QInputDialog(this);
    inputDialog->adjustSize();
    for (const auto& i: list) {
        if (i.first >= 'A' && i.first <= 'Z') {
            QStringList options;
            bool ok;
            QString result;
            // 0: 0u + 1d, 1: 0d + 1u, 2: 1u + 0d, 3: 1d + 0u
            options.push_back(QString(characters[i.first-'A'].getSelectedUp(0).toString() + " + " + characters[i.first-'A'].getSelectedDown(1).toString()));
            options.push_back(QString(characters[i.first-'A'].getSelectedDown(0).toString() + " + " + characters[i.first-'A'].getSelectedUp(1).toString()));
            options.push_back(QString(characters[i.first-'A'].getSelectedUp(1).toString() + " + " + characters[i.first-'A'].getSelectedDown(0).toString()));
            options.push_back(QString(characters[i.first-'A'].getSelectedDown(1).toString() + " + " + characters[i.first-'A'].getSelectedUp(0).toString()));
            do {
                result = inputDialog->getItem(this, "Select Character " + QString(i.first) + " Action Detail", "Combations: ", options, 0, false, &ok, inputDialog->windowFlags());
            } while (!ok);
            int idx = options.indexOf(result);
            qDebug() << result << idx;
//            for (const auto& j: characters[i.first-'A'].)
        } else if (i.first >= 'a' && i.first <= 'z') {
            qDebug() << monsters[i.first - 'a'].getSelected().getInfo();
        }
    }
}

void Gloomhaven::selectAction(int i) {
    ui->labelInstruction->setText("Select an action for character " + QString(i + 'A'));
    ui->listWidget->clear();
    QList<QListWidgetItem*> items;
    QList<QListWidgetItem*> itemsDisabled;
    QListWidgetItem* rest = new QListWidgetItem("長休");
    if (!characters[i].restable()) {
        QFont font;
        font.setStrikeOut(true);
        rest->setFont(font);
        rest->setFlags(rest->flags() & ~Qt::ItemFlag::ItemIsSelectable);
    }
    ui->listWidget->insertItem(0, rest);
    for (const auto& card: characters[i].inHands) {
        if (card.second == true) {
            qDebug() << "+" << card.first;
            QListWidgetItem *i = new QListWidgetItem(QString::number(card.first));
            items.push_back(i);
        } else {
            qDebug() << "-" << card.first;
            QListWidgetItem *i = new QListWidgetItem(QString::number(card.first));
            QFont font;
            font.setStrikeOut(true);
            i->setFont(font);
            i->setFlags(i->flags() & ~Qt::ItemFlag::ItemIsSelectable);
            itemsDisabled.push_back(i);
        }
    }
    for (int i = 0; i < items.size(); ++i) {
        ui->listWidget->insertItem(i, items[i]);
    }
    for (int i = 0; i < itemsDisabled.size(); ++i) {
        ui->listWidget->insertItem(items.size() + 1 + i, itemsDisabled[i]);
    }
    ui->listWidget->setStyleSheet("QListWidget { background-color: black; color: gray; }");
    ui->listWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->listWidget->show();
    ui->listWidget->activateWindow();
    ui->listWidget->raise();
    ui->confirmButton->show();
    ui->confirmButton->activateWindow();
    ui->confirmButton->raise();
}

void Gloomhaven::selectedChange() {
    QList<QGraphicsItem*> list = ui->graphicsView->scene()->selectedItems();
    if (list.size()) {
        qDebug() << list.front()->data(0).toPointF().y() << "-" << list.front()->data(0).toPointF().x() << endl;
        characters[t].setPos(Point2d(list.front()->data(0).toPointF().y(), list.front()->data(0).toPointF().x()));
        showMap();
        if (++t < (int)(characters.size())) {
            ui->labelInstruction->setText("Please select start position for character " + QString(t+'A'));
        } else {
            ui->labelInstruction->setText("START GAME!");
            disconnect(ui->graphicsView->scene(), SIGNAL(selectionChanged()), this, SLOT(selectedChange()));
            ui->graphicsView->scene()->clearSelection();
            showMap();
            characterPrepare();
        }
    }
}

void Gloomhaven::nothing() {
    qDebug() << "nothing" << endl;
}

void Gloomhaven::start() {
    t = 0;
    ui->labelInstruction->setText("Please select start position for character " + QString(t+'A'));
}

void Gloomhaven::on_confirmButton_released()
{
    QList<QListWidgetItem*> list = ui->listWidget->selectedItems();
    auto checkRest = std::find_if(list.begin(), list.end(), [](QListWidgetItem* const& u) {
         return u->text() == "長休";
    });
    if ((checkRest != list.end() && list.size() != 1) || (checkRest == list.end() && list.size() != 2)) {
        // (select rest and others) or (no rest and not two cards)
        selectAction(t2);
        return;
    }
    QString s;
    for (int i = 0; i < list.size(); ++i) {
        s += list[i]->text() + " ";
    }
    ui->labelBattleInfo->setText(ui->labelBattleInfo->toPlainText() + "Character " + QString(t2 + 'A') + " selected " + s + "\n");
    characters[t2].setSelected(s);
    characters[t2].setStatus(list.size() == 1 ? 0 : 1);
    if (++t2 < (int)characters.size()) {
        selectAction(t2);
    } else {
        ui->confirmButton->hide();
        ui->listWidget->hide();
        monsterPrepare();
    }
}

int Gloomhaven::isCharacter(char c) const {
    return (c >= 'A' && c <= 'Z');
}
