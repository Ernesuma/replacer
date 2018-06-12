#include "controller.h"

bool readFile2String(const QDir& path, QString& readText)
{
    bool retVal{false};
    QFile data(path.absolutePath());
    if (data.open(QFile::ReadOnly | QFile::Text))
    {
        QTextStream in(&data);
        readText = in.readAll();
        retVal = true;
    }
    data.close();
    return retVal;
}

bool writeString2File(const QDir& path, const QString& writeText)
{
    bool retVal{false};
    QFile data(path.absolutePath());
    if (data.open(QFile::WriteOnly | QFile::Text))
    {
        QTextStream out(&data);
        out << writeText;
        retVal = true;
    }
    data.close();
    return retVal;
}

bool writeTagMap2File(const QDir& path, const tagMap &tags)
{
    bool retVal{false};

    QFile data(path.absolutePath());
    if (data.open(QFile::WriteOnly | QFile::Text))
    {
        QTextStream out(&data);

        auto keys{tags.uniqueKeys()};
        foreach (auto key, keys)
        {
            out << key << "," << tags[key] << "\n";
        }
        retVal = true;
    }
    data.close();
    return retVal;
}

bool readFile2TagMap(const QDir &path, tagMap &tags)
{
    bool retVal{false};

    QFile data(path.absolutePath());
    if (data.open(QFile::ReadOnly | QFile::Text))
    {
        QTextStream in(&data);

        QString row{};
        retVal = true;
        while (!in.atEnd())
        {
            in.readLineInto(&row);
            QStringList rowList = row.split(",");
            qInfo() << rowList;
            if (2 == rowList.size())
            {
                tags[rowList[0]] = rowList[1];
            }
            else
            {
                qWarning() << "WARNING: invalid tag list file to import";
                retVal = false;
                break;
            }
        }
    }
    return retVal;
}

bool Controller::isTagMapEmpty() const
{
    return m_pTagMapModel.get()->getTagMap().isEmpty();
}

void Controller::SetPlainText(const QString& plainText)
{
    m_plainText = plainText;
}

const QString &Controller::GetPlainText() const
{
    return m_plainText;
}

const QString &Controller::GetFinalText() const
{
    return m_finalText;
}

const QString &Controller::Plain2Clipboard() const
{
    const QString& tmp = this->GetPlainText();
    QApplication::clipboard()->setText(tmp);
    return tmp;
}

const QString &Controller::Final2Clipboard() const
{
    const QString& tmp = this->GetFinalText();
    QApplication::clipboard()->setText(tmp);
    return tmp;
}

bool Controller::RemoveTags(const QModelIndexList &rows)
{
    return m_pTagMapModel.get()->removeRows(rows);
}

bool Controller::RemoveAllTags()
{
    return m_pTagMapModel.get()->removeAllRows();
}

bool Controller::replace()
{
    Replacer rep{};
    return rep.replace(this->GetPlainText(),
                        m_finalText,
                        m_pTagMapModel.get()->getTagMap());
}

bool Controller::isValidProjectName(const QString &name) const
{
    return Project::isValidName(name);
}

bool Controller::isProjectSet() const
{
    return m_project.isSet();
}

void Controller::newProject(MainWindow *ui)
{
    // if there is some text or some tags:
    // ask user for confirmation to clear everything
    if (!(isTagMapEmpty() &
          GetPlainText().isEmpty() &
          GetFinalText().isEmpty()))
    {
        QString title{QString("New Project")};
        QString info{QString("Do you really want to create a new project?\nAll unsaved changes will be lost…")};
        if (!reallyAllNew(ui, title, info))
        {
            // abort creation of new menu
            return;
        }
    }

    // clear all texts and tags
    ui->clearTextEdits();
    clear();

    // open new project dialog
    ProjectDialog projDialog("Setup New Project", ui);
    projDialog.exec();
    qInfo() << "was cancelled: " << projDialog.wasCancelled();
    qInfo() << "projName: " << projDialog.getProjectName();
    qInfo() << "projDir: " << projDialog.getProjectDir();

    // if projDialog was cancelled by user
    if (projDialog.wasCancelled())
    {
        // abort creation of new project
        return;
    }

    // make some checks with name and path
    const auto name = projDialog.getProjectName();
    const auto path = projDialog.getProjectDir();
    // is name empty?
    if (name.isEmpty())
    {
        warnMsgBox("ERROR: Creation of new project aborted:",
                   "No project name provided!",
                   ui);
        return;
    }

    // is name valid?
    if (!isValidProjectName(name))
    {
        warnMsgBox("ERROR: Creation of new project aborted. No valid project name:",
                   name,
                   ui);
        return;
    }

    if(!path.exists())
    {
        warnMsgBox("ERROR: provided path does not exist:",
                   path.path(),
                   ui);
        return;
    }

    // append name to path to test for already existing directory
    QDir projPath = QDir(path.absolutePath() + QDir::separator() + name);

    // if directory does not exist, create it
    if (!projPath.exists())
    {
        if (!path.mkdir(name))
        {
            warnMsgBox("ERROR: Could not create project directory! Aborted creating new project.",
                       projPath.absolutePath(),
                       ui);
            return;
        }
    }

    // set the new project as active project
    m_project.set(name, projPath);
    ((MainWindow*) ui)->updateProjectInfoLabel();
}

void Controller::saveProject(QWidget *ui) const
{
    if (!isProjectSet())
    {
        warnMsgBox("ERROR: No project set!", "", ui);
    }
    else
    {
        // use export function to save plain text to file in project dir
        QString plainFile{appendSuffix(getProjectName(), "plain")};
        QDir filePathPlain{concatinatePaths(getProjectPath(), QDir(plainFile))};
        exportPlain(filePathPlain);

        // use export function to save tags to file in project dir
        QString tagFile{appendSuffix(getProjectName(), "tags")};
        QDir filePathTags{concatinatePaths(getProjectPath(), QDir(tagFile))};
        exportTagList(filePathTags);
    }
}

const QString &Controller::getProjectName() const
{
    return m_project.getProjectName();
}

const QDir &Controller::getProjectPath() const
{
    return m_project.getProjectPath();
}

bool Controller::exportPlain(const QDir &path) const
{
    return writeString2File(path, m_plainText);
}

bool Controller::importPlain(const QDir& path)
{
    return readFile2String(path, m_plainText);
}

bool Controller::exportFinal(const QDir &path) const
{
    return writeString2File(path, m_finalText);
}

bool Controller::exportTagList(const QDir &path) const
{
    return writeTagMap2File(path, m_pTagMapModel.get()->getTagMap());
}

bool Controller::importTagList(const QDir &path)
{
    tagMap tmp{};
    bool retVal = readFile2TagMap(path, tmp);
    if (retVal)
    {
        this->RemoveAllTags();
        foreach(auto key, tmp.uniqueKeys())
        {
            m_pTagMapModel.get()->insert(key, tmp[key]);
        }
    }
    return retVal;
}

void Controller::clear()
{
    RemoveAllTags();
    SetPlainText("");
    m_finalText = QString("");
}
