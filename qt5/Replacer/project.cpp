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

QString Project::getProjectName() const
{
    return m_name;
}
