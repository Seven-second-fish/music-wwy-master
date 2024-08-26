#include "datasavecontrol.h"

QString DataSaveControl::getFileName(FileType fileType) const {
    switch (fileType) {
        case ListItems: return "list_items.ini";
        case Settings: return "settings.ini";
        case Another: return "another_file.ini";
        default: return "list_items.ini";  // Default file name
    }
}

void DataSaveControl::saveListItems(const QString &groupName, const QStringList &items, FileType fileType) {
    QString fileName = getFileName(fileType);
    QSettings settings(fileName, QSettings::IniFormat);

    settings.beginGroup(groupName);
    for (int i = 0; i < items.size(); ++i) {
        settings.setValue(QString("Item%1").arg(i + 1), items[i]);
    }
    settings.endGroup();
}

QStringList DataSaveControl::loadListItems(const QString &groupName, FileType fileType) {
    QString fileName = getFileName(fileType);
    QSettings settings(fileName, QSettings::IniFormat);

    settings.beginGroup(groupName);
    QStringList items;
    QStringList keys = settings.childKeys();
    for (const QString &key : keys) {
        items.append(settings.value(key).toString());
    }
    settings.endGroup();

    return items;
}

QStringList DataSaveControl::scanFilesInDirectory(const QString &directoryPath, const QStringList &filters) {
    QDir dir(directoryPath);
    QStringList fileList;

    // 如果提供了过滤器，则应用过滤器
    if (!filters.isEmpty()) {
        dir.setNameFilters(filters);
    }

    // 获取目录中的所有文件（包括符合过滤条件的文件）
    QFileInfoList files = dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot);

    // 将文件名或文件路径添加到 QStringList 中
    for (const QFileInfo &fileInfo : files) {
        fileList << fileInfo.fileName(); // 仅文件名
        // fileList << fileInfo.absoluteFilePath(); // 完整路径（如果需要）
    }

    return fileList;
}

