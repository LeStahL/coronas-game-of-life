#include "Map.hpp"

#include <QDirIterator>
#include <QDebug>

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

}
