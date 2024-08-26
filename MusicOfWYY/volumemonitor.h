#ifndef VOLUMEMONITOR_H
#define VOLUMEMONITOR_H

#include <QObject>
#include <thread>
#include <atomic>
#include <iostream>

class VolumeMonitor : public QObject {
    Q_OBJECT

public:
    explicit VolumeMonitor(QObject *parent = nullptr);
    ~VolumeMonitor();

    void startMonitoring(); // 开始监控
    void stopMonitoring();  // 停止监控

signals:
    void systemVolumeChanged(int newVolume); // 当系统音量发生变化时发射信号

private:
    std::atomic<bool> stopMonitoringFlag; // 标志是否停止监控

    int getSystemVolume(); // 获取当前系统音量
    void monitorSystemVolume(); // 监控系统音量变化
};

#endif // VOLUMEMONITOR_H
