#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtDebug>
#include <QString>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_controller(),
    m_list("one"),
    m_pModel(new StringListModel(m_list))
{
    ui->setupUi(this);

    ui->listView->setModel(m_pModel.get());
    ui->listView->show();

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
    m_pModel.get()->insertRow(0);
}
