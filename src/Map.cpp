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

    QList<QPoint> availablePlayerCoordinates = playerCoordinates();
    activePlayerCoordinate = availablePlayerCoordinates.at(0);
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

    // update player and floor character 
    playerCharacter = getPlayerCharacter();
    floorCharacter = getFloorCharacter();
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

QChar Map::getPlayerCharacter()
{
    QChar playerCharacter;
    for(int i=0; i<tiles.size(); ++i)
    {
        if(tiles.at(i).name == "Player")
            playerCharacter = tiles.at(i).character;
    }
    return playerCharacter;
}

QChar Map::getFloorCharacter()
{
    QChar playerCharacter;
    for(int i=0; i<tiles.size(); ++i)
    {
        if(tiles.at(i).name == "Floor")
            playerCharacter = tiles.at(i).character;
    }
    return playerCharacter;
}

QList<QPoint> Map::playerCoordinates()
{
    // Use player char to determine player coordinates
    QList<QPoint> coordinates;
    for(int i=0; i<size.width(); ++i)
    {
        for(int j=0; j<size.height(); ++j)
        {
            if(layout.at(j)[i] == playerCharacter)
                coordinates << QPoint(i, j);
        }
    }
    return coordinates;
}

void Map::nextPlayer()
{
    QList<QPoint> availablePlayerCoordinates = playerCoordinates();

    int index = availablePlayerCoordinates.indexOf(activePlayerCoordinate);
    index = (index + 1) % availablePlayerCoordinates.size();
    activePlayerCoordinate = availablePlayerCoordinates[index];
}

void Map::moveCurrentPlayerUp()
{
    // Check if player can move there
    QPoint newLocation = QPoint(activePlayerCoordinate.x(), activePlayerCoordinate.y()-1);
    if(newLocation.y() < 0) return;
    if(newLocation.y() >= size.height()) return;
    
    Tile *newTile = tileAt(newLocation.x(), newLocation.y());
    if(newTile->name == "Wall")return;
    if(newTile->name == "Player")return;

    // Move player there
    setCharAt(activePlayerCoordinate.x(), activePlayerCoordinate.y(), floorCharacter);
    setCharAt(newLocation.x(), newLocation.y(), playerCharacter);
    activePlayerCoordinate = newLocation;
}

void Map::moveCurrentPlayerRight()
{
    // Check if player can move there
    QPoint newLocation = QPoint(activePlayerCoordinate.x()+1, activePlayerCoordinate.y());
    if(newLocation.x() < 0) return;
    if(newLocation.x() >= size.width()) return;
    
    Tile *newTile = tileAt(newLocation.x(), newLocation.y());
    if(newTile->name == "Wall")return;
    if(newTile->name == "Player")return;

    // Move player there
    setCharAt(activePlayerCoordinate.x(), activePlayerCoordinate.y(), floorCharacter);
    setCharAt(newLocation.x(), newLocation.y(), playerCharacter);
    activePlayerCoordinate = newLocation;
}

void Map::moveCurrentPlayerDown()
{
    // Check if player can move there
    QPoint newLocation = QPoint(activePlayerCoordinate.x(), activePlayerCoordinate.y()+1);
    if(newLocation.y() < 0) return;
    if(newLocation.y() >= size.height()) return;
    
    Tile *newTile = tileAt(newLocation.x(), newLocation.y());
    if(newTile->name == "Wall")return;
    if(newTile->name == "Player")return;

    // Move player there
    setCharAt(activePlayerCoordinate.x(), activePlayerCoordinate.y(), floorCharacter);
    setCharAt(newLocation.x(), newLocation.y(), playerCharacter);
    activePlayerCoordinate = newLocation;
}

void Map::moveCurrentPlayerLeft()
{
    // Check if player can move there
    QPoint newLocation = QPoint(activePlayerCoordinate.x()-1, activePlayerCoordinate.y());
    if(newLocation.x() < 0) return;
    if(newLocation.x() >= size.width()) return;
    
    Tile *newTile = tileAt(newLocation.x(), newLocation.y());
    if(newTile->name == "Wall")return;
    if(newTile->name == "Player")return;

    // Move player there
    setCharAt(activePlayerCoordinate.x(), activePlayerCoordinate.y(), floorCharacter);
    setCharAt(newLocation.x(), newLocation.y(), playerCharacter);
    activePlayerCoordinate = newLocation;
}

void Map::setCharAt(int x, int y, QChar character)
{
    layout[y][x] = character;
}