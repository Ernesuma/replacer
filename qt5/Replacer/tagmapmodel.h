#ifndef TAGMAPMODEL_H
#define TAGMAPMODEL_H

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
    // declare constructor
    TagMapModel(const QMap<QString, QString> &map, QObject* pParent = 0);

    // empty destructor
    ~TagMapModel(){}

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;

};

#endif // TAGMAPMODEL_H
