#pragma once

#include <QChar>
#include <QVariant>
#include <QImage>

class Tile
{
    public:
    Tile(QChar character, QImage image);
    ~Tile() = default;

    QVariant serialize();

    QChar character;
    QImage image;
    bool hasCorona;
};