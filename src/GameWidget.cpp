#include "ui_gamewidget.h"
#include "GameWidget.hpp"

GameWidget::GameWidget(QString mapUrl, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GameWidget)
    , mediaPlayer(new QMediaPlayer)
    , mediaPlaylist(new QMediaPlaylist)
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
}

GameWidget::~GameWidget()
{
    delete ui;
    mediaPlayer->stop();
    delete mediaPlayer;
    delete mediaPlaylist;
}
