#include "MapModel.hpp"

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
    if(role == Qt::DisplayRole)
    {
        return QVariant(map->tileAt(index.column(), index.row())->image);
    }
    return QVariant();
}
