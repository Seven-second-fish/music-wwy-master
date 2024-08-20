#ifndef DATASAVECONTROL_H
#define DATASAVECONTROL_H

#include <QSettings>
#include <QString>
#include <QStringList>

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

private:
    QString getFileName(FileType fileType) const;
};
#endif // DATASAVECONTROL_H
