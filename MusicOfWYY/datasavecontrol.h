#ifndef DATASAVECONTROL_H
#define DATASAVECONTROL_H

#include <QSettings>
#include <QString>
#include <QStringList>
#include <QDir>
#include <QFileInfoList>

class DataSaveControl {
public:
    enum FileType
    {
        ListItems,
        Settings,
        Another
    };

    void saveListItems(const QString &groupName, const QStringList &items, FileType fileType);
    QStringList loadListItems(const QString &groupName, FileType fileType);
    QStringList scanFilesInDirectory(const QString &directoryPath, const QStringList &filters = QStringList());

private:
    QString getFileName(FileType fileType) const;
};
#endif // DATASAVECONTROL_H
