#ifndef DIALOGNEW_H
#define DIALOGNEW_H

#include<ui_dialognew.h>
#include<QtDebug>
#include<QWidget>
#include<QFileDialog>
#include<QDir>


class DialogNew : public QDialog
{
    Q_OBJECT

    // member
    Ui::DialogNew* m_pDialogNew;
    QString m_projectName{QString("")};
    QDir m_projectDir{QDir("")};

public:
    DialogNew(QWidget *parent);
    ~DialogNew();

    //void setDialogReturns(String& name );

private slots:
    void on_toolButton_clicked();

    void on_buttonBox_accepted();
};

#endif // DIALOGNEW_H
