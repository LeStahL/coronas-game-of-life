#include "Tile.hpp"

#include <QJsonObject>
#include <QDebug>

Tile::Tile(QChar _character, QImage _image, QString _imagePath, QString _name)
    : character(_character)
    , image(_image)
    , hasCorona(false)
    , name(_name)
    , imagePath(_imagePath)
{
}

QVariant Tile::serialize()
{
    QJsonObject data;
    data.insert("name", QJsonValue(name));
    data.insert("character", QJsonValue(QString(character)));
    data.insert("image", QJsonValue(imagePath));
    return QVariant(data);
}

void Tile::deserialize(QVariant data)
{
    QJsonObject json = data.toJsonObject();
    name = json["name"].toString();
    character = QChar(json["character"].toString()[0]);
    imagePath = json["image"].toString();

    image = QImage(imagePath);
    hasCorona = false;
}