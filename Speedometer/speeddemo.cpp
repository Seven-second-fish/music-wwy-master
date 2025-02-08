#include "speeddemo.h"
#include <QPainter>
#include <QPen>
#include <QPolygon>
#include <QConicalGradient>
#include <QtMath>
#include <QDebug>
#include <QElapsedTimer>

#define SpeedometerTimer 2

Speeddemo::Speeddemo(QWidget *parent)
    : QWidget(parent), m_speed(0), m_maxSpeed(100)
{
    setMinimumSize(200, 200);
    SpeedometerTimerID = startTimer(SpeedometerTimer);
}

Speeddemo::~Speeddemo()
{
}

void Speeddemo::setSpeed(int speed)
{
    qDebug()<<__FUNCTION__<<__LINE__;
    m_speed = qBound(0, speed, m_maxSpeed);
    update();
}

void Speeddemo::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.fillRect(rect(), Qt::black);
    setAutoFillBackground(false);

    painter.fillRect(rect(), Qt::transparent);

    drawBackground(painter);
    drawLabels(painter);
}

void Speeddemo::resizeEvent(QResizeEvent *event)
{
    qDebug()<<__FUNCTION__<<__LINE__;
    QWidget::resizeEvent(event);
    m_labelsCached = false;
}

void Speeddemo::setPainterViewport(QPainter &painter, int side)
{
    painter.setViewport((width() - side) / 2, (height() - side) / 2, side, side);
    painter.setWindow(-100, -100, 200, 200);
}


void Speeddemo::drawBackground(QPainter &painter)
{
    painter.save();

    int side = qMin(width(), height());;
    setPainterViewport(painter, side);

    int outerRadius = 95;
    int innerRadius = 85;

    qreal startAngle = -50.0;
    qreal spanAngle = 280.0;

    qreal speedRatio = qBound(0.0, static_cast<double>(m_speed) / static_cast<double>(m_maxSpeed), 1.0);
    qreal filledAngle = spanAngle * speedRatio;

    int numSegments = 300;
    qreal anglePerSegment = spanAngle / numSegments;

    QPainterPath combinedPath;

    for (int i = 0; i < numSegments; ++i)
    {
        qreal currentAngle = startAngle + spanAngle - i * anglePerSegment - anglePerSegment;

        if (i * anglePerSegment >= filledAngle)
            break;

        qreal position = static_cast<qreal>(i) / numSegments;
        QColor color = QColor::fromHsvF((1.0 - position) * 0.4, 1.0, 1.0);

        QPainterPath segment;
        segment.moveTo(0, 0);
        segment.arcTo(-outerRadius, -outerRadius, 2 * outerRadius, 2 * outerRadius, currentAngle, -anglePerSegment);
        segment.arcTo(-innerRadius, -innerRadius, 2 * innerRadius, 2 * innerRadius, currentAngle - anglePerSegment, anglePerSegment);
        segment.closeSubpath();
        combinedPath.addPath(segment);

        painter.setBrush(color);
        painter.setPen(Qt::NoPen);
    }

    painter.drawPath(combinedPath);

    painter.restore();
}


void Speeddemo::drawLabels(QPainter &painter)
{
    int side = qMin(width(), height());
    if (!m_labelsCached || cachedSize != QSize(side, side))
    {
        m_labelsCache = QPixmap(width(), height());
        m_labelsCache.fill(Qt::transparent);
        cachedSize = QSize(side, side);

        QPainter cachePainter(&m_labelsCache);
        cachePainter.setRenderHint(QPainter::Antialiasing);

        setPainterViewport(cachePainter, side);

        cachePainter.setPen(Qt::white);
        cachePainter.setFont(QFont("Arial", 6, QFont::Bold));

        int numTicks = m_maxSpeed / 10 + 1;
        qreal startAngle = 130.0;
        qreal endAngle = 410.0;
        qreal angleIncrement = (endAngle - startAngle) / (numTicks - 1);

        for (int i = 0; i < numTicks; ++i)
        {
            qreal angle = startAngle + i * angleIncrement;
            qreal radians = qDegreesToRadians(angle);

            bool isLongTick = (i % 2 == 0);
            qreal xStart = (isLongTick ? 72 : 76) * qCos(radians);
            qreal yStart = (isLongTick ? 72 : 76) * qSin(radians);
            qreal xEnd = 80 * qCos(radians);
            qreal yEnd = 80 * qSin(radians);

            cachePainter.drawLine(QPointF(xStart, yStart), QPointF(xEnd, yEnd));
        }

        m_labelsCached = true;
    }

    painter.drawPixmap(0, 0, m_labelsCache);
}





void Speeddemo::timerEvent(QTimerEvent *e)
{
    static int i = 0;
    static bool status = false;
    int update = 1;

    if (e->timerId() == SpeedometerTimerID)
    {
        if (!status)
        {
            i += update;
            if (i >= m_maxSpeed)
            {
                i = m_maxSpeed;
                status = true;
            }
        }
        else
        {
            i -= update;
            if (i <= 0)
            {
                i = 0;
                status = false;
            }
        }

        setSpeed(i);
        qDebug() << "i=" << i;
    }
}

void Speeddemo::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);
    static bool pressstatus = false;
    if(SpeedometerTimerID != 0)
    {
        SpeedometerTimerID = 0;
        pressstatus = true;
    }else{
        pressstatus = false;
        SpeedometerTimerID = startTimer(SpeedometerTimer);
    }
}

void Speeddemo::mouseMoveEvent(QMouseEvent *event)
{
    QWidget::mouseMoveEvent(event);
}

void Speeddemo::mouseReleaseEvent(QMouseEvent *event)
{
    QWidget::mouseReleaseEvent(event);
}



