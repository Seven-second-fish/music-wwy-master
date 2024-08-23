#include "customslider.h"
#include <QMouseEvent>

/*
    用于实现点击音量进度条某处直接跳转到该位置功能
    抛弃该功能
*/
CustomSlider::CustomSlider(QWidget *parent) : QSlider(parent) {}

void CustomSlider::mousePressEvent(QMouseEvent *event) {
    if (orientation() == Qt::Horizontal) {
        int pos = event->x();
        int newValue = minimum() + (maximum() - minimum()) * pos / width();
        setValue(newValue);
    } else {
        int pos = event->y();
        int newValue = minimum() + (maximum() - minimum()) * pos / height();
        setValue(newValue);
    }
    // Call the base class implementation to ensure default behavior
    QSlider::mousePressEvent(event);
}

void CustomSlider::mouseMoveEvent(QMouseEvent *event) {
    mousePressEvent(event);  // Handle dragging as well
}
