#pragma once

#include <QWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>

#include "Map.hpp"

namespace Ui{ class GameWidget; }

class GameWidget : public QWidget
{
    Q_OBJECT

    public:
    GameWidget(QString mapUrl, QWidget *parent = nullptr);
    ~GameWidget();

    private slots:

    private:
    Map *map;
    Ui::GameWidget *ui;
    QMediaPlayer *mediaPlayer;
    QMediaPlaylist *mediaPlaylist;
};
