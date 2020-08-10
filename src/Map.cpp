#include "Map.hpp"

#include <QDirIterator>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QVariantList>

Map::Map(QString filePath)
{
    QFile f(filePath);
    if (!f.exists())
        qDebug() << filePath + " does not exist.\n";
    else
    {
        f.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts(&f);
        deserialize(QVariant(ts.readAll()));
        f.close();
    }
}


void Map::initializeCorona()
{

}

void Map::iterateCorona()
{

}

QVariant Map::serialize()
{
    return QVariant();
}

void Map::deserialize(QVariant data)
{
    QJsonDocument jsonDocument = QJsonDocument::fromJson(data.toByteArray());
    QJsonObject jsonObject = jsonDocument.object();

    // Read meta info
    name = jsonObject["name"].toString();
    background = QImage(jsonObject["background"].toString());

    // Read layout
    QVariantList layoutVariantList = jsonObject["layout"].toArray().toVariantList();
    layout.clear();
    for(int i=0; i<layoutVariantList.size(); ++i)
    {
        layout << layoutVariantList.at(i).toString();
    }
    size = QSize(layout.first().size(), layout.size());

    // Read tiles
    QJsonArray tilesJson = jsonObject["tiles"].toArray();
    tiles.clear();
    for(int i=0; i<tilesJson.size(); ++i)
    {
        Tile t;
        t.deserialize(tilesJson.at(i).toVariant());
        tiles.push_back(t);
    }
}

Tile *Map::tileFromChar(QChar character)
{
    for(int i=0; i<tiles.size(); ++i)
    {
        if(tiles.at(i).character == character) 
            return (Tile*)&(tiles.at(i));
    }
    return nullptr;
}

Tile *Map::tileAt(int x, int y)
{
    if(x >= size.width() || x < 0) return nullptr;
    if(y >= size.height() || y < 0) return nullptr;

    QChar character = layout.at(y)[x];
    return tileFromChar(character);
}
