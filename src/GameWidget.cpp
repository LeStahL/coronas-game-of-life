#include "ui_gamewidget.h"
#include "GameWidget.hpp"

#include <QAction>

GameWidget::GameWidget(QString mapUrl, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GameWidget)
    , mediaPlayer(new QMediaPlayer)
    , mediaPlaylist(new QMediaPlaylist)
    , map(new Map(mapUrl))
{
    ui->setupUi(this);

    QFile f(":/style/MainMenu.qss");
    if (!f.exists())
        qDebug() << "Style sheet for MainMenu is not present in resources.\n";
    else
    {
        f.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts(&f);
        setStyleSheet(ts.readAll());
        f.close();
    }

    mediaPlaylist->addMedia(QUrl("qrc:/music/CoronaGoL.mp3"));
    mediaPlaylist->setPlaybackMode(QMediaPlaylist::Loop);

    mediaPlayer->setPlaylist(mediaPlaylist);
    mediaPlayer->play();

    mapModel = new MapModel(map, this);

    this->addAction(ui->actionCycle);
    this->addAction(ui->actionUp);
    this->addAction(ui->actionDown);
    this->addAction(ui->actionRight);
    this->addAction(ui->actionLeft);

    ui->tableView->setModel(mapModel);
    update();
}

GameWidget::~GameWidget()
{
    delete ui;
    mediaPlayer->stop();
    delete mediaPlayer;
    delete mediaPlaylist;
    delete map;
    delete mapModel;
}

void GameWidget::cyclePlayers()
{
    map->nextPlayer();
    mapModel->update();
}

void GameWidget::moveUp()
{
    map->moveCurrentPlayerUp();
    mapModel->update();
}

void GameWidget::moveRight()
{
    map->moveCurrentPlayerRight();
    mapModel->update();
}

void GameWidget::moveLeft()
{
    map->moveCurrentPlayerLeft();
    mapModel->update();
}

void GameWidget::moveDown()
{
    map->moveCurrentPlayerDown();
    mapModel->update();
}