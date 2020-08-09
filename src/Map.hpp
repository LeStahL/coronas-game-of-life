#pragma once

#include "Tile.hpp"

class Map
{
    public:
    Map(QString filePath);

    static QList<QString> listMaps(QString directoryPath);
    void initializeCorona();
    void iterateCorona();

    QList<QList<Tile>> tiles;
};