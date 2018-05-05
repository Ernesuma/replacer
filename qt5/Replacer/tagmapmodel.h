#ifndef TAGMAPMODEL_H
#define TAGMAPMODEL_H

#include <QDebug>
#include <QAbstractTableModel>
#include <QObject>
#include <QMap>

class TagMapModel : public QAbstractTableModel
{
    Q_OBJECT

private:
    // private Member
    // --------------
    QMap<QString, QString> m_map;

public:
    // declare constructors
    TagMapModel(QObject *pParent=0);
    TagMapModel(const QMap<QString, QString> &map, QObject* pParent = 0);

    // empty destructor
    ~TagMapModel(){}

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;

    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    bool insertRows(int row, int count, const QModelIndex &parent);
    bool removeRows(int row, int count, const QModelIndex &parent);
};

#endif // TAGMAPMODEL_H