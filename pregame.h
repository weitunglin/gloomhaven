#ifndef PREGAME_H
#define PREGAME_H

#include <QMainWindow>
#include <QMessageBox>

#include "gloomhaven.h"

namespace Ui {
class PreGame;
}

class PreGame : public QMainWindow
{
    Q_OBJECT

public:
    explicit PreGame(QWidget *parent = nullptr);
    ~PreGame();

private slots:
    void on_playButton_clicked();
    void on_exitButton_clicked();

public slots:
    void restartGame(QString result);

private:
    Ui::PreGame *ui;
    Gloomhaven* game;
};

#endif // PREGAME_H
