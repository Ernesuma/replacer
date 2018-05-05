#include "tagmapmodel.h"
//#include "algorithm"

TagMapModel::TagMapModel(QObject *pParent):
    QAbstractTableModel(pParent),
    m_map()
{
    // TEST: add a test entry to the map
    m_map["test_empty_constr"]="test_value_empty_constr";
}

TagMapModel::TagMapModel(const QMap<QString, QString> &map, QObject* pParent):
    QAbstractTableModel(pParent),
    m_map(map)
{ }

int TagMapModel::rowCount(const QModelIndex &parent) const
{
    // the number of map entries shall equal the number of table rows
    return m_map.count();
}

int TagMapModel::columnCount(const QModelIndex &parent) const
{
    // with an empty map there are no columns
    if (m_map.isEmpty())
        return 0;
    else
        // a map consists of key/value pairs -> two columns
        return 2;
}

Qt::ItemFlags TagMapModel::flags(const QModelIndex &index) const
{
    // no valid index
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
        // get list of map keys
        auto keys{m_map.uniqueKeys()};

        // column 0 means to set the key
        if (index.column() == 0)
        {
            // save value
            QString tmpVal = m_map[keys[index.row()]];
            // remove entry from map
            m_map.remove(keys[index.row()]);
            // add value with new key
            m_map[value.toString()] = tmpVal;
        }
        // not column 0 means to set the value
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

    // with vald roles
    if (Qt::DisplayRole == role || Qt::EditRole == role)
    {
        // get list of map keys
        auto keys{m_map.uniqueKeys()};

        // column 0 means key requested
        if (index.column() == 0)
        {
            qDebug() << "return '" << keys[index.row()] << "' for index (" << index.row() << "," << index.column() << ")";
            // return key from position 'row' in key-list 'keys'
            return keys[index.row()];
        }
        // not column 0 means value requested
        else
        {
            qDebug() << "return '" << m_map[keys[index.row()]] << "' for index (" << index.row() << "," << index.column() << ")";
            // return value to key from key-list 'keys' at position 'row'
            return m_map[keys[index.row()]];
        }
    }
    else
    {
        qDebug() << "WARNING: no valid return possible on index (" << index.row() << "," << index.column() << ") and role " << role ;
        return QVariant();
    }
}

QVariant TagMapModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (Qt::DisplayRole == role)
    {
        if (Qt::Orientation::Horizontal == orientation)
        {
            if (0 == section)
            {
                return QString("Key");
            }
            else
            {
                return QString("Value");
            }
        }
    }
    return QVariant();
}

bool TagMapModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row+count-1);
    qDebug() << "insert rows";
    for (int i{row}; i<row+count; ++i)
    {
        m_map[QString::number(row)] = "";
    }

    endInsertRows();
    return true;
}

bool TagMapModel::removeRows(int row, int count, const QModelIndex &parent)
{
    qInfo() << "remove rows";
    // inform connected views about the starting removal of rows
    beginRemoveRows(parent, row, row+count-1);

    // get list of all map keys
    auto keys = m_map.uniqueKeys();

    // get a sub-list of keys to remove
    auto keys2remove{keys.mid(row, count)};

    // remove the keys2remove from the map
    foreach (auto key, keys2remove)
    {
        m_map.remove(key);
    }

    // inform the connected views about the finished removal of rows
    endRemoveRows();
    return true;
}
