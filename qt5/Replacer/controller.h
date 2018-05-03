#ifndef CONTROLLER_H
#define CONTROLLER_H

//#include <memory>
//#include "ui_mainwindow.h"

class Controller
{
private:
    //std::unique_ptr<Ui::MainWindow> m_pUiHandle;
    QString m_plainText{""};

public:
    Controller();
    ~Controller();

    QString& SetPlainText(const QString& plainText);
    QString GetPlainText() const;
    QString GetFinalText() const;
    QString Plain2Clipboard() const;
    QString Final2Clipboard() const;
};

#endif // CONTROLLER_H
