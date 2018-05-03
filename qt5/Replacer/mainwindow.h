#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "controller.h"
#include "stringlistmodel.h"

#include <memory>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_textEdit_plain_textChanged();

    void on_pushButton_c2c_plain_clicked();
    void on_pushButton_c2c_final_clicked();
    void on_pushButton_replace_clicked();

    void on_pushButton_add_2_tag_list_clicked();

private:
    Ui::MainWindow *ui;
    Controller m_controller;

    QStringList m_list;
    std::unique_ptr<QAbstractListModel> m_pModel;
};

#endif // MAINWINDOW_H
