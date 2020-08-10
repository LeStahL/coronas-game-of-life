#include "MapModel.hpp"

#include <QPixmap>

MapModel::MapModel(Map *_map, QObject *parent)
    : QAbstractTableModel(parent)
    , map(_map)
{
}

MapModel::~MapModel()
{
}

int MapModel::rowCount(const QModelIndex &parent) const
{
    return map->size.height();
}

int MapModel::columnCount(const QModelIndex &parent) const
{
    return map->size.width();
}

QVariant MapModel::data(const QModelIndex &index, int role) const
{
    if(role == Qt::DecorationRole)
    {
        if(QPoint(index.column(), index.row()) == map->activePlayerCoordinate)
        {
            return QVariant(map->tileAt(index.column(), index.row())->image->createMaskFromColor(QColor::fromRgb(255,0,0).rgb()));
        }

        return QVariant(*map->tileAt(index.column(), index.row())->image);
    }
    return QVariant();
}

void MapModel::update()
{
    emit dataChanged(index(0,0), index(map->size.height(), map->size.width()));
}