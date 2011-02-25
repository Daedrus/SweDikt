#include "swedictionarytablemodel.h"

int SweDictionaryTableModel::rowCount(const QModelIndex &parent) const
{
    return QSqlTableModel::rowCount(parent) + 1;
}

QVariant SweDictionaryTableModel::data(const QModelIndex &idx, int role) const
{
    if (idx.isValid() && role == Qt::DisplayRole) {
        if (idx.row() == QSqlTableModel::rowCount())
            return QVariant();
        else
            return QSqlTableModel::data(idx, role);
    } else {
        return QSqlTableModel::data(idx, role);
    }
}

bool SweDictionaryTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        if (index.row() == QSqlTableModel::rowCount()) {
            insertRow(QSqlTableModel::rowCount());
            return QSqlTableModel::setData(index, value, role);
        } else {
            return QSqlTableModel::setData(index, value, role);
        }
    } else {
        return QSqlTableModel::setData(index, value, role);
    }
}
