#pragma once

#include "Tile.hpp"

class Map
{
    public:
    Map(QString filePath);

    static QList<QString> listMaps(QString directoryPath);
    void initializeCorona();
    void iterateCorona();

    void deserialize(QVariant data);

    QList<QList<Tile>> tiles;
};