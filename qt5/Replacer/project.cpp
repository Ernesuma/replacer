#include "project.h"

// constructor
Project::Project():
    m_name(""),
    m_projectPath("")
{

}

// destructor
Project::~Project()
{

}

bool Project::isSet() const
{
    return !(getProjectName().isEmpty());
}

void Project::set(const QString &name, const QDir &path)
{
    m_name = name;
    m_projectPath = path;
    return;
}

QString Project::getProjectName() const
{
    return m_name;
}

bool Project::isValidName(const QString &name)
{
    std::regex expr(R"(^[a-zA-Z0-9_][a-zA-Z0-9_+-]*$)");
    if (std::regex_match(name.toStdString(), expr))
    {
        return true;
    }
    return false;
}
