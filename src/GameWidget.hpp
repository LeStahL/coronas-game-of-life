#pragma once

#include <QWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>

#include "Map.hpp"
#include "MapModel.hpp"

namespace Ui{ class GameWidget; }

class GameWidget : public QWidget
{
    Q_OBJECT

    public:
    GameWidget(QString mapUrl, QWidget *parent = nullptr);
    ~GameWidget();

    private slots:
    void cyclePlayers();
    void moveRight();
    void moveLeft();
    void moveUp();
    void moveDown();

    private:
    Map *map;
    MapModel *mapModel;
    Ui::GameWidget *ui;
    QMediaPlayer *mediaPlayer;
    QMediaPlaylist *mediaPlaylist;
};
