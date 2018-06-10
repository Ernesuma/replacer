#include "projectdialog.h"

ProjectDialog::ProjectDialog(const QString &title, QWidget *parent):
    QDialog(parent),
    m_pProjectDialog(new Ui::ProjectDialog)
{
    m_pProjectDialog->setupUi(this);
    setWindowTitle(title);
}

ProjectDialog::~ProjectDialog()
{
    delete m_pProjectDialog;
}

void ProjectDialog::on_toolButton_clicked()
{
    QString tmpStr = QFileDialog::getExistingDirectory(this, tr("Choose directory to save this project to"));
    if (!tmpStr.isNull())
    {
        QDir saveFilePath{tmpStr};
        QString proDir = saveFilePath.absolutePath();
        //qInfo() << m_projectDir << " " << m_projectDir.path();
        m_pProjectDialog->lineEdit_proDir->setText(proDir);
    }
}

void ProjectDialog::on_buttonBox_accepted()
{
    m_projectName = m_pProjectDialog->lineEdit_proName->text();
    m_projectDir = QDir(m_pProjectDialog->lineEdit_proDir->text());
    m_cancelled = false;
}
