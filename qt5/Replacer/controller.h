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
    QString m_finalText{""};
    std::unique_ptr<TagMapModel> m_pTagMapModel{new TagMapModel()};

public:
    // constructor
    Controller(){};
    // destructor
    ~Controller(){};

    // grant access to the raw pointer: USE WITH CARE!
    TagMapModel* GetTagMapModelRaw(){return m_pTagMapModel.get();};

    void SetPlainText(const QString& plainText);
    const QString &GetPlainText() const;
    const QString &GetFinalText() const;
    const QString &Plain2Clipboard() const;
    const QString &Final2Clipboard() const;

    bool isTagMapEmpty() const;
    bool RemoveTags(const QModelIndexList& rows);
    bool replace();
};

#endif // CONTROLLER_H
