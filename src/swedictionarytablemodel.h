#ifndef SWEDICTIONARYTABLEMODEL_H
#define SWEDICTIONARYTABLEMODEL_H

#include <QSqlTableModel>

class SweDictionaryTableModel : public QSqlTableModel
{
    Q_OBJECT

public:
    explicit SweDictionaryTableModel(QObject *parent = 0, QSqlDatabase db = QSqlDatabase()) : QSqlTableModel(parent, db) {}
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &idx, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
};

#endif // SWEDICTIONARYTABLEMODEL_H
