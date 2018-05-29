#ifndef PROJECT_H
#define PROJECT_H

#include <QDir>

class Project
{
private:
    // member
    QString m_name{""};
    QDir m_projectPath{""};

public:
    Project();
    ~Project();

    bool isSet() const;

    QString getProjectName() const;
};

#endif // PROJECT_H
