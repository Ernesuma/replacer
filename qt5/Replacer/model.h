#ifndef MODEL_H
#define MODEL_H

//#include <memory>
//#include "ui_mainwindow.h"

class Model
{
private:
    //std::unique_ptr<Ui::MainWindow> m_pUiHandle;
    QString m_plainText{""};

public:
    Model();
    ~Model();

    QString& SetPlainText(const QString& plainText);
    QString GetPlainText() const;
    QString GetFinalText() const;
    QString Plain2Clipboard() const;
    QString Final2Clipboard() const;
};

#endif // MODEL_H
