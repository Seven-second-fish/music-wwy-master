#ifndef SPEEDOMETER_H
#define SPEEDOMETER_H

#include <QWidget>
#include <QTimerEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class Speedometer; }
QT_END_NAMESPACE

class Speedometer : public QWidget
{
    Q_OBJECT

public:
    explicit Speedometer(QWidget *parent = nullptr);
    ~Speedometer();
    void setSpeed(int speed);
    void setPowerValue(int power);
    void setDialPosition(int x, int y, int size);
    void initializeCache();
    void setPainterViewport(QPainter &painter, int side);
    void drawTicks(QPainter &painter, int numTicks, qreal startAngle, qreal endAngle, QColor color);
    void drawArc(QPainter &painter, int radius, qreal startAngle, qreal spanAngle, double width, QColor color);
    void drawAngle(QPainter &painter, qreal value, qreal maxValue, int innerRadius, int outerRadius,
                   qreal startAngle, qreal spanAngle, int counter);
    void setAngleImg();
    void drawAngleImg(QPainter &painter, qreal value, qreal maxValue,int innerRadius, int outerRadius,
                      qreal startAngle, qreal spanAngle,int counter);
    void updateArcCache(int outerRadius, int innerRadius, int counter, qreal startAngle, qreal spanAngle);


protected:
    void paintEvent(QPaintEvent *event) override;
    void timerEvent(QTimerEvent *e);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void resizeEvent(QResizeEvent *event);

private:
    int m_speed;
    int m_powervalue;
    const int m_maxSpeed;
    const int m_maxpowervalue;
    int SpeedometerTimerID;
    QPixmap m_labelsCache;
    bool m_labelsCached = false;
    QSize cachedSize;
    bool m_speedChanged;
    bool m_powervalueChanged;
    QVector<QPixmap> spimages;
    QVector<QPixmap> baimages;
    QPixmap m_arcCacheSpeed;
    QPixmap m_arcCachePower;
    bool m_speedCacheDirty = true;
    bool m_powerCacheDirty = true;

    void drawBackground(QPainter &painter);
    void drawNeedle(QPainter &painter);
    void drawLabels(QPainter &painter);
};
#endif // SPEEDOMETER_H
