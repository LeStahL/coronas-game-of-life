#pragma once

#include "Tile.hpp"

#include <QList>
#include <QDirIterator>
#include <QDebug>

class Map
{
    public:
    Map(QString filePath);

    static QList<QString> listMaps(QString directoryPath)
    {
        QList<QString> maps;
        QDirIterator it(":/maps", QDirIterator::Subdirectories);
        while (it.hasNext()) {
            maps << it.next();
        }
        qDebug() << maps;
        return maps;
    }

    void initializeCorona();
    void iterateCorona();

    Tile *tileAt(int x, int y);
    Tile *tileFromChar(QChar character);

    QVariant serialize();
    void deserialize(QVariant data);

    QList<Tile> tiles;
    QList<QString> layout;

    QString name;
    QImage background;
    QSize size;
};
