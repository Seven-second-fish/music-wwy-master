#ifndef MUSICFORM_H
#define MUSICFORM_H

#include <QWidget>

namespace Ui {
class MusicForm;
}

class MusicForm : public QWidget
{
    Q_OBJECT

public:
    explicit MusicForm(QWidget *parent = nullptr);
    ~MusicForm();
    void setMusicName(const QString& musicName);
    void setMusicAuthor(QString musicAuther);
    void setMusicPicture(QString url);

private:
    Ui::MusicForm *ui;

    QTimer* scrollTimer = nullptr;
    QString originalText;  // 原始文本
    int offset = 0;        // 偏移量，用于控制滚动位置
    int ScrollTextWidth = 7;
private slots:
    void updateScrollingText();  // 更新滚动文本
};

#endif // MUSICFORM_H
