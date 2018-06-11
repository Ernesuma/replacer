
#include "msgboxhelper.h"

void infoMsgBox(const QString &info, const QString &info2=QString(), QWidget* parent=nullptr)
{
    QMessageBox msgBox(parent);
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setText(info);
    msgBox.setInformativeText(info2);
    msgBox.exec();
}

void warnMsgBox(const QString &info, const QString &info2, QWidget* parent)
{
    QMessageBox mBox(parent);
    mBox.setIcon(QMessageBox::Warning);
    mBox.setText(info);
    mBox.setInformativeText(info2);
    mBox.exec();
}

bool reallyAllNew(QWidget* parent, const QString& title, const QString &info)
{
    int ret = QMessageBox::warning(parent, title, info,
                                 QMessageBox::Cancel | QMessageBox::Ok,
                                 QMessageBox::Cancel);
    if (QMessageBox::Ok == ret)
        return true;
    return false;
}
