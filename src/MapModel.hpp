#pragma once

#include <QAbstractTableModel>

#include "Map.hpp"

class MapModel : public QAbstractTableModel
{
    Q_OBJECT

    public:
    explicit MapModel(Map *map, QObject *parent = nullptr);
    ~MapModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    // QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    Map *map;
};