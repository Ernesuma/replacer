#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QModelIndex>
#include <QtDebug>
#include <QApplication>
#include <QClipboard>
#include <memory>
#include <QDir>

#include "tagmapmodel.h"
#include "replacer.h"
#include "project.h"


class Controller
{
private:
    //std::unique_ptr<Ui::MainWindow> m_pUiHandle;
    QString m_plainText{""};
    QString m_finalText{""};
    std::unique_ptr<TagMapModel> m_pTagMapModel{new TagMapModel()};
    Project m_project{Project()};

public:
    // constructor
    Controller(){};
    // destructor
    ~Controller(){};

    // grant access to the raw pointer: USE WITH CARE!
    TagMapModel* GetTagMapModelRaw(){return m_pTagMapModel.get();};

    // getter and setter
    void SetPlainText(const QString& plainText);
    const QString &GetPlainText() const;
    const QString &GetFinalText() const;
    const QString &Plain2Clipboard() const;
    const QString &Final2Clipboard() const;

    bool isTagMapEmpty() const;
    bool isProjectSet() const;
    bool RemoveTags(const QModelIndexList& rows);
    bool RemoveAllTags();
    bool replace();

    bool newProject(const QDir& path);
    bool saveProject(const QDir &path) const;

    bool exportPlain(const QDir &path) const;
    bool importPlain(const QDir &path);
    bool exportFinal(const QDir &path) const;

    bool exportTagList(const QDir &path) const;
    bool importTagList(const QDir &path);
};

#endif // CONTROLLER_H
