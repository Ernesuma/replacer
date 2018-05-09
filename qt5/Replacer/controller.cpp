#include "controller.h"

QString &Controller::SetPlainText(const QString& plainText)
{
    m_plainText = plainText;
    return m_plainText;
}

QString Controller::GetPlainText() const
{
    return m_plainText;
}

QString Controller::GetFinalText() const
{
    QString finalText{};
    Replacer rep{};
    rep.replace(this->GetPlainText(),
                     finalText,
                     m_pTagMapModel.get()->getTagMap());
    return finalText;
}

QString Controller::Plain2Clipboard() const
{
    QString tmp = this->GetPlainText();
    QApplication::clipboard()->setText(tmp);
    return tmp;
}

QString Controller::Final2Clipboard() const
{
    QString tmp = this->GetFinalText();
    QApplication::clipboard()->setText(tmp);
    return tmp;
}

bool Controller::RemoveTags(const QModelIndexList &rows)
{
    return m_pTagMapModel.get()->removeRows(rows);
}
