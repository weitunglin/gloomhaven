#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete game;
}


void MainWindow::showMap() {
    QGraphicsScene *scene = new QGraphicsScene();
    ui->graphicsView->setAlignment(Qt::AlignAbsolute);
    std::cout << "g view size: (" << ui->graphicsView->width() << "," << ui->graphicsView->height() << ")" << std::endl;
    int itemWidth = ui->graphicsView->width() / game->map->col;
    int itemHeight = ui->graphicsView->height() / game->map->row;
    std::cout << "itemSize: (" << itemWidth << "," << itemHeight << ")" << std::endl;
    std::vector<Point2d> traveled;
    std::cout << "start: (" << game->map->pos->getY() << "," << game->map->pos->getX() << ")" << std::endl;
    drawBlock(scene, game->map->pos->getY(), game->map->pos->getX(), traveled, itemWidth, itemHeight);
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
}

bool MainWindow::inVision(Point2d p) {
    int i = p.getY(), j = p.getX();
    auto it = find_if(game->map->startPos.begin(), game->map->startPos.end(), [i, j](const Point2d& u) {
        if (u.getX() == i && u.getY() == j) return true;
        else return false;
    });
}

void MainWindow::drawBlock(QGraphicsScene* scene, int r, int c, std::vector<Point2d>& traveled, int itemWidth, int itemHeight) {
    if (game->map->get(r, c) == Map::MapData::floor) {
        auto it = find_if(game->map->startPos.begin(), game->map->startPos.end(), [r, c](const Point2d& u) {
            if (u.getX() == c && u.getY() == r) return true;
            else return false;
        });
        QImage image;
        if (it != game->map->startPos.end()) {
            image = QImage(":/images/map_floor_with_start.jpg");
        } else {
            image = QImage(":/images/map_floor");
        }
        if(image.isNull()) {
            QMessageBox::information(this,"Image Viewer","Error Displaying image");
            return;
        }
        QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(image).scaled(itemWidth - 2, itemHeight - 3));
        item->setPos(QPointF(c * itemWidth, r * itemHeight));
        item->setFlag(QGraphicsItem::ItemIsSelectable, true);
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
        item->setData(0, QVariant{QPointF{qreal(r), qreal(c)}});
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
            drawBlock(scene, r-1, c, traveled, itemWidth, itemHeight);
        }
    }
    p.set(r, c+1);
    if (game->map->inBound(p)) {
        auto it = find_if(traveled.begin(), traveled.end(), [p](const Point2d& u) {
            if (u.getX() == p.getX() && u.getY() == p.getY()) return true;
            else return false;
        });
        if (it == traveled.end()) {
            drawBlock(scene, r, c+1, traveled, itemWidth, itemHeight);
        }
    }
    p.set(r+1, c);
    if (game->map->inBound(p)) {
        auto it = find_if(traveled.begin(), traveled.end(), [p](const Point2d& u) {
            if (u.getX() == p.getX() && u.getY() == p.getY()) return true;
            else return false;
        });
        if (it == traveled.end()) {
            drawBlock(scene, r, c+1, traveled, itemWidth, itemHeight);
        }
    }
    p.set(r,c-1);
    if (game->map->inBound(p)) {
        auto it = find_if(traveled.begin(), traveled.end(), [p](const Point2d& u) {
            if (u.getX() == p.getX() && u.getY() == p.getY()) return true;
            else return false;
        });
        if (it == traveled.end()) {
            drawBlock(scene, r, c-1, traveled, itemWidth, itemHeight);
        }
    }
}
