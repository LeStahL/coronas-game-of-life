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
