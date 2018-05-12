#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QtDebug>
#include <QString>
#include <QModelIndex>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>

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

    // slots for Menu 'Date'
    void menuExportPlain();
    void menuImportPlain();
    void menuExportFinal();
    void menuExportTagList();
    void menuImportTagList();

    // slots for menu 'Help'
    void menuAbout();

    // slots to execute right before showing menus
    void m_menuMenuAboutToShow();
    void m_menuDataAboutToShow();
    void m_menuHelpAboutToShow();

private:
    // private methods
    void createMenus();

    // member
    Ui::MainWindow *ui;
    Controller m_controller{};

    QMenu *m_menuMenu{nullptr};
    QMenu *m_menuData{nullptr};
    QMenu *m_menuHelp{nullptr};

    QAction *m_actionExportPlain{nullptr};
    QAction *m_actionExportFinal{nullptr};
    QAction *m_actionExportTagList{nullptr};
};

#endif // MAINWINDOW_H
