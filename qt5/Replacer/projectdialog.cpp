#include "projectdialog.h"

ProjectDialog::ProjectDialog(const QString &title, QWidget *parent):
    QDialog(parent),
    m_pProjectDialog(new Ui::ProjectDialog)
{
    m_pProjectDialog->setupUi(this);
    setWindowTitle(title);

    // check if a Ok button is defined
    // if not defined the okBtnEnable() will crush the application execution
    auto tmp = m_pProjectDialog->buttonBox->buttons();
    bool bOkBtnFound{false};
    foreach(auto btn, tmp)
    {
        int stdBtn = m_pProjectDialog->buttonBox->standardButton(btn);
        if (QDialogButtonBox::Ok == stdBtn)
        {
            bOkBtnFound = true;
            break;
        }
    }
    if (!bOkBtnFound)
    {
        // no Ok button defined: give error message to console
        qFatal("ERROR: No Ok button defined for the project dialog!");
    }
    // disable the ok button if needed
    okBtnDisableIfNeeded();
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
    m_projectDir = QDir(m_pProjectDialog->lineEdit_proDir->text()).absolutePath();
    m_cancelled = false;
}

// called on the change of the project-directory-lineEdit's text
void ProjectDialog::on_lineEdit_proDir_textChanged()
{
    // disable Ok button if needed
    okBtnDisableIfNeeded();
}

// called on the change of the project-name-lineEdit's text
void ProjectDialog::on_lineEdit_proName_textChanged()
{
    // disable Ok button if needed
    okBtnDisableIfNeeded();
}

// disables and enables the Ok button
// IMPORTANT: Make sure the button box has a Ok button!
void ProjectDialog::okBtnDisableIfNeeded()
{
    // true if one or both of the lineEdits are empty
    bool bEmpty =
            m_pProjectDialog->lineEdit_proName->text().isEmpty() ||
            m_pProjectDialog->lineEdit_proDir->text().isEmpty();

    // disable Ok button according to the lineEdits empty status
    m_pProjectDialog->buttonBox->button(QDialogButtonBox::Ok)->setDisabled(bEmpty);
}
