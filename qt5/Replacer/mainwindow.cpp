#include "mainwindow.h"

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

void MainWindow::menuExportPlain()
{
    qInfo() << "clicked 'export plain'";
}

void MainWindow::menuImportPlain()
{
    qInfo() << "'clicked 'import plain'";
}

void MainWindow::menuExportTagList()
{
    qInfo() << "clicked 'export tags'";
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
    // (Note that menuBar takes ownership of the new menu! -> No explicit deletion of menuMenu needed!)
    QMenu* menuMenu = ui->menuBar->addMenu(tr("&Menu"));
    QMenu* menuData = ui->menuBar->addMenu(tr("&Date"));
    QMenu* menuHelp = ui->menuBar->addMenu(tr("&Help"));

    // create "Exit" action
    QAction *exitAction = new QAction(tr("&Exit"), this);
    // add standard shortcut for closing
    exitAction->setShortcut(QKeySequence::Quit);
    // add status bar tooltip
    exitAction->setStatusTip(tr("close this application"));
    // connect this actions triggered SIGNAL to the MainWindow exit SLOT
    connect(exitAction, &QAction::triggered, this, &MainWindow::menuExit);

    QAction *saveAction = new QAction(tr("&Save"), this);
    saveAction->setShortcut(QKeySequence::Save);
    saveAction->setStatusTip(tr("save plain text and tag list"));
    connect(saveAction, &QAction::triggered, this, &MainWindow::menuSave);

    QAction *saveAsAction = new QAction(tr("Save &As"), this);
    saveAsAction->setShortcut(QKeySequence::SaveAs);
    saveAsAction->setStatusTip(tr("save plain text and tag list to …"));
    connect(saveAsAction, &QAction::triggered, this, &MainWindow::menuSaveAs);

    QAction *loadAction = new QAction(tr("&Load"), this);
    loadAction->setShortcut(QKeySequence::Open);
    loadAction->setStatusTip(tr("load plain text and tag list from file…"));
    connect(loadAction, &QAction::triggered, this, &MainWindow::menuLoad);

    QAction *newAction = new QAction(tr("&New"), this);
    newAction->setShortcut(QKeySequence::New);
    newAction->setStatusTip(tr("new project"));
    connect(newAction, &QAction::triggered, this, &MainWindow::menuNew);

    QAction* exportPlainAction = new QAction(tr("&Export Plain Text to File"), this);
    exportPlainAction->setStatusTip("write plain text to a file");
    connect(exportPlainAction, &QAction::triggered, this, &MainWindow::menuExportPlain);

    QAction* importPlainAction = new QAction(tr("&Import Plain Text from File"), this);
    importPlainAction->setStatusTip(tr("import plain text from a text file"));
    connect(importPlainAction, &QAction::triggered, this, &MainWindow::menuImportPlain);

    QAction* exportFinalAction = new QAction(tr("&Export Final Text to File"), this);
    exportFinalAction->setStatusTip(tr("write final text to file"));
    connect(exportFinalAction, &QAction::triggered, this, &MainWindow::menuExportFinal);

    QAction* importTagList = new QAction(tr("&Import Tag List to File"));
    QAction* importTagList = new QAction(tr("&Import Tag List to File"), this);
    importTagList->setStatusTip(tr("import tag list from a file"));
    connect(importTagList, &QAction::triggered, this, &MainWindow::menuImportTagList);


    QAction *aboutAction = new QAction(tr("&About"), this);
    aboutAction->setStatusTip(tr("show about dialog"));
    connect(aboutAction, &QAction::triggered, this, &MainWindow::menuAbout);

    // add actions to menus
    menuMenu->addAction(newAction);
    menuMenu->addAction(loadAction);
    menuMenu->addAction(saveAction);
    menuMenu->addAction(saveAsAction);
    menuMenu->addAction(exitAction);

    menuData->addAction(exportPlainAction);
    menuData->addAction(importPlainAction);
    menuData->addAction(exportFinalAction);
    menuData->addAction(importTagList);

    menuHelp->addAction(aboutAction);
}
