#ifndef DIALOGNEW_H
#define DIALOGNEW_H

#include<ui_projectdialog.h>
#include<QtDebug>
#include<QWidget>
#include<QFileDialog>
#include<QDir>
#include<QPushButton>


class ProjectDialog : public QDialog
{
    Q_OBJECT

    // member
    Ui::ProjectDialog* m_pProjectDialog;
    QString m_projectName{QString("")};
    QDir m_projectDir{QDir("")};
    bool m_cancelled{true};

public:
    ProjectDialog(const QString &title, QWidget *parent);
    ~ProjectDialog();

    //void setDialogReturns(String& name );
    bool wasCancelled(){return m_cancelled;};
    QString& getProjectName(){return m_projectName;};
    QDir& getProjectDir(){return m_projectDir;};

private slots:
    void on_toolButton_clicked();
    void on_buttonBox_accepted();
    void on_lineEdit_proDir_textChanged();
    void on_lineEdit_proName_textChanged();

private:
    void okBtnDisableIfNeeded();
};

#endif // DIALOGNEW_H
