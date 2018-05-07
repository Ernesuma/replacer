#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(m_controller.GetTagMapModelRaw());
    ui->tableView->show();

    // set the status bar tooltips
    ui->pushButton_replace->setStatusTip(tr("replace all {…} tags from the plain text with corresponding values from tag list and print to final text view"));
    ui->pushButton_c2c_plain->setStatusTip(tr("copy plain text to clipboard"));
    ui->pushButton_c2c_final->setStatusTip(tr("copy final text to clipboard"));
    ui->pushButton_remove_tag->setStatusTip(tr("remove all selected tags from the tag list"));
    ui->pushButton_add_2_tag_list->setStatusTip(tr("add a new tag to the tag list"));
    ui->tableView->setStatusTip(tr("click on already defined tags or values to edit them"));
    ui->lineEdit_newTag->setStatusTip(tr("enter new tag"));
    ui->lineEdit_newValue->setStatusTip(tr("enter new tag value"));
    ui->textEdit_plain->setStatusTip(tr("enter your text here; mark tags to be replaced with {tag}"));
    ui->textEdit_final->setStatusTip(tr("here appears the final text after you hit button \"Replace\""));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_c2c_plain_clicked()
{
    //qInfo() << "copy 2 clipboard - plain";
    m_controller.Plain2Clipboard();
}

void MainWindow::on_textEdit_plain_textChanged()
{
    //qInfo() << ui->textEdit_plain->toPlainText();
    m_controller.SetPlainText(ui->textEdit_plain->toPlainText());
    //qInfo() << m_model.GetPlainText();
}

void MainWindow::on_pushButton_c2c_final_clicked()
{
    m_controller.Final2Clipboard();
}

void MainWindow::on_pushButton_replace_clicked()
{
    QString finalText{m_controller.GetFinalText()};
    ui->textEdit_final->setPlainText(finalText);
}

void MainWindow::on_pushButton_add_2_tag_list_clicked()
{
    qDebug() << "DEBUG: on_pushButton_add_2_tag_list_clicked()";

    // read values to add to tag list from the lineEdits
    auto key = ui->lineEdit_newTag->text();
    auto value = ui->lineEdit_newValue->text();

    // call the controller to add new entry to tag map model
    m_controller.GetTagMapModelRaw()->insert(key, value);

    // set up GUI to comfortably add another tag entry
    ui->lineEdit_newValue->clear();
    ui->lineEdit_newTag->clear();
    ui->lineEdit_newTag->setFocus();
}

void MainWindow::on_pushButton_remove_tag_clicked()
{
    qDebug() << "DEBUG: on_pushButton_remove_tag_clicked(): clicked to remove selected tag(s)";
    QItemSelectionModel* pSelect{ui->tableView->selectionModel()};
    QModelIndexList rows = pSelect->selectedRows();
    //qDebug() << "DEBUG: on_pushButton_remove_tag_clicked(): selection: " << rows;
    if (!rows.isEmpty())
    {
        m_controller.RemoveTags(rows);
    }
    ui->tableView->clearSelection();
}
