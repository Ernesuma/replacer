#include "dialognew.h"

DialogNew::DialogNew(QWidget *parent):
    QDialog(parent),
    m_pDialogNew(new Ui::DialogNew)
{
    m_pDialogNew->setupUi(this);
}

DialogNew::~DialogNew()
{
    delete m_pDialogNew;
}

void DialogNew::on_toolButton_clicked()
{
    QString tmpStr = QFileDialog::getExistingDirectory(this, tr("Choose directory to save this project to"));
    if (!tmpStr.isNull())
    {
        QDir saveFilePath{tmpStr};
        QString proDir = saveFilePath.absolutePath();
        //qInfo() << m_projectDir << " " << m_projectDir.path();
        m_pDialogNew->lineEdit_proDir->setText(proDir);
    }
}

void DialogNew::on_buttonBox_accepted()
{
    m_projectName = m_pDialogNew->lineEdit_proName->text();
    m_projectDir = QDir(m_pDialogNew->lineEdit_proDir->text());
    m_cancelled = false;
}
