#include <QtDebug>
#include <QApplication>
#include <QClipboard>
#include "model.h"

Model::Model()
{

}

Model::~Model()
{

}

QString &Model::SetPlainText(const QString& plainText)
{
    m_plainText = plainText;
    return m_plainText;
}

QString Model::GetPlainText() const
{
    return m_plainText;
}

QString Model::GetFinalText() const
{
    QString finalText{this->GetPlainText() + "This is final!"};
    return finalText;
}

QString Model::Plain2Clipboard() const
{
    QString tmp = this->GetPlainText();
    QApplication::clipboard()->setText(tmp);
    return tmp;
}

QString Model::Final2Clipboard() const
{
    QString tmp = this->GetFinalText();
    QApplication::clipboard()->setText(tmp);
    return tmp;
}
