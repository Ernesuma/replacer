#include "controller.h"

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
