#ifndef MSGBOXHELPER_H
#define MSGBOXHELPER_H

#include <QMessageBox>
#include <QString>
#include <QWidget>

void infoMsgBox(const QString &info, const QString &info2, QWidget* parent);
void warnMsgBox(const QString &info, const QString &info2, QWidget* parent);
bool reallyAllNew(QWidget* parent, const QString& title, const QString &info);

#endif // MSGBOXHELPER_H
