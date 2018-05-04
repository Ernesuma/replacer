#include "tagmapmodel.h"
//#include "algorithm"

TagMapModel::TagMapModel(QObject *pParent):
    QAbstractTableModel(pParent),
    m_map()
{
    m_map["test_empty_constr"]="test_value_empty_constr";
}

TagMapModel::TagMapModel(const QMap<QString, QString> &map, QObject* pParent):
    QAbstractTableModel(pParent),
    m_map(map)
{
    m_map["one"]="ready";
}

int TagMapModel::rowCount(const QModelIndex &parent) const
{
    return m_map.count();
}

int TagMapModel::columnCount(const QModelIndex &parent) const
{
    if (m_map.isEmpty())
        return 0;
    else
        return 2;
}

Qt::ItemFlags TagMapModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
    {
        return Qt::ItemIsEnabled;
    }
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool TagMapModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && Qt::EditRole == role)
    {
        auto keys{m_map.uniqueKeys()};
        if (index.column() == 0)
        {
            QString tmpVal = m_map[keys[index.row()]];
            m_map.remove(keys[index.row()]);
            m_map[value.toString()] = tmpVal;
        }
        else
            m_map[keys[index.row()]] = value.toString();

        emit dataChanged(index, index);
        return true;
    }
    return false;
}

QVariant TagMapModel::data(const QModelIndex &index, const int role) const
{
    if (!index.isValid())
    {
        qWarning() << "WARNING: Invalid Index";
        return QVariant();
    }

    if (index.row() >= this->rowCount())
    {
        qWarning() << "WARNING: Invalid index.row";
        return QVariant();
    }

    if (Qt::DisplayRole == role || Qt::EditRole == role)
    {
        auto keys{m_map.uniqueKeys()};
        //std::sort(keys.begin(), keys.end());

        if (index.column() == 0)
        {
            qDebug() << "return '" << keys[index.row()] << "' for index (" << index.row() << "," << index.column() << ")";
            return keys[index.row()];
        }
        else
        {
            qDebug() << "return '" << m_map[keys[index.row()]] << "' for index (" << index.row() << "," << index.column() << ")";
            return m_map[keys[index.row()]];
        }
    }
    else
    {
        qDebug() << "WARNING: no valid return possible on index (" << index.row() << "," << index.column() << ") and role " << role ;
        return QVariant();
    }
}
