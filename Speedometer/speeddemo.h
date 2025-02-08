#ifndef SPEEDDEMO_H
#define SPEEDDEMO_H

#include <QWidget>
#include <QTimerEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class Speedometer; }
QT_END_NAMESPACE

class Speeddemo : public QWidget
{
    Q_OBJECT

public:
    explicit Speeddemo(QWidget *parent = nullptr);
    ~Speeddemo();
    void setSpeed(int speed);  // 设置速度
    void setDialPosition(int x, int y, int size);  // 设置速度盘位置
    void initializeCache();
    void setPainterViewport(QPainter &painter, int side);

protected:
    void paintEvent(QPaintEvent *event) override;
    void timerEvent(QTimerEvent *e);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void resizeEvent(QResizeEvent *event);

private:
    Ui::Speedometer *ui;
    int m_speed;       // 当前速度
    const int m_maxSpeed; // 最大速度
    int SpeedometerTimerID;
    QPixmap m_labelsCache; // 用于缓存刻度线的绘制结果
    bool m_labelsCached = false; // 标志缓存是否已初始化
    QSize cachedSize;

    void drawBackground(QPainter &painter);
    void drawNeedle(QPainter &painter);
    void drawLabels(QPainter &painter);
};

#endif // SPEEDDEMO_H
