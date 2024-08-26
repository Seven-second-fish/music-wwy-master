#include "volumemonitor.h"
#include <chrono>
#include <thread>

VolumeMonitor::VolumeMonitor(QObject *parent)
    : QObject(parent), stopMonitoringFlag(false) {}

VolumeMonitor::~VolumeMonitor() {
    stopMonitoring(); // 确保对象销毁时停止监控线程
}

void VolumeMonitor::startMonitoring() {
    stopMonitoringFlag = false;
    std::thread monitorThread(&VolumeMonitor::monitorSystemVolume, this);
    monitorThread.detach(); // 将线程从主线程中分离，使其在后台运行
}

void VolumeMonitor::stopMonitoring() {
    stopMonitoringFlag = true; // 设置标志以停止监控
}

void VolumeMonitor::monitorSystemVolume() {
    int lastVolume = getSystemVolume();
    while (!stopMonitoringFlag) {
        int currentVolume = getSystemVolume();
        if (currentVolume != lastVolume) {
            lastVolume = currentVolume;
            emit systemVolumeChanged(currentVolume); // 如果音量变化，发射信号
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // 每500ms检查一次
    }
}

int VolumeMonitor::getSystemVolume() {
    int volume = -1;
    // 这里实现获取系统音量的逻辑
    // 示例：Windows 系统上可以使用 waveOutGetVolume API 获取音量
    // 或者在 Linux 系统上使用 ALSA 库获取音量
#if defined(_WIN32) || defined(_WIN64)  // Windows 平台
    #include <windows.h>
    #include <mmdeviceapi.h>
    #include <endpointvolume.h>

    HRESULT hr;
    CoInitialize(NULL);  // 初始化COM库

    IMMDeviceEnumerator* pDeviceEnumerator = NULL;
    hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER, __uuidof(IMMDeviceEnumerator), (LPVOID *)&pDeviceEnumerator);

    IMMDevice* pDevice = NULL;
    hr = pDeviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &pDevice);

    IAudioEndpointVolume* pEndpointVolume = NULL;
    hr = pDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_INPROC_SERVER, NULL, (LPVOID *)&pEndpointVolume);

    float currentVolume = 0;
    pEndpointVolume->GetMasterVolumeLevelScalar(&currentVolume);

    // 清理
    pEndpointVolume->Release();
    pDevice->Release();
    pDeviceEnumerator->Release();
    CoUninitialize();  // 释放COM库

    volume = static_cast<int>(currentVolume * 100); // 将音量转换为百分比

#elif defined(__APPLE__)  // macOS 平台
    #include <CoreAudio/CoreAudio.h>

    Float32 volumeLevel;
    UInt32 size = sizeof(Float32);
    AudioObjectPropertyAddress address = {
        kAudioHardwareServiceDeviceProperty_VirtualMasterVolume,
        kAudioDevicePropertyScopeOutput,
        kAudioObjectPropertyElementMaster
    };

    AudioObjectID deviceId = kAudioObjectSystemObject;
    AudioHardwareServiceGetPropertyData(deviceId, &address, 0, NULL, &size, &volumeLevel);

    volume = static_cast<int>(volumeLevel * 100); // 将音量转换为百分比

#elif defined(__linux__)  // Linux 平台
    FILE* pipe = popen("amixer get Master | grep -o '[0-9]*%' | head -n1 | tr -d '%'", "r");
    if (pipe) {
        char buffer[128];
        fgets(buffer, sizeof(buffer), pipe);
        pclose(pipe);
        volume = atoi(buffer); // 返回音量百分比
    }
#endif

    return volume;
}
