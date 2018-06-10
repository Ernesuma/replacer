#ifndef PROJECT_H
#define PROJECT_H

#include <QDir>
#include <regex>

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
    void set(const QString& name, const QDir& path);

    const QString &getProjectName() const;
    const QDir& getProjectPath() const;

    static bool isValidName(const QString& name);
};

#endif // PROJECT_H
