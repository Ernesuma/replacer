
#include"pathhelper.h"


QDir concatinatePaths(const QDir &path1, const QDir &path2)
{
    QDir returnPath{path1.path() + QDir::separator() + path2.path()};
    qInfo() << "retPath: " << returnPath.path();
    return returnPath;
}

QString appendSuffix(const QString &file, const QString &suffix)
{
    const QString suffixSeperator{'.'};
    QString returnString{file};
    if (0 != suffix.length())
    {
        if (suffixSeperator == suffix[0])
        {
            returnString.append(suffix);
        }
        else
        {
            returnString.append(suffixSeperator + suffix);
        }
    }
    return returnString;
}
