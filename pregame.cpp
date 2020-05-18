#include "pregame.h"
#include "ui_pregame.h"

PreGame::PreGame(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PreGame)
{
    ui->setupUi(this);
    mainwindow = new MainWindow();
}

PreGame::~PreGame()
{
    delete ui;
    delete mainwindow;
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
            mainwindow->game = new Gloomhaven(nullptr, ui->textCharacterData->text(), ui->textMonsterData->text());
            mainwindow->showMap();
            mainwindow->show();
            this->hide();
            break;
        case QMessageBox::No:
            break;
        }
    } else {
        ui->textCharacterData->setText("character1.txt");
        ui->textMonsterData->setText("monster1.txt");
        std::cout << "ok, start game" << std::endl;
        mainwindow->game = new Gloomhaven(nullptr, ui->textCharacterData->text(), ui->textMonsterData->text());
        mainwindow->showMap();
        mainwindow->show();
        this->hide();
    }
}

void PreGame::on_exitButton_clicked()
{
    // exit game
    this->close();
}
