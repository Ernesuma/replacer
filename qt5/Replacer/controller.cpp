#include "controller.h"

bool readFile2String(const QDir& path, QString& readText)
{
    bool retVal{false};
    QFile data(path.path());
    if (data.open(QFile::ReadOnly | QFile::Text))
    {
        QTextStream in(&data);
        readText = in.readAll();
        retVal = true;
    }
    data.close();
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
    m_pTagMapModel.get()->removeRows(rows);
}

bool Controller::replace()
{
    Replacer rep{};
    return rep.replace(this->GetPlainText(),
                        m_finalText,
                        m_pTagMapModel.get()->getTagMap());
}

bool Controller::importPlain(const QDir& path)
{
    return readFile2String(path, m_plainText);
}
