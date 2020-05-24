#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->graphicsView->setAlignment(Qt::AlignAbsolute);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete scene;
    delete game;
}


void MainWindow::showMap() {
    scene = new QGraphicsScene();
    std::cout << "g view size: (" << ui->graphicsView->width() << "," << ui->graphicsView->height() << ")" << std::endl;
    itemWidth = ui->graphicsView->width() / game->map->col;
    itemHeight = ui->graphicsView->height() / game->map->row;
    std::cout << "itemSize: (" << itemWidth << "," << itemHeight << ")" << std::endl;
    std::vector<Point2d> traveled;
    std::cout << "start: (" << game->map->pos->getY() << "," << game->map->pos->getX() << ")" << std::endl;
    drawBlock(scene, game->map->pos->getY(), game->map->pos->getX(), traveled);
//    for (int i = 0; i < game->map->row; ++i) {
//        for (int j = 0; j < game->map->col; ++j) {
//            if (!inVision(Point2d(nullptr, i, j))) continue;
//            if (game->map->get(i, j) == Map::MapData::wall) {
//                // nothing, print black block
//            } else if (game->map->get(i, j) == Map::MapData::floor) {
//                auto it = find_if(game->map->startPos.begin(), game->map->startPos.end(), [i, j](const Point2d& u) {
//                    if (u.getX() == i && u.getY() == j) return true;
//                    else return false;
//                });
//                QImage image;
//                if (it != game->map->startPos.end()) {
//                    image = QImage(":/images/map_floor_with_start.jpg");
//                } else {
//                    image = QImage(":/images/map_floor");
//                }
//                if(image.isNull()) {
//                    QMessageBox::information(this,"Image Viewer","Error Displaying image");
//                    return;
//                }
//                QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(image).scaled(itemWidth - 2, itemHeight - 3));
//                item->setPos(QPointF(j * itemWidth, i * itemHeight));
//                item->setFlag(QGraphicsItem::ItemIsSelectable, true);
//                scene->addItem(item);
//                std::cout << "floor point: (" << i << "," << j << ")" << std::endl;
//            } else if (game->map->get(i, j) == Map::MapData::obstacle) {
//                // todo: print obstable
//            } else if (game->map->get(i, j) == Map::MapData::door) {
//                QImage image(":/images/map_door.jpeg");
//                if (image.isNull()) {
//                    QMessageBox::information(this, "Image Viewer", "Error Displaying image");
//                    return;
//                }
//                QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(image).scaled(itemWidth - 2, itemHeight - 3));
//                item->setPos((QPointF(j * itemWidth, i * itemHeight)));
//                item->setData(0, QVariant{QPointF{qreal(i), qreal(j)}});
//                scene->addItem(item);
//                std::cout << "floor point: (" << i << "," << j << ")" << std::endl;
//            }
//        }
//    }
    ui->graphicsView->setAlignment(Qt::AlignAbsolute);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
    for (int i = 0; i < game->map->characters.size(); ++i) {
        if (game->map->characters[i].getPos().getY() != -1 && game->map->characters[i].getPos().getX() != -1) {
            auto x = ui->graphicsView->scene()->itemAt(QPointF(game->map->characters[i].getPos().getY() * itemWidth, game->map->characters[i].getPos().getX() * itemHeight), QTransform());
//            QPainter painter(this);
//            painter.setPen(Qt::blue);
//            painter.setFont(QFont("Arial", 30));
//            painter.drawText(rect(), Qt::AlignCenter, "Qt");
//            QStyleOptionGraphicsItem qOptions;
//            x->paint(&painter, &qOptions);
        }
    }
//    QList<QGraphicsItem*> list = ui->graphicsView->scene()->items();
//    auto x = ui->graphicsView->scene()->itemAt(QPointF(5 * itemWidth, 10 * itemHeight), QTransform());
//    std::cout << x->data(0).toPointF().y() << "-" << x->data(0).toPointF().x() << std::endl;
}

bool MainWindow::inVision(Point2d p) {
    int i = p.getY(), j = p.getX();
    find_if(game->map->startPos.begin(), game->map->startPos.end(), [i, j](const Point2d& u) {
        if (u.getX() == i && u.getY() == j) return true;
        else return false;
    });
    return false;
}

void MainWindow::drawBlock(QGraphicsScene* scene, int r, int c, std::vector<Point2d>& traveled) {
    auto it = find_if(traveled.begin(), traveled.end(), [r, c](const Point2d& u) {
        if (u.getX() == c && u.getY() == r) return true;
        else return false;
    });
    if (it != traveled.end()) {
        return;
    }

    if (game->map->get(r, c) == Map::MapData::floor) {
        auto it = find_if(game->map->startPos.begin(), game->map->startPos.end(), [r, c](const Point2d& u) {
            if (u.getX() == c && u.getY() == r) return true;
            else return false;
        });
        QImage image;
        if (it != game->map->startPos.end()) {
            if (game->map->t < (2*game->map->characters.size())) {
                image = QImage(":/images/map_floor_with_start.jpg");
            } else {
                image = QImage(":/images/map_floor");
            }
        } else {
            image = QImage(":/images/map_floor");
        }
        if(image.isNull()) {
            QMessageBox::information(this,"Image Viewer","Error Displaying image");
            return;
        }
        QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(image).scaled(itemWidth - 2, itemHeight - 3));
        QObject::connect(scene, SIGNAL(selectionChanged()), this, SLOT(selectedChange()));
        item->setPos(QPointF(c * itemWidth, r * itemHeight));
        item->setData(0, QVariant{QPointF{qreal(c), qreal(r)}});
        if (game->map->t < (2*game->map->characters.size()) && it != game->map->startPos.end()) {
            item->setFlag(QGraphicsItem::ItemIsSelectable, true);
        }
        for (int i = 0; i < game->map->characters.size(); ++i) {
            if (game->map->characters[i].getPos().getY() == r && game->map->characters[i].getPos().getX() == c) {
                std::cout << "found character" << std::endl;
                QPixmap p = item->pixmap();
                QPainter *painter = new QPainter(&p);
                painter->setPen(Qt::blue);
                painter->setFont(QFont("Arial", 30));
                painter->drawText(QRect(0, 0, itemWidth-2, itemHeight-2), Qt::AlignCenter, QString(i + 'A'));
                painter->end();
                delete painter;
                item->setPixmap(p);
            }
        }
        scene->addItem(item);
        std::cout << "floor point: (" << r << "," << c << ")" << std::endl;
        std::cout << "(" << c * itemWidth << "," << r * itemHeight << std::endl;
    } else if (game->map->get(r, c) == Map::MapData::door) {
        QImage image(":/images/map_door.jpeg");
        if (image.isNull()) {
            QMessageBox::information(this, "Image Viewer", "Error Displaying image");
            return;
        }
        QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(image).scaled(itemWidth - 2, itemHeight - 3));
        item->setPos((QPointF(c * itemWidth, r * itemHeight)));
        item->setData(0, QVariant{QPointF{qreal(c), qreal(r)}});
        scene->addItem(item);
        std::cout << "floor point: (" << r << "," << c << ")" << std::endl;
        std::cout << "(" << c * itemWidth << "," << r * itemHeight << std::endl;
    }
    traveled.push_back(Point2d(nullptr, r, c));

    if (game->map->get(r, c) == Map::MapData::door || game->map->get(r, c) == Map::MapData::wall) {
        return;
    }
    Point2d p(nullptr, r-1, c);
    if (game->map->inBound(p)) {
        auto it = find_if(traveled.begin(), traveled.end(), [p](const Point2d& u) {
            if (u.getX() == p.getX() && u.getY() == p.getY()) return true;
            else return false;
        });
        if (it == traveled.end()) {
            drawBlock(scene, r-1, c, traveled);
        }
    }
    p.set(r, c+1);
    if (game->map->inBound(p)) {
        auto it = find_if(traveled.begin(), traveled.end(), [p](const Point2d& u) {
            if (u.getX() == p.getX() && u.getY() == p.getY()) return true;
            else return false;
        });
        if (it == traveled.end()) {
            drawBlock(scene, r, c+1, traveled);
        }
    }
    p.set(r+1, c);
    if (game->map->inBound(p)) {
        auto it = find_if(traveled.begin(), traveled.end(), [p](const Point2d& u) {
            if (u.getX() == p.getX() && u.getY() == p.getY()) return true;
            else return false;
        });
        if (it == traveled.end()) {
            drawBlock(scene, r, c+1, traveled);
        }
    }
    p.set(r,c-1);
    if (game->map->inBound(p)) {
        auto it = find_if(traveled.begin(), traveled.end(), [p](const Point2d& u) {
            if (u.getX() == p.getX() && u.getY() == p.getY()) return true;
            else return false;
        });
        if (it == traveled.end()) {
            drawBlock(scene, r, c-1, traveled);
        }
    }
}

void MainWindow::selectCharacterPos() {
}

void MainWindow::selectedChange() {
    QList<QGraphicsItem*> list = ui->graphicsView->scene()->selectedItems();
    if (list.size()) {
        std::cout << list.front()->data(0).toPointF().y() << "-" << list.front()->data(0).toPointF().x() << std::endl;
        game->map->characters[game->map->t/2].setPos(Point2d(nullptr, list.front()->data(0).toPointF().y(), list.front()->data(0).toPointF().x()));
        if (++game->map->t < (2*game->map->characters.size())) {
            ui->label_instruction->setText("Please select start position for character " + QString(QChar((int)(game->map->t/2)+'A')));

        } else {
            ui->label_instruction->setText("START GAME!");
            disconnect(ui->graphicsView->scene(), SIGNAL(selectionChanged()), this, SLOT(selectedChange()));
            showMap();
        }
    }
    ui->graphicsView->scene()->clearSelection();
}

void MainWindow::nothing() {
    std::cout << "nothing" << std::endl;
}

void MainWindow::start() {
    game->map->t = 0;
    ui->label_instruction->setText("Please select start position for character " + QString(QChar((int)(game->map->t/2)+'A')));
}
