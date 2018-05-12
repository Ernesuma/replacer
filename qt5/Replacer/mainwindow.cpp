#include "mainwindow.h"

void infoMsgBox(const QString &info, const QString &info2=QString())
{
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText(info);
        msgBox.setInformativeText(info2);
        msgBox.exec();
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(m_controller.GetTagMapModelRaw());
    ui->tableView->show();

    // create the menus of the menu bar
    createMenus();

    // set the status bar tooltips
    ui->pushButton_replace->setStatusTip(tr("replace all {…} tags from the plain text with corresponding values from tag list and print to final text view"));
    ui->pushButton_c2c_plain->setStatusTip(tr("copy plain text to clipboard"));
    ui->pushButton_c2c_final->setStatusTip(tr("copy final text to clipboard"));
    ui->pushButton_remove_tag->setStatusTip(tr("remove all selected tags from the tag list"));
    ui->pushButton_add_2_tag_list->setStatusTip(tr("add a new tag to the tag list"));
    ui->tableView->setStatusTip(tr("click on already defined tags or values to edit them"));
    ui->lineEdit_newTag->setStatusTip(tr("enter new tag"));
    ui->lineEdit_newValue->setStatusTip(tr("enter new tag value"));
    ui->textEdit_plain->setStatusTip(tr("enter your text here; mark tags to be replaced with curly braces like: {myTag}"));
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
    QString finalText{"Error while replacing"};
    if (m_controller.replace())
    {
        finalText = m_controller.GetFinalText();
    }
    else
    {
        qWarning() << "WARNING: could not replace tags";
    }
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
        if (!m_controller.RemoveTags(rows))
        {
            qWarning() << "WARNING: could not remove tags";
        }
    }
    ui->tableView->clearSelection();
}

void MainWindow::menuNew()
{
    qInfo() << "clicked 'New'";
}

void MainWindow::menuLoad()
{
    qInfo() << "clicked 'Load'";
}

void MainWindow::menuSave()
{
    qInfo() << "clicked 'Save'";
}

void MainWindow::menuSaveAs()
{
    qInfo() << "clicked 'Save As'";
}

void MainWindow::menuExit()
{
    this->close();
}

void MainWindow::m_menuMenuAboutToShow()
{
    qDebug() << "m_menuMenuAboutToShow()";
}

void MainWindow::m_menuDataAboutToShow()
{
    qDebug() << "m_menuDataAboutToShow()";

    // disable export actions in the menu according to the availbility of the contents to export
    m_actionExportPlain->setDisabled(m_controller.GetPlainText().isEmpty());
    m_actionExportFinal->setDisabled(m_controller.GetFinalText().isEmpty());
    m_actionExportTagList->setDisabled(m_controller.isTagMapEmpty());
}

void MainWindow::m_menuHelpAboutToShow()
{
    qDebug() << "m_menuHelpAboutToShow()";
}

void MainWindow::menuExportPlain()
{
    qInfo() << "clicked 'export plain'";
    QString tmpStr = QFileDialog::getSaveFileName(this, tr("Choose file to export  plain text to"));
    if (!tmpStr.isNull())
    {
        QDir exportFilePath{tmpStr};
        qInfo() << exportFilePath.absolutePath();
        m_controller.exportPlain(exportFilePath);

        infoMsgBox("Exported plain text to:", exportFilePath.absolutePath());
    }
}

void MainWindow::menuImportPlain()
{
    qInfo() << "'clicked 'import plain'";
    QString tmpStr{QFileDialog::getOpenFileName(this, tr("Choose file to import plain text from"))};
    if (!tmpStr.isNull())
    {
        QDir importFilePath{tmpStr};
        qInfo() << importFilePath.absolutePath();
        m_controller.importPlain(importFilePath);
        ui->textEdit_plain->setText(m_controller.GetPlainText());

        infoMsgBox("Imported plain text from file:", importFilePath.absolutePath());
    }
}

void MainWindow::menuExportFinal()
{
    qInfo() << "clicked 'export final'";
    QString tmpStr = QFileDialog::getSaveFileName(this, tr("Choose file to export final text to"));
    if (!tmpStr.isNull())
    {
        QDir exportFilePath{tmpStr};
        qInfo() << exportFilePath.absolutePath();
        m_controller.exportFinal(exportFilePath);

        infoMsgBox("Exported final text to file:", exportFilePath.absolutePath());
    }
}

void MainWindow::menuExportTagList()
{
    qInfo() << "clicked 'export tags'";
    QString tmpStr = QFileDialog::getSaveFileName(this, tr("Choose file to export tag list to"));
    if (!tmpStr.isNull())
    {
        QDir exportFilePath{tmpStr};
        qInfo() << exportFilePath.absolutePath();
        m_controller.exportTagList(exportFilePath);

        infoMsgBox("Exported tag list to file:", exportFilePath.absolutePath());
    }
}

void MainWindow::menuImportTagList()
{
    qInfo() << "clicked 'import tags'";
}

void MainWindow::menuAbout()
{
    qInfo() << "clicked 'About'";
}

void MainWindow::createMenus()
{
    // add menu "Menu" to the menuBar
    // use tr(…) function to mark charecter acting as <Alt-…> keybinding
    // (Note that menuBar takes ownership of the new menu! -> No explicit deletion of m_menuMenu needed!)
    m_menuMenu = ui->menuBar->addMenu(tr("&Menu"));
    m_menuData = ui->menuBar->addMenu(tr("&Data"));
    m_menuHelp = ui->menuBar->addMenu(tr("&Help"));

    // create "Exit" action
    QAction *exitAction = new QAction(tr("&Exit"), this);
    // add standard shortcut for closing
    exitAction->setShortcut(QKeySequence::Quit);
    // add status bar tooltip
    exitAction->setStatusTip(tr("close this application"));
    // connect this actions triggered SIGNAL to the MainWindow exit SLOT
    connect(exitAction, &QAction::triggered, this, &MainWindow::menuExit);

    QAction *newAction = new QAction(tr("&New"), this);
    newAction->setShortcut(QKeySequence::New);
    newAction->setStatusTip(tr("create new project"));
    connect(newAction, &QAction::triggered, this, &MainWindow::menuNew);

    QAction *saveAction = new QAction(tr("&Save"), this);
    saveAction->setShortcut(QKeySequence::Save);
    saveAction->setStatusTip(tr("save project"));
    connect(saveAction, &QAction::triggered, this, &MainWindow::menuSave);

    QAction *saveAsAction = new QAction(tr("Save &As"), this);
    saveAsAction->setShortcut(QKeySequence::SaveAs);
    saveAsAction->setStatusTip(tr("save project as …"));
    connect(saveAsAction, &QAction::triggered, this, &MainWindow::menuSaveAs);

    QAction *loadAction = new QAction(tr("&Load"), this);
    loadAction->setShortcut(QKeySequence::Open);
    loadAction->setStatusTip(tr("load project"));
    connect(loadAction, &QAction::triggered, this, &MainWindow::menuLoad);

    QAction* importPlainAction = new QAction(tr("&Import Plain Text from File"), this);
    importPlainAction->setStatusTip(tr("import plain text from a text file"));
    connect(importPlainAction, &QAction::triggered, this, &MainWindow::menuImportPlain);

    QAction* importTagList = new QAction(tr("&Import Tag List from File"), this);
    importTagList->setStatusTip(tr("import tag list from a file"));
    connect(importTagList, &QAction::triggered, this, &MainWindow::menuImportTagList);

    m_actionExportPlain = new QAction(tr("&Export Plain Text to File"), this);
    m_actionExportPlain->setStatusTip("write plain text to a file");
    connect(m_actionExportPlain, &QAction::triggered, this, &MainWindow::menuExportPlain);

    m_actionExportFinal = new QAction(tr("&Export Final Text to File"), this);
    m_actionExportFinal->setStatusTip(tr("write final text to file"));
    connect(m_actionExportFinal, &QAction::triggered, this, &MainWindow::menuExportFinal);

    m_actionExportTagList = new QAction(tr("&Export Tag List to File"), this);
    m_actionExportTagList->setStatusTip("write the tag list to a file");
    connect(m_actionExportTagList, &QAction::triggered, this, &MainWindow::menuExportTagList);

    QAction *aboutAction = new QAction(tr("&About"), this);
    aboutAction->setStatusTip(tr("show about dialog"));
    connect(aboutAction, &QAction::triggered, this, &MainWindow::menuAbout);

    // add actions to menus
    // the QMenu::addAction takes ownership of the returned QAction
    m_menuMenu->addAction(newAction);
    m_menuMenu->addAction(loadAction);
    m_menuMenu->addAction(saveAction);
    m_menuMenu->addAction(saveAsAction);
    m_menuMenu->addSeparator();
    m_menuMenu->addAction(exitAction);

    m_menuData->addAction(importPlainAction);
    m_menuData->addAction(importTagList);
    m_menuData->addSeparator();
    m_menuData->addAction(m_actionExportPlain);
    m_menuData->addAction(m_actionExportFinal);
    m_menuData->addAction(m_actionExportTagList);

    m_menuHelp->addAction(aboutAction);

    // connect menus aboutToShow signals to MainWindows slots to handle this
    connect(m_menuMenu, &QMenu::aboutToShow, this, &MainWindow::m_menuMenuAboutToShow);
    connect(m_menuData, &QMenu::aboutToShow, this, &MainWindow::m_menuDataAboutToShow);
    connect(m_menuHelp, &QMenu::aboutToShow, this, &MainWindow::m_menuHelpAboutToShow);
}
