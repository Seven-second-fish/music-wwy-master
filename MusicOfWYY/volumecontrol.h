#ifndef VOLUMECONTROL_H
#define VOLUMECONTROL_H

#include <QWidget>
#include <QSlider>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>

class VolumeControl : public QWidget
{
    Q_OBJECT

public:
    explicit VolumeControl(QWidget *parent = nullptr);

signals:
    void volumeChanged(int value);  // Signal emitted when volume changes

public slots:
    void setVolume(int value);  // Slot to set the volume externally
    void handleVolumeChange(int value);  // Slot to handle volume changes from the slider

private:
    QSlider *volumeSlider;
    QLabel *volumeLabel;
};

#endif // VOLUMECONTROL_H
