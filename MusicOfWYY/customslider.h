#ifndef CUSTOMSLIDER_H
#define CUSTOMSLIDER_H

#include <QSlider>
#include <QMouseEvent>

class CustomSlider : public QSlider {
    Q_OBJECT

public:
    explicit CustomSlider(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *ev) override;
};

#endif // CUSTOMSLIDER_H
