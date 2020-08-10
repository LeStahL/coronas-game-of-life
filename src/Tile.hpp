#pragma once

#include <QChar>
#include <QVariant>
#include <QImage>
#include <QString>

class Tile
{
    public:
    Tile(QChar character = QChar(' '), QImage *image = nullptr, QString imagePath = QString(""), QString name = QString("Tile"));
    ~Tile() = default;

    QVariant serialize();
    void deserialize(QVariant data);

    QChar character;
    QImage *image;
    QString name,
        imagePath;
    bool hasCorona;
};
