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
        m_projectDir = saveFilePath.absolutePath();
        //qInfo() << m_projectDir << " " << m_projectDir.path();
        m_pDialogNew->lineEdit_2->setText(m_projectDir.path());
    }
}

void DialogNew::on_buttonBox_accepted()
{
    //TODO: do some checks here
}
