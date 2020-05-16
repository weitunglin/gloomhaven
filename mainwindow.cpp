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

void MainWindow::on_playButton_clicked()
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
            game = new Gloomhaven(nullptr, ui->textCharacterData->text().toStdString(), ui->textMonsterData->text().toStdString());
            break;
        case QMessageBox::No:
            break;
        }
    } else {
        ui->textCharacterData->setText("character1.txt");
        ui->textMonsterData->setText("monster1.txt");
        std::cout << "ok, start game" << std::endl;
        game = new Gloomhaven(nullptr, ui->textCharacterData->text().toStdString(), ui->textMonsterData->text().toStdString());
    }
}

void MainWindow::on_exitButton_clicked()
{
    // exit game
    this->close();
}
