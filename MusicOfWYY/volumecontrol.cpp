#include "volumecontrol.h"

VolumeControl::VolumeControl(QWidget *parent) : QWidget(parent)
{
    // Initialize slider
    volumeSlider = new QSlider(Qt::Horizontal, this);
    volumeSlider->setRange(0, 100);  // Volume range from 0 to 100
    volumeSlider->setValue(50);  // Set initial value to 50

    // Initialize label
    volumeLabel = new QLabel("Volume: 50", this);

    // Layout setup
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(volumeLabel);
    layout->addWidget(volumeSlider);
    setLayout(layout);

    // Connect slider signal to the slot
    connect(volumeSlider, &QSlider::valueChanged, this, &VolumeControl::handleVolumeChange);
}

void VolumeControl::setVolume(int value)
{
    volumeSlider->setValue(value);
}

void VolumeControl::handleVolumeChange(int value)
{
    volumeLabel->setText(QString("Volume: %1").arg(value));
    emit volumeChanged(value);
}
