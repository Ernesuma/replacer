#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(m_controller.GetTagMapModelRaw());
    ui->tableView->show();
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
    qInfo() << "add tag";
    //m_pTagMapModel.get()->insertRow(m_pTagMapModel.get()->rowCount());
}

void MainWindow::on_pushButton_remove_tag_clicked()
{
    qInfo() << "clicked to remove selected tag";
    QItemSelectionModel* pSelect{ui->tableView->selectionModel()};
    QModelIndexList rows = pSelect->selectedRows();
    m_controller.RemoveTags(rows);
}
