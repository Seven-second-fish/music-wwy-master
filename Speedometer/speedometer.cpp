#include "speedometer.h"
#include <QPainter>
#include <QPen>
#include <QPolygon>
#include <QConicalGradient>
#include <QtMath>
#include <QDebug>
#include <QElapsedTimer>
#include <QDir>

#define SpeedometerTimer 200

Speedometer::Speedometer(QWidget *parent)
    : QWidget(parent), m_speed(0), m_maxSpeed(100), m_maxpowervalue(40),
      m_speedChanged(false),m_powervalueChanged(false)
{
//    setAngleImg();
    setMinimumSize(200, 200);
    SpeedometerTimerID = startTimer(SpeedometerTimer);
//    initializeCache();

//    m_speed = m_maxSpeed;

//    m_powervalue = m_maxpowervalue;
//    qDebug() << "Qt Version:" << QT_VERSION_STR;
//    qDebug() << "Graphics backend: " << QGuiApplication::platformName();
}

Speedometer::~Speedometer()
{
}

void Speedometer::setAngleImg()
{
    QString path = ":/image/angle/";
    QDir dir(path);

    QStringList filters;
    filters << "sp*.png" << "ba*.png";  // 只读取相关文件
    QStringList fileList = dir.entryList(filters, QDir::Files, QDir::Name);

    for (const QString &file : fileList) {
        QString imagePath = path + file;
        QPixmap pixmap(imagePath);

        if (pixmap.isNull()) {
            qDebug() << "Failed to load image:" << imagePath;
            continue;
        }

        if (file.startsWith("sp")) {
            spimages.append(pixmap);
        } else if (file.startsWith("ba")) {
            baimages.append(pixmap);
        }
    }

    qDebug() << "Loaded" << spimages.size() << "speed images and"
             << baimages.size() << "power images.";
}

void Speedometer::setSpeed(int speed)
{
    speed = qBound(0, speed, m_maxSpeed);
    if (speed != m_speed)
    {
        m_speed = speed;
        m_speedChanged = true;
    }
    update();
}

void Speedometer::setPowerValue(int powervalue)
{
    powervalue = qBound(0, powervalue, m_maxpowervalue);
    if (powervalue != m_powervalue)
    {
        m_powervalue = powervalue;
        m_powervalueChanged = true;
    }
    update();
}


void Speedometer::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

//    painter.fillRect(rect(), Qt::black);
    setAutoFillBackground(false);

    painter.fillRect(rect(), Qt::transparent);

    drawBackground(painter);
    drawLabels(painter);
}

void Speedometer::resizeEvent(QResizeEvent *event)
{
    qDebug()<<__FUNCTION__<<__LINE__;
    QWidget::resizeEvent(event);
    m_labelsCached = false;
}

void Speedometer::initializeCache()
{
    QImage tempImage(10, 10, QImage::Format_ARGB32);
    tempImage.fill(Qt::transparent);
    m_arcCacheSpeed = QPixmap::fromImage(tempImage);
    m_arcCachePower = QPixmap::fromImage(tempImage);
}

void Speedometer::setPainterViewport(QPainter &painter, int side)
{
    painter.setViewport((width() - side) / 2, (height() - side) / 2, side, side);
    painter.setWindow(-100, -100, 200, 200);
}

void Speedometer::drawBackground(QPainter &painter)
{
    painter.save();

    int side = qMin(width(), height());
    setPainterViewport(painter, side);

    //draw a line
    drawArc(painter, 95, -50.5, 280.0, 1.5, QColor(255, 100, 0));

    painter.setOpacity(1.0);

    // for speed
    if (m_speedChanged) {
//        drawAngle(painter, m_speed, m_maxSpeed, 90, 100, -130, -170, 1);
//        drawAngleImg(painter, m_speed, m_maxSpeed, 85, 95, 60.0, 170.0, 1);
        drawAngle2(painter, m_speed, m_maxSpeed, 90, 100, 60.0, 170.0, 1);
//        drawAngleImg2(painter,m_speed, m_maxSpeed,1);
        m_speedChanged = false;
    }

    // for powervalue
    if (m_powervalueChanged) {
        drawAngle(painter, m_powervalue, m_maxpowervalue, 90, 100, -51, 88, 2);
//        drawAngleImg(painter, m_powervalue, m_maxpowervalue, 90, 100, -50, 88, 2);
//        drawAngle2(painter, m_powervalue, m_maxpowervalue, 90, 100, -51, 88, 2);
//        drawAngleImg2(painter,m_powervalue, m_maxpowervalue,2);
        m_powervalueChanged = false;
    }


    painter.restore();
}

void Speedometer::updateArcCache(int outerRadius, int innerRadius, int counter, qreal startAngle, qreal spanAngle)
{
//    qDebug()<<__FUNCTION__<<__LINE__;
    if (counter == 1 && !m_speedCacheDirty) return;
    if (counter == 2 && !m_powerCacheDirty) return;

    int numSegments = 10000;
    int size = qMin(width(), height());

    QPixmap &arcCache = (counter == 1) ? m_arcCacheSpeed : m_arcCachePower;
    arcCache = QPixmap(size, size);
//    arcCache.fill(Qt::transparent);

    QPainter painter(&arcCache);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.save();

    painter.translate(size / 2, size / 2);
    painter.setPen(Qt::NoPen);

    qreal anglePerSegment = spanAngle / numSegments;

    QPainterPath combinedPath;

    QConicalGradient gradient(0, 0, startAngle);
    qreal currentAngle = 0;
    for (int i = 0; i < numSegments; ++i)
    {
//        qreal currentAngle = startAngle + i * anglePerSegment;
        if(counter == 1){  //left
            currentAngle = startAngle + spanAngle - (i + 1) * anglePerSegment;
        }else if(counter == 2){  //right
            currentAngle = startAngle + i * anglePerSegment;
        }

        qreal position = static_cast<qreal>(i) / numSegments;
        QColor color;
        if (counter == 1) {  // left
            color = QColor::fromHsvF(0.0 + position * 0.083, 1.0, 1.0);
        } else if (counter == 2) {  // right
            color = QColor::fromHsvF(0.33, 1.0, 0.5 + position * 0.5);
        }
        gradient.setColorAt(position, color);

        QPainterPath segment;
        segment.moveTo(0, 0);
        segment.arcTo(-outerRadius, -outerRadius, 2 * outerRadius, 2 * outerRadius, currentAngle, -anglePerSegment);
        segment.arcTo(-innerRadius, -innerRadius, 2 * innerRadius, 2 * innerRadius, currentAngle - anglePerSegment, anglePerSegment);
        segment.closeSubpath();

        combinedPath.addPath(segment);

        painter.setBrush(gradient);
        painter.drawPath(segment);
    }

    painter.drawPath(combinedPath);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter.setRenderHint(QPainter::HighQualityAntialiasing, true);


    if (counter == 1) m_speedCacheDirty = false;
    if (counter == 2) m_powerCacheDirty = false;
    painter.restore();
    qDebug()<<__FUNCTION__<<__LINE__;
}

void Speedometer::drawAngle(QPainter &painter, qreal value, qreal maxValue,
                            int innerRadius, int outerRadius, qreal startAngle, qreal spanAngle,
                            int counter)
{
    updateArcCache(outerRadius, innerRadius, counter, startAngle, spanAngle);

    qreal ratio = qBound(qreal(0.0), value / maxValue, qreal(1.0));
    qreal filledAngle = spanAngle * ratio;

    if (filledAngle == spanAngle) {
        qDebug()<<__FUNCTION__<<__LINE__;
        filledAngle -= 0.01;
    }

    QPainterPath clipPath;

    QRectF outerRect(-outerRadius, -outerRadius, 2 * outerRadius, 2 * outerRadius);
    clipPath.arcTo(outerRect, startAngle, filledAngle);

    QRectF innerRect(-innerRadius, -innerRadius, 2 * innerRadius, 2 * innerRadius);
    clipPath.arcTo(innerRect, startAngle + filledAngle, -filledAngle);

    painter.save();
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter.setRenderHint(QPainter::HighQualityAntialiasing, true);

    painter.setClipPath(clipPath);
//    painter.setClipRegion(clipPath.toFillPolygon().toPolygon());

    QPixmap *arcCache = nullptr;

    if (counter == 1)
        arcCache = &m_arcCacheSpeed;
    else if (counter == 2)
        arcCache = &m_arcCachePower;

    if (arcCache && !arcCache->isNull()) {
        int size = arcCache->width();

        if (size > 0) {
//            painter.drawPixmap(-size / 2, -size / 2, *arcCache);

            QImage cacheImage = arcCache->toImage().convertToFormat(QImage::Format_ARGB32);
            QPixmap smoothPixmap = QPixmap::fromImage(cacheImage);

            painter.drawPixmap(-size / 2, -size / 2, smoothPixmap);

            painter.setCompositionMode(QPainter::CompositionMode_DestinationIn);
            painter.fillPath(clipPath, QColor(0, 0, 0, 255));
        }
    }

    painter.restore();
}

void Speedometer::drawAngleImg(QPainter &painter, qreal value, qreal maxValue,
                               int innerRadius, int outerRadius, qreal startAngle, qreal spanAngle, int counter)
{
    int numSegments = 0;
    const QVector<QPixmap> *imageList = nullptr;

    switch (counter) {
        case 1:
            numSegments = 8;
            imageList = &spimages;
            break;
        case 2:
            numSegments = 4;
            imageList = &baimages;
            break;
        default:
            qWarning() << "Invalid counter value:" << counter;
            return;
    }

    qreal anglePerSegment = spanAngle / numSegments;
    qreal ratio = qBound(qreal(0.0), value / maxValue, qreal(1.0));
    qreal filledAngle = spanAngle * ratio;

    for (int i = 0; i < numSegments; ++i)
    {
        qreal currentAngle = startAngle + i * anglePerSegment;
        qreal midAngle = currentAngle + anglePerSegment / 2;

        if (midAngle > startAngle + filledAngle)
            break;

        qreal midRad = qDegreesToRadians(midAngle);
        qreal centerX = qCos(midRad) * (innerRadius + outerRadius) / 2;
        qreal centerY = qSin(midRad) * (innerRadius + outerRadius) / 2;

        // ✅ 获取正确的图片
        if (i >= imageList->size()) {
            qWarning() << "Index out of bounds for imageList!";
            break;
        }

        const QPixmap &pixmap = (*imageList)[i];

        // ✅ 计算图片目标大小（确保不会覆盖整个仪表盘）
        int targetWidth = (outerRadius - innerRadius) * 8;  // 让图片稍微大一点，填充间隙
        int targetHeight = targetWidth * (pixmap.height() / static_cast<double>(pixmap.width()));

        QPixmap scaledPixmap = pixmap.scaled(targetWidth, targetHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);

        painter.save();
        painter.translate(centerX, centerY);
        painter.rotate(midAngle + 120);

        QRect targetRect(-scaledPixmap.width() / 2, -scaledPixmap.height() / 2, scaledPixmap.width(), scaledPixmap.height());
        painter.drawPixmap(targetRect, scaledPixmap);

        painter.restore();
    }
}

void Speedometer::drawAngle2(QPainter &painter, qreal value, qreal maxValue,
                            int innerRadius, int outerRadius, qreal startAngle, qreal spanAngle,
                            int counter)
{
    int numSegments = 300;

//    qreal ratio = qBound(0.0, value / maxValue, 1.0);
    qreal ratio = qBound(qreal(0.0), value / maxValue, qreal(1.0));
    qreal filledAngle = spanAngle * ratio;
    qreal anglePerSegment = spanAngle / numSegments;

    QPainterPath combinedPath;

    qreal currentAngle = 0;

    for (int i = 0; i < numSegments; ++i)
    {
        if(counter == 1){  //left
            currentAngle = startAngle + spanAngle - i * anglePerSegment - anglePerSegment;
        }else if(counter == 2){  //right
            currentAngle = startAngle + i * anglePerSegment;
        }

        if (i * anglePerSegment >= filledAngle)
            break;

        qreal position = static_cast<qreal>(i) / numSegments;
        QColor color;

        if(counter == 1){  //left
//            color = QColor::fromHsvF((1.0 - position) * 0.4, 1.0, 1.0);
            color = QColor::fromHsvF(0.0 + position * 0.083, 1.0, 1.0);
        }else if(counter == 2){  //right
            color = QColor::fromHsvF(0.33, 1.0, 0.5 + position * 0.5);

//            color = fixedColor.isValid() ? fixedColor : Qt::white;
        }

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
}

void Speedometer::drawLabels(QPainter &painter)
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

        cachePainter.setFont(QFont("Arial", 6, QFont::Bold));

        //for speed
        drawTicks(cachePainter, 9, 130.0, 300.0, QColor(255, 100, 0));

        //for powervalue
        drawTicks(cachePainter, 5, 323.0, 410.0, Qt::green);

        m_labelsCached = true;
    }

    painter.drawPixmap(0, 0, m_labelsCache);
}

void Speedometer::drawArc(QPainter &painter, int radius, qreal startAngle, qreal spanAngle, double width, QColor color)
{
    QPen pen(color, width);
    pen.setCapStyle(Qt::FlatCap);
    painter.setPen(pen);

    int startAngleInQt = startAngle * 16;
    int spanAngleInQt = spanAngle * 16;

    QRectF arcRect(-radius, -radius, 2 * radius, 2 * radius);

    painter.drawArc(arcRect, startAngleInQt, spanAngleInQt);
}

void Speedometer::drawTicks(QPainter &painter, int numTicks, qreal startAngle, qreal endAngle, QColor color)
{
    painter.setPen(QPen(color, 1.5));

    qreal angleIncrement = (endAngle - startAngle) / (numTicks - 1);

    for (int i = 0; i < numTicks; ++i)
    {
        qreal angle = startAngle + i * angleIncrement;
        qreal radians = qDegreesToRadians(angle);

        qreal xStart = 78 * qCos(radians);
        qreal yStart = 78 * qSin(radians);
        qreal xEnd = 85 * qCos(radians);
        qreal yEnd = 85 * qSin(radians);

        painter.drawLine(QPointF(xStart, yStart), QPointF(xEnd, yEnd));
    }
}

//be used

//void Speedometer::drawAngleImg2(qreal value, qreal maxValue, int counter)
//{
//    SpBackgroundImage *speedRing = this->findChild<SpBackgroundImage *>("speedRing");
//    SpBackgroundImage *battaryRing = this->findChild<SpBackgroundImage *>("battaryRing");

//    int totalSegments = (counter == 1) ? 8 : 4;
////    int index = std::round(value / maxValue * (totalSegments - 1)) + 1;
//    int index = qBound(1, static_cast<int>(std::round(value / maxValue * (totalSegments - 1))) + 1, totalSegments);

//    qDebug()<<__FUNCTION__<<__LINE__<<"              index="<<index;

//    if (speedRing) {
//        QString speedImagePath = QString(":/home_images/infopage/angle/speed%1.png").arg(index);
//        QPixmap speedPixmap(speedImagePath);
//        if (!speedPixmap.isNull()) {
//            speedRing->setPixmap(speedPixmap);
//            speedRing->update();
//        } else {
//            qWarning() << "Failed to load speed image at path:" << speedImagePath;
//        }
//    }

//    if (battaryRing) {
//        QString batteryImagePath = QString(":/home_images/infopage/angle/battary%1.png").arg(index);
//        QPixmap batteryPixmap(batteryImagePath);
//        if (!batteryPixmap.isNull()) {
//            battaryRing->setPixmap(batteryPixmap);
//            battaryRing->update();
//        } else {
//            qWarning() << "Failed to load battery image at path:" << batteryImagePath;
//        }
//    }
//}


void Speedometer::timerEvent(QTimerEvent *e)
{
    static int i = 0;
    static int j = 0;
    static bool speedIncreasing = true;
    static bool powerIncreasing = true;
    int updatespeed = 1;
    int updatepower = 1;

    if (e->timerId() == SpeedometerTimerID)
    {
        if (speedIncreasing)
        {
            i += updatespeed;
            if (i >= m_maxSpeed)
            {
                i = m_maxSpeed;
                speedIncreasing = false;
            }
        }
        else
        {
            i -= updatespeed;
            if (i <= 0)
            {
                i = 0;
                speedIncreasing = true;
            }
        }

        if (powerIncreasing)
        {
            j += updatepower;
            if (j >= m_maxpowervalue)
            {
                j = m_maxpowervalue;
                powerIncreasing = false;
            }
        }
        else
        {
            j -= updatepower;
            if (j <= 0)
            {
                j = 0;
                powerIncreasing = true;
            }
        }

        setSpeed(i);
        setPowerValue(j);
    }
}


void Speedometer::mousePressEvent(QMouseEvent *event)
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

void Speedometer::mouseMoveEvent(QMouseEvent *event)
{
    QWidget::mouseMoveEvent(event);
}

void Speedometer::mouseReleaseEvent(QMouseEvent *event)
{
    QWidget::mouseReleaseEvent(event);
}


