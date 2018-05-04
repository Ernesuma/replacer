#include "tagmapmodel.h"
#include <QList>

TagMapModel::TagMapModel(const QMap<QString, QString> &map, QObject* pParent):
    QAbstractTableModel(pParent),
    m_map(map)
{
}

int TagMapModel::rowCount(const QModelIndex &parent) const
{
    return m_map.count();
}

int TagMapModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant TagMapModel::data(const QModelIndex &index, const int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= this->rowCount())
            return QVariant();

    if (Qt::DisplayPropertyRole == role || Qt::EditRole == role)
    {
        QList<QString> keys{m_map.uniqueKeys()};
        return m_map[keys[index.row()]];
    }
    else
        return QVariant();
}
