#include "pregame.h"
#include "ui_pregame.h"

PreGame::PreGame(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PreGame)
{
    ui->setupUi(this);
    game = new Gloomhaven(nullptr);
}

PreGame::~PreGame()
{
    delete ui;
    delete game;
}

void PreGame::on_playButton_clicked()
{
    // start playing game
    std::cout << "play button clicked" << std::endl;
    if (ui->textCharacterData->text().toStdString() == "" || ui->textMonsterData->text().toStdString() == "") {
        QMessageBox msgBox;
        msgBox.setText("Invalid Character or Monster Data.");
        msgBox.setInformativeText("Do you want to use default('character1.txt' and 'monster1.txt')?");
        msgBox.setStandardButtons(QMessageBox::No | QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        int ret = msgBox.exec();
        switch (ret) {
        case QMessageBox::Ok:
            ui->textCharacterData->setText("character1.txt");
            ui->textMonsterData->setText("monster1.txt");
            std::cout << "ok, start game" << std::endl;
            connect(game, SIGNAL(endGame(QString)), this, SLOT(restartGame(QString)));
            game->setFileData(ui->textCharacterData->text(), ui->textMonsterData->text(), ui->inputDebugMode->value());
            game->showMap();
            game->show();
            game->start();
            this->hide();
            break;
        case QMessageBox::No:
            break;
        }
    } else {
        ui->textCharacterData->setText("character1.txt");
        ui->textMonsterData->setText("monster1.txt");
        std::cout << "ok, start game" << std::endl;
        connect(game, SIGNAL(endGame(QString)), this, SLOT(restartGame(QString)));
        game->setFileData(ui->textCharacterData->text(), ui->textMonsterData->text(), ui->inputDebugMode->value());
        game->showMap();
        game->show();
        game->start();
        this->hide();
    }
}

void PreGame::on_exitButton_clicked()
{
    // exit game
    this->close();
}

void PreGame::restartGame(QString result) {
    game->hide();
    game = new Gloomhaven(nullptr);
    ui->welcomeText->setText(result);
    this->show();
    ui->textCharacterData->setText("character1.txt");
    ui->textMonsterData->setText("monster1.txt");
}
