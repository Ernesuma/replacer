#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QModelIndex>
#include <QtDebug>
#include <QApplication>
#include <QClipboard>
#include <memory>

#include "tagmapmodel.h"
#include "replacer.h"

class Controller
{
private:
    //std::unique_ptr<Ui::MainWindow> m_pUiHandle;
    QString m_plainText{""};
    std::unique_ptr<TagMapModel> m_pTagMapModel{new TagMapModel()};

public:
    // constructor
    Controller(){};
    // destructor
    ~Controller(){};

    // grant access to the raw pointer: USE WITH CARE!
    TagMapModel* GetTagMapModelRaw(){return m_pTagMapModel.get();};

    QString& SetPlainText(const QString& plainText);
    QString GetPlainText() const;
    QString GetFinalText() const;
    QString Plain2Clipboard() const;
    QString Final2Clipboard() const;

    bool RemoveTags(const QModelIndexList& rows);
};

#endif // CONTROLLER_H
