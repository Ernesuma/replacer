#ifndef PATHHELPER_H
#define PATHHELPER_H

#include<QDir>
#include<QString>
#include<QDebug>

QDir concatinatePaths(const QDir& path1, const QDir& path2);
QString appendSuffix(const QString& file, const QString& suffix);

#endif // PATHHELPER_H
