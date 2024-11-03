#include "musicform.h"
#include "ui_musicform.h"
#include <QTimer>

MusicForm::MusicForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MusicForm)
{
    ui->setupUi(this);
}

MusicForm::~MusicForm()
{
    delete ui;
}

//void MusicForm::setMusicName(QString musicName)
//{
//    ui->labMName->setText(musicName);
//}

void MusicForm::setMusicName(const QString& musicName) {
    ui->labMName->setText(musicName);
    originalText = musicName;  // 保存原始文本
    offset = 0;  // 偏移量初始化

    if (scrollTimer == nullptr) {
        scrollTimer = new QTimer(this);
        connect(scrollTimer, &QTimer::timeout, this, &MusicForm::updateScrollingText);
    }
    scrollTimer->start(200);  // 每200毫秒更新一次
}

void MusicForm::setMusicAuthor(QString musicAuther)
{
    ui->labMuAuthor->setText(musicAuther);
}

void MusicForm::setMusicPicture(QString url)
{
    QString str = "QPushButton{border-image:url("+url+");}";
    ui->ptnGetMusic->setStyleSheet(str);
    ui->pushButton->setStyleSheet("QPushButton{border-image:url(./images/Messageform/like.png);}");
}

void MusicForm::updateScrollingText() {
    // 若文字宽度小于标签宽度，则无需滚动
    QFontMetrics fm(ui->labMName->font());
    int textWidth = fm.horizontalAdvance(originalText);
    if (textWidth <= ScrollTextWidth) {
        ui->labMName->setText(originalText);
        scrollTimer->stop();  // 停止定时器
        return;
    }

    // 根据偏移量创建滚动文本
    QString spacing = "             ";  // 设置间隔
    QString scrollingText = originalText.mid(offset) + spacing + originalText.left(offset);
    ui->labMName->setText(scrollingText);

    // 更新偏移量，实现滚动效果
    offset = (offset + 1) % (originalText.length() + spacing.length());
}

