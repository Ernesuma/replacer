#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QtDebug>
#include <QString>
#include <QModelIndex>
//#include <QMap>
//#include <memory>

#include "ui_mainwindow.h"
#include "controller.h"

namespace Ui
{
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
    void on_pushButton_remove_tag_clicked();

    // slots for menu 'Menu'
    void menuNew();
    void menuLoad();
    void menuSave();
    void menuSaveAs();
    void menuExit();

    // slots for menu 'Help'
    void menuAbout();
private:
    // private methods
    void createMenus();

    // member
    Ui::MainWindow *ui;
    Controller m_controller{};
};

#endif // MAINWINDOW_H
