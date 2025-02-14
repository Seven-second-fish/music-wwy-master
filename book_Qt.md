# QT5教程 完整版



> 下方为教程路径地址

[QT指南](https://github.com/Nitrosaccharose/qt-learning-guide/blob/main/Qt%E6%8C%87%E5%8D%97.md)

[QT学习之路](https://www.devbean.net/2012/08/qt-study-road-2-catelog/)

[QT入门](https://subingwen.cn/qt/qt-primer/)

[CSDN教程](https://blog.csdn.net/m0_65635427/article/details/130780280?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522D4A398FD-F4BA-4351-B985-6B431FF8BEFA%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=D4A398FD-F4BA-4351-B985-6B431FF8BEFA&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~top_positive~default-1-130780280-null-null.142^v100^pc_search_result_base8&utm_term=qt&spm=1018.2226.3001.4187)

[视频教程](https://www.bilibili.com/video/BV1GW42197ff/?spm_id_from=333.337.search-card.all.click&vd_source=5cfc5f3807f31b335afa03d3ac5d692f)

------

进度：60  页

视频：C++QT2024年最新版，QT5

# QT知识点：

# 目录：需要填充的知识点

- [x] 定时器，文件操作，TCP，数据库

- [x] 信号与槽：Qt的核心机制，用于对象间的通信。通过信号和槽的连接，Qt允许在对象之间传递事件或数据。
- [x] 事件循环与事件处理：Qt应用是基于事件循环的，每当有事件（如鼠标点击、键盘输入等）发生时，Qt会将其分发到相应的处理函数。
- [x] 多线程：Qt支持多线程编程，提供了QThread类以及用于线程同步的机制，如信号槽、互斥量等。
- [x] 布局管理器：Qt提供了多种布局管理器，如QHBoxLayout、QVBoxLayout、QGridLayout等，用于自动调整界面元素的布局。
- [x] 自定义控件：Qt允许通过继承QWidget或QGraphicsItem来创建自定义控件，以满足特殊的UI需求。
- [ ] 模型/视图编程：Qt通过QAbstractItemModel和视图类（如QListView、QTableView、QTreeView）实现数据与UI分离，支持更灵活的数据展示。
- [ ] 图形视图框架：QGraphicsView和QGraphicsScene用于实现复杂的2D图形处理，支持图形项的动态交互。
- [x] 网络编程：除了TCP，还包括UDP、HTTP等协议的支持，Qt提供了QTcpSocket、QUdpSocket等类。
- [ ] 国际化与本地化：Qt支持多语言的国际化和本地化，可以通过QTranslator和.ts文件进行翻译。
- [ ] QtQuick与QML：Qt提供了用于构建现代、动态用户界面的框架，支持声明式编程，适合触摸屏、移动设备等应用。
- [ ] 图像处理：Qt提供了QImage、QPixmap等类进行图像的加载、显示、编辑和转换。
- [ ] 动画与过渡效果：Qt的QPropertyAnimation和QAnimationGroup类允许在应用程序中实现平滑的动画效果。
- [x] 小知识点，自己总结的内容

## 1. Qt 定时器使用指南：

### 1. Qt 定时器简介

Qt 提供了多种定时器机制来执行定时任务，主要包括：

- `QTimer`（最常用）
- `QBasicTimer`
- `QElapsedTimer`
- `QThread::msleep()` / `QThread::usleep()`
- `QTime`

### 2. QTimer 详解

#### 2.1 QTimer 基本用法

QTimer 是 Qt 中最常用的定时器，可以用来触发特定时间间隔的操作。

**示例 1：单次定时器**

```cpp
#include <QCoreApplication>
#include <QTimer>
#include <QDebug>

void timeoutHandler() {
    qDebug() << "Timeout occurred!";
}

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    QTimer::singleShot(2000, &timeoutHandler); // 2 秒后执行
    return a.exec();
}
```

**示例 2：周期性定时器**

```cpp
#include <QCoreApplication>
#include <QTimer>
#include <QDebug>

class MyClass : public QObject {
    Q_OBJECT
public:
    MyClass() {
        QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &MyClass::onTimeout);
        timer->start(1000); // 每 1 秒触发一次
    }

public slots:
    void onTimeout() {
        qDebug() << "Timer triggered!";
    }
};

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    MyClass obj;
    return a.exec();
}
```

#### 2.2 停止定时器

使用 `QTimer::stop()` 方法可以停止定时器。

```cpp
timer->stop();
```

### 3. QBasicTimer

QBasicTimer 适用于对性能要求较高的场景，需要手动管理定时器事件。

```cpp
#include <QCoreApplication>
#include <QBasicTimer>
#include <QTimerEvent>
#include <QDebug>

class MyClass : public QObject {
    Q_OBJECT
    QBasicTimer timer;

public:
    void startTimer() {
        timer.start(1000, this); // 1 秒触发一次
    }

protected:
    void timerEvent(QTimerEvent *event) override {
        if (event->timerId() == timer.timerId()) {
            qDebug() << "Basic timer triggered!";
        }
    }
};

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    MyClass obj;
    obj.startTimer();
    return a.exec();
}
```

### 4. QElapsedTimer

QElapsedTimer 用于高精度时间测量。

```cpp
#include <QCoreApplication>
#include <QElapsedTimer>
#include <QDebug>

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    QElapsedTimer timer;
    timer.start();
    // 执行一些任务
    qint64 elapsed = timer.elapsed(); // 获取经过的毫秒数
    qDebug() << "Elapsed time:" << elapsed << "ms";
    return a.exec();
}
```

### 5. QTime 计时

`QTime` 类也可以用于测量时间间隔，适用于较低精度的需求。

```cpp
#include <QCoreApplication>
#include <QTime>
#include <QDebug>

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    QTime time;
    time.start();
    // 模拟耗时任务
    QThread::sleep(1);
    int elapsed = time.elapsed();
    qDebug() << "Elapsed time:" << elapsed << "ms";
    return a.exec();
}
```

### 6. 线程中的定时器

使用 `QThread::msleep()` 可以在线程中暂停执行。

```cpp
#include <QThread>
#include <QDebug>

class MyThread : public QThread {
    void run() override {
        qDebug() << "Thread started";
        QThread::msleep(2000);
        qDebug() << "Thread finished";
    }
};

int main() {
    MyThread thread;
    thread.start();
    thread.wait();
    return 0;
}
```

### 7. 总结

- `QTimer` 适用于大多数定时任务，支持单次和周期性触发。
- `QBasicTimer` 适用于性能要求高的场景。
- `QElapsedTimer` 适用于测量时间间隔。
- `QTime` 适用于低精度计时。
- `QThread::msleep()` 可用于线程休眠。

合理选择定时器可以提升 Qt 应用的性能和响应速度。

## 信号与槽

Qt 的信号与槽机制是一种用于对象间通信的机制，类似于观察者模式。信号（Signal）在特定事件发生时发出，槽（Slot）是用于响应信号的函数。

### 1. 基本用法

信号与槽的连接通过 `QObject::connect` 方法完成，可以连接 Qt 提供的信号，也可以连接自定义信号。

```cpp
#include <QApplication>
#include <QPushButton>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QPushButton button("Click Me");
    QObject::connect(&button, &QPushButton::clicked, &app, &QApplication::quit);
    button.show();
    return app.exec();
}
```

### 2. 自定义信号与槽

可以通过 `signals` 关键字定义信号，并通过 `slots` 关键字定义槽。

```cpp
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QObject>
#include <QDebug>

class MyWidget : public QWidget {
    Q_OBJECT

public:
    MyWidget(QWidget *parent = nullptr) {
        QPushButton *button = new QPushButton("Press Me", this);
        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->addWidget(button);
        connect(button, &QPushButton::clicked, this, &MyWidget::handleButtonClick);
        connect(this, &MyWidget::mySignal, this, &MyWidget::mySlot);
    }

signals:
    void mySignal();

public slots:
    void handleButtonClick() {
        qDebug() << "Button clicked! Emitting signal...";
        emit mySignal();
    }

    void mySlot() {
        qDebug() << "Custom signal received!";
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MyWidget widget;
    widget.show();
    return app.exec();
}
```

### 3. 连接多个信号与槽

```cpp
connect(sender, &SenderClass::signal1, receiver, &ReceiverClass::slot1);
connect(sender, &SenderClass::signal2, receiver, &ReceiverClass::slot2);
```

### 4. 断开信号与槽

```cpp
disconnect(sender, &SenderClass::signal1, receiver, &ReceiverClass::slot1);
```

## 事件循环与事件处理

Qt 的事件循环是基于 `QEventLoop` 实现的，`QApplication::exec()` 进入主事件循环，处理 GUI 事件。

### 1. 事件处理机制

Qt 事件系统基于 `QEvent`，每个窗口组件都能接收和处理事件。

```cpp
#include <QApplication>
#include <QWidget>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QWheelEvent>
#include <QDebug>

class MyWidget : public QWidget {
protected:
    void mousePressEvent(QMouseEvent *event) override {
        qDebug() << "Mouse Pressed at: " << event->pos();
    }

    void keyPressEvent(QKeyEvent *event) override {
        qDebug() << "Key Pressed: " << event->key();
    }

    void wheelEvent(QWheelEvent *event) override {
        qDebug() << "Mouse Wheel Delta: " << event->angleDelta();
    }

    void resizeEvent(QResizeEvent *event) override {
        qDebug() << "Widget resized: " << event->size();
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MyWidget widget;
    widget.show();
    return app.exec();
}
```

### 2. 事件过滤器

使用 `installEventFilter` 可以在对象级别拦截事件。

```cpp
class EventFilter : public QObject {
protected:
    bool eventFilter(QObject *obj, QEvent *event) override {
        if (event->type() == QEvent::KeyPress) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            qDebug() << "Key Pressed in Filter: " << keyEvent->key();
            return true; // 阻止事件传播
        }
        return QObject::eventFilter(obj, event);
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MyWidget widget;
    EventFilter filter;
    widget.installEventFilter(&filter);
    widget.show();
    return app.exec();
}
```

## 布局管理器

Qt 提供 `QVBoxLayout`、`QHBoxLayout`、`QGridLayout`、`QFormLayout` 等布局管理器。

### 1. 使用 `QVBoxLayout`

```cpp
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QWidget window;
    QVBoxLayout *layout = new QVBoxLayout(&window);
    QPushButton *btn1 = new QPushButton("Button 1");
    QPushButton *btn2 = new QPushButton("Button 2");
    layout->addWidget(btn1);
    layout->addWidget(btn2);
    window.show();
    return app.exec();
}
```

### 2. 使用 `QGridLayout`

```cpp
#include <QGridLayout>
#include <QLabel>
#include <QApplication>
#include <QWidget>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QWidget window;
    QGridLayout *layout = new QGridLayout(&window);
    layout->addWidget(new QLabel("Row 0, Col 0"), 0, 0);
    layout->addWidget(new QLabel("Row 0, Col 1"), 0, 1);
    layout->addWidget(new QLabel("Row 1, Col 0"), 1, 0);
    layout->addWidget(new QLabel("Row 1, Col 1"), 1, 1);
    window.show();
    return app.exec();
}
```

## 自定义控件

### 1. 继承 `QWidget` 进行绘制

可以重写 `paintEvent` 方法，使用 `QPainter` 进行绘制。

```cpp
#include <QApplication>
#include <QWidget>
#include <QPainter>

class CustomWidget : public QWidget {
protected:
    void paintEvent(QPaintEvent *) override {
        QPainter painter(this);
        painter.setBrush(Qt::blue);
        painter.drawRect(10, 10, 100, 100);
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    CustomWidget widget;
    widget.show();
    return app.exec();
}
```

### 2. 自定义按钮控件

```cpp
#include <QPushButton>
#include <QPainter>
class CustomButton : public QPushButton {
    Q_OBJECT
public:
    CustomButton(const QString &text, QWidget *parent = nullptr) : QPushButton(text, parent) {}
protected:
    void paintEvent(QPaintEvent *) override {
        QPainter painter(this);
        painter.setBrush(Qt::red);
        painter.drawRect(rect());
        painter.drawText(rect(), Qt::AlignCenter, text());
    }
};
```


## Qt 多线程开发指南

### 1. 引言
在 Qt 进行多线程编程时，可以使用 `QThread` 直接继承或移动到新线程，也可以使用 `QRunnable` 结合 `QThreadPool` 进行轻量级任务管理。本指南将介绍 Qt 多线程的基础知识，并通过示例进行讲解。

---

### 2. 使用 QThread 继承方式

#### 2.1 QThread 介绍

`QThread` 是 Qt 提供的线程类，通常有两种使用方式：
- 继承 `QThread`，重写 `run()` 方法
- 继承 `QObject`，将对象移动到 `QThread`

#### 2.2 继承 QThread 实现线程
```cpp
#include <QThread>
#include <QDebug>

class MyThread : public QThread {
public:
    void run() override {
        for (int i = 0; i < 5; ++i) {
            qDebug() << "Running in thread:" << QThread::currentThread();
            QThread::sleep(1);
        }
    }
};

int main() {
    MyThread thread;
    thread.start();
    thread.wait();
    return 0;
}
```

#### 2.3 使用 QObject + QThread

```cpp
#include <QCoreApplication>
#include <QThread>
#include <QDebug>

class Worker : public QObject {
    Q_OBJECT
public slots:
    void process() {
        for (int i = 0; i < 5; ++i) {
            qDebug() << "Processing in thread:" << QThread::currentThread();
            QThread::sleep(1);
        }
    }
};

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    
    QThread thread;
    Worker worker;
    worker.moveToThread(&thread);
    
    QObject::connect(&thread, &QThread::started, &worker, &Worker::process);
    thread.start();
    
    return a.exec();
}
```

---

### 3. 使用 QRunnable 和 QThreadPool

`QRunnable` 适用于短时间任务，结合 `QThreadPool` 进行管理。

```cpp
#include <QRunnable>
#include <QThreadPool>
#include <QDebug>

class MyTask : public QRunnable {
public:
    void run() override {
        qDebug() << "Task running in thread:" << QThread::currentThread();
    }
};

int main() {
    QThreadPool::globalInstance()->start(new MyTask());
    return 0;
}
```

---

### 4. 线程间通信（信号与槽）
在多线程环境下，`Qt::QueuedConnection` 方式可用于线程间通信。

```cpp
#include <QObject>
#include <QThread>
#include <QDebug>

class Worker : public QObject {
    Q_OBJECT
public slots:
    void doWork() {
        qDebug() << "Worker thread:" << QThread::currentThread();
    }
};

int main() {
    QThread thread;
    Worker worker;
    worker.moveToThread(&thread);
    QObject::connect(&thread, &QThread::started, &worker, &Worker::doWork);
    thread.start();
    return 0;
}
```

---

### 5. 线程管理
#### 5.1 停止线程
使用 `requestInterruption()` 和 `isInterruptionRequested()` 进行线程终止。

```cpp
class MyThread : public QThread {
public:
    void run() override {
        while (!isInterruptionRequested()) {
            qDebug() << "Running...";
            QThread::msleep(500);
        }
        qDebug() << "Thread stopped.";
    }
};

int main() {
    MyThread thread;
    thread.start();
    QThread::sleep(2);
    thread.requestInterruption();
    thread.wait();
    return 0;
}
```

---

### 6. 结论
- `QThread` 适用于长期运行的线程
- `QRunnable` + `QThreadPool` 适用于短时间任务
- `moveToThread()` 提供更好的面向对象方式
- `Qt::QueuedConnection` 实现线程安全的信号槽通信

以上内容涵盖了 Qt 多线程的基础用法，可根据需求选择合适的方法。

## QT文件操作

### 1. 引言
Qt 提供了 `QFile`、`QTextStream`、`QFileInfo`、`QDir` 等类用于文件操作，支持读取、写入、删除文件，以及操作目录。

### 2. 读取文件内容
#### 2.1 逐行读取文本文件
```cpp
#include <QFile>
#include <QTextStream>
#include <QDebug>

void readFile(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "无法打开文件:" << file.errorString();
        return;
    }
    
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        qDebug() << line;
    }
    file.close();
}
```

#### 2.2 读取整个文件内容
```cpp
void readWholeFile(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "无法打开文件:" << file.errorString();
        return;
    }
    QTextStream in(&file);
    qDebug() << in.readAll();
    file.close();
}
```

### 3. 写入文件内容
#### 3.1 覆盖写入文件
```cpp
void writeFile(const QString &filePath, const QString &content) {
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "无法打开文件:" << file.errorString();
        return;
    }
    QTextStream out(&file);
    out << content;
    file.close();
}
```

#### 3.2 追加写入文件
```cpp
void appendToFile(const QString &filePath, const QString &content) {
    QFile file(filePath);
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        qDebug() << "无法打开文件:" << file.errorString();
        return;
    }
    QTextStream out(&file);
    out << content << "\n";
    file.close();
}
```

### 4. 删除文件
```cpp
void deleteFile(const QString &filePath) {
    QFile file(filePath);
    if (file.exists()) {
        if (file.remove()) {
            qDebug() << "文件删除成功";
        } else {
            qDebug() << "文件删除失败";
        }
    } else {
        qDebug() << "文件不存在";
    }
}
```

### 5. 目录操作
#### 5.1 创建目录
```cpp
void createDirectory(const QString &dirPath) {
    QDir dir;
    if (dir.exists(dirPath)) {
        qDebug() << "目录已存在";
    } else {
        if (dir.mkpath(dirPath)) {
            qDebug() << "目录创建成功";
        } else {
            qDebug() << "目录创建失败";
        }
    }
}
```

#### 5.2 遍历目录
```cpp
void listFilesInDirectory(const QString &dirPath) {
    QDir dir(dirPath);
    if (!dir.exists()) {
        qDebug() << "目录不存在";
        return;
    }
    QStringList files = dir.entryList(QDir::Files);
    foreach (QString file, files) {
        qDebug() << file;
    }
}
```

#### 5.3 删除目录及其内容
```cpp
void deleteDirectory(const QString &dirPath) {
    QDir dir(dirPath);
    if (dir.exists()) {
        if (dir.removeRecursively()) {
            qDebug() << "目录删除成功";
        } else {
            qDebug() << "目录删除失败";
        }
    } else {
        qDebug() << "目录不存在";
    }
}
```

### 6. 获取文件信息
```cpp
void getFileInfo(const QString &filePath) {
    QFileInfo fileInfo(filePath);
    if (!fileInfo.exists()) {
        qDebug() << "文件不存在";
        return;
    }
    qDebug() << "文件名:" << fileInfo.fileName();
    qDebug() << "文件路径:" << fileInfo.filePath();
    qDebug() << "文件大小:" << fileInfo.size() << "字节";
    qDebug() << "最后修改时间:" << fileInfo.lastModified().toString();
}
```

### 7. 结论
Qt 提供了丰富的文件操作接口，包括文件读取、写入、删除、目录操作等，使用 `QFile`、`QDir` 和 `QFileInfo` 可以方便地处理文件系统任务。

## Qt TCP 网络编程教程

### 1. 简介

在Qt中，可以使用 `QTcpSocket` 和 `QTcpServer` 类来进行TCP通信。`QTcpSocket` 用于客户端，`QTcpServer` 用于服务器。通过这两个类，可以实现网络数据的发送和接收。Qt的网络模块使得开发者能够方便地进行TCP、UDP等协议的实现，而无需处理底层的网络细节。

### 2. 创建TCP客户端

#### 2.1. 导入模块

首先，确保你的Qt项目中包含了网络模块。可以在 `.pro` 文件中添加：

```pro
QT += network
```

#### 2.2. 客户端代码

```cpp
#include <QTcpSocket>
#include <QCoreApplication>
#include <QTextStream>
#include <QDebug>

class TcpClient : public QObject
{
    Q_OBJECT

public:
    TcpClient() {
        socket = new QTcpSocket(this);

        // 连接服务器
        socket->connectToHost("127.0.0.1", 1234);
        connect(socket, &QTcpSocket::connected, this, &TcpClient::onConnected);
        connect(socket, &QTcpSocket::readyRead, this, &TcpClient::onReadyRead);
        connect(socket, &QTcpSocket::errorOccurred, this, &TcpClient::onErrorOccurred);
    }

private slots:
    void onConnected() {
        qDebug() << "连接成功!";
        // 发送数据
        socket->write("Hello, Server!");
    }

    void onReadyRead() {
        QByteArray data = socket->readAll();
        qDebug() << "接收到数据:" << data;
    }
    
    void onErrorOccurred(QTcpSocket::SocketError socketError) {
        qDebug() << "发生错误:" << socket->errorString();
    }

private:
    QTcpSocket *socket;
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    TcpClient client;

    return a.exec();
}

#include "main.moc"
```

#### 2.3. 解释

- `QTcpSocket` 对象用于连接到服务器，`connectToHost` 方法接受主机地址和端口号。
- 使用 `write` 方法发送数据，`readyRead` 信号用于接收数据。
- `errorOccurred` 信号用于处理连接中的错误，例如网络中断、无法连接等问题。

#### 2.4. 错误处理与重连

为了增加客户端的健壮性，可以为 `QTcpSocket` 设置错误处理逻辑，并实现自动重连机制。

```cpp
void TcpClient::onErrorOccurred(QTcpSocket::SocketError socketError) {
    qDebug() << "连接错误:" << socket->errorString();
    if (socketError == QTcpSocket::NetworkError) {
        // 在发生网络错误时尝试重新连接
        qDebug() << "尝试重新连接...";
        socket->connectToHost("127.0.0.1", 1234);
    }
}
```

### 3. 创建TCP服务器

#### 3.1. 服务器代码

```cpp
#include <QTcpServer>
#include <QTcpSocket>
#include <QCoreApplication>
#include <QDebug>

class TcpServer : public QObject
{
    Q_OBJECT

public:
    TcpServer() {
        server = new QTcpServer(this);
        
        // 监听端口
        if (!server->listen(QHostAddress::Any, 1234)) {
            qDebug() << "无法启动服务器";
            return;
        }
        
        connect(server, &QTcpServer::newConnection, this, &TcpServer::onNewConnection);
    }

private slots:
    void onNewConnection() {
        QTcpSocket *clientSocket = server->nextPendingConnection();
        connect(clientSocket, &QTcpSocket::readyRead, this, [=]() {
            QByteArray data = clientSocket->readAll();
            qDebug() << "接收到数据:" << data;
            clientSocket->write("Hello, Client!");
        });
        
        connect(clientSocket, &QTcpSocket::disconnected, this, [=]() {
            clientSocket->deleteLater();
            qDebug() << "客户端断开连接";
        });
    }

private:
    QTcpServer *server;
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    TcpServer server;

    return a.exec();
}

#include "main.moc"
```

#### 3.2. 解释

- `QTcpServer` 对象用于监听客户端的连接。
- 通过 `nextPendingConnection` 获取客户端连接。
- 通过 `readyRead` 信号接收数据，并使用 `write` 方法发送响应。
- 使用 `disconnected` 信号处理客户端断开连接的情况，释放资源并关闭连接。

#### 3.3. 多客户端处理

如果要支持多个客户端的并发连接，可以将每个客户端连接保存在一个容器中。每当有新的客户端连接时，将其加入容器；当客户端断开连接时，从容器中移除它们。

### 4. 示例：客户端与服务器交互

1. 启动服务器端程序，它将监听端口 `1234`。
2. 启动客户端程序，它将连接到服务器并发送 `"Hello, Server!"`。
3. 服务器接收到消息后，将回复 `"Hello, Client!"`。

### 5. 常见问题

#### 5.1. 如何处理网络延迟？

- 使用异步通信（例如 `QTcpSocket::waitForReadyRead`）可以确保UI线程不会被阻塞。
- 可以通过设置超时机制来处理网络延迟，例如使用 `setSocketOption` 设置 TCP_NODELAY。

#### 5.2. 如何处理多个客户端？

- 可以使用 `QTcpServer::nextPendingConnection()` 获取每一个新的客户端连接，并将它们分别处理。
- 通过为每个客户端创建一个独立的 `QTcpSocket` 对象，确保并发连接可以独立处理。

#### 5.3. 如何处理断线重连？

- 使用 `QTcpSocket` 的 `errorOccurred` 信号处理断线错误，并在适当时尝试重新连接。可以在错误处理函数中设置重试逻辑。

### 6. 参考资料

- [Qt官方文档 - QTcpSocket](https://doc.qt.io/qt-5/qtcore-qtcpsocket.html)
- [Qt官方文档 - QTcpServer](https://doc.qt.io/qt-5/qtcore-qtcpserver.html)

## Qt 连接 MySQL 教程

### **1. 前置准备**

在 Qt 中使用 MySQL 需要以下环境：

- Qt 安装（建议 Qt 5 或 Qt 6）
- MySQL 数据库（确保 MySQL Server 正常运行）
- MySQL 连接驱动

**安装 MySQL 连接驱动（Ubuntu）**

```bash
sudo apt update
sudo apt install libqt5sql5-mysql # Qt 5
sudo apt install libqt6sql6-mysql # Qt 6
```

**安装 MySQL 连接驱动（Windows）**

如果是 Windows，你可能需要手动下载 `qsqlmysql.dll` 并将其放入 Qt 目录（如 `C:\Qt\5.x.x\mingwxx_64\plugins\sqldrivers`）。

### **2. 在 Qt 项目中使用 MySQL**

#### **2.1 pro 文件配置**

在 `.pro` 文件中添加 SQL 模块支持：

```pro
QT += sql
```

#### **2.2 代码示例**

以下是 **Qt 连接 MySQL** 并执行查询的示例代码：

```cpp
#include <QCoreApplication>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>

void connectToDatabase() {
    // 创建数据库连接
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost"); // 服务器地址
    db.setDatabaseName("testdb"); // 数据库名称
    db.setUserName("root"); // 用户名
    db.setPassword("password"); // 密码
    
    if (!db.open()) {
        qDebug() << "连接数据库失败: " << db.lastError().text();
        return;
    }
    qDebug() << "数据库连接成功！";

    // 创建表
    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS users (id INT PRIMARY KEY AUTO_INCREMENT, name VARCHAR(50))");
    
    // 插入数据
    query.prepare("INSERT INTO users (name) VALUES (:name)");
    query.bindValue(":name", "张三");
    if (!query.exec()) {
        qDebug() << "插入失败: " << query.lastError().text();
    } else {
        qDebug() << "插入成功！";
    }

    // 查询数据
    if (query.exec("SELECT * FROM users")) {
        while (query.next()) {
            qDebug() << "ID:" << query.value("id").toInt() << "Name:" << query.value("name").toString();
        }
    } else {
        qDebug() << "查询失败: " << query.lastError().text();
    }
}

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    connectToDatabase();
    return a.exec();
}
```

### **3. 在 Qt UI 中显示 MySQL 数据**

#### **3.1 在 Qt Designer 中添加控件**

- 打开 Qt Designer。
- 添加一个 `QTableView` 控件到 UI 界面。
- 在代码中获取 `QTableView` 组件的对象。

#### **3.2 使用 `QSqlTableModel` 绑定数据**

```cpp
#include <QSqlTableModel>
#include <QTableView>

void showDataInTableView(QTableView *tableView) {
    QSqlTableModel *model = new QSqlTableModel();
    model->setTable("users");
    model->select();
    tableView->setModel(model);
}
```

### **4. 运行程序**

#### **4.1 启动 MySQL 服务器**

```bash
sudo systemctl start mysql
```

#### **4.2 运行 Qt 项目**

编译并运行 Qt 代码，观察终端输出。

### **5. 可能遇到的问题及解决方案**

#### **5.1 无法加载 QMYSQL 驱动**

**错误信息：**

```
QSqlDatabase: QMYSQL driver not loaded
```

**解决方案：**

1. 确保已安装 `libqt5sql5-mysql`（Linux）或 `qsqlmysql.dll`（Windows）。
2. 确保 `mysqlclient.dll` 或 `libmysqlclient.so` 在 `PATH` 环境变量中。

#### **5.2 连接失败（认证方式问题）**

**错误信息：**

```
Access denied for user 'root'@'localhost'
```

**解决方案：**

1. 确保数据库用户 `root` 允许远程连接。

2. 可能需要修改 MySQL 认证方式：

   ```sql
   ALTER USER 'root'@'localhost' IDENTIFIED WITH mysql_native_password BY 'password';
   FLUSH PRIVILEGES;
   ```

------

### **6. 总结**

- **安装 MySQL 驱动**（`libqt5sql5-mysql` / `qsqlmysql.dll`）。
- **在 Qt 项目中配置 `.pro` 文件**。
- **使用 `QSqlDatabase` 连接 MySQL 并执行 SQL 语句**。
- **在 `QTableView` 中显示 MySQL 数据**。
- **排查 `QMYSQL` 驱动问题和数据库权限问题**。

## 模型/视图编程（Model/View Programming）

Qt 提供了一套强大的 **Model/View** 体系来管理和显示数据，主要组件包括：

- **QAbstractItemModel**（抽象模型基类）
- **QAbstractListModel / QAbstractTableModel / QAbstractItemModel**（具体实现）
- **QListView / QTableView / QTreeView**（视图类）
- **QItemDelegate**（自定义委托）
- **QSortFilterProxyModel**（数据过滤与排序）

### 1. 简单示例：自定义 ListModel

```cpp
#include <QAbstractListModel>

class SimpleListModel : public QAbstractListModel {
    Q_OBJECT
public:
    explicit SimpleListModel(QObject *parent = nullptr) : QAbstractListModel(parent) {
        dataList = {"Item 1", "Item 2", "Item 3"};
    }

    int rowCount(const QModelIndex &parent = QModelIndex()) const override {
        return dataList.size();
    }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override {
        if (!index.isValid() || index.row() >= dataList.size())
            return QVariant();
        
        if (role == Qt::DisplayRole)
            return dataList.at(index.row());
        
        return QVariant();
    }

private:
    QStringList dataList;
};
```

### 2. 使用代理模型进行排序

```cpp
QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel;
proxyModel->setSourceModel(model);
proxyModel->sort(0);
view->setModel(proxyModel);
```

---

## 图形视图框架（Graphics View Framework）

Qt 的 **QGraphicsView** 提供了一个高效的 2D 图形框架，主要包括：

- **QGraphicsScene**（场景，管理图形项）
- **QGraphicsView**（视图，显示场景内容）
- **QGraphicsItem**（图形项）
- **QGraphicsPixmapItem**（显示图片）
- **QGraphicsTextItem**（显示文本）
- **QGraphicsEllipseItem / QGraphicsRectItem / QGraphicsLineItem**（基本形状）

### 1. 基本示例：绘制矩形

```cpp
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    QGraphicsScene scene;
    QGraphicsRectItem *rect = scene.addRect(0, 0, 100, 50);
    rect->setBrush(Qt::blue);
    
    QGraphicsView view(&scene);
    view.show();
    
    return app.exec();
}
```

### 2. 添加图片

```cpp
QGraphicsPixmapItem *pixmapItem = new QGraphicsPixmapItem(QPixmap("image.png"));
scene.addItem(pixmapItem);
```

---

## 图像处理（Image Processing）

Qt 提供 **QImage、QPixmap、QPainter** 进行图像处理，常见操作包括：

- **加载 & 保存图片（QImage::load, save）**
- **调整大小（QImage::scaled）**
- **灰度化（QImage::convertToFormat）**
- **绘制图像（QPainter）**

### 1. 读取 & 保存图片

```cpp
QImage image("image.png");
image.save("output.jpg", "JPG");
```

### 2. 调整大小

```cpp
QImage resizedImage = image.scaled(200, 200, Qt::KeepAspectRatio);
```

### 3. 旋转图片

```cpp
QTransform transform;
transform.rotate(90);
QImage rotatedImage = image.transformed(transform);
```

### 4. 在图片上绘制文字

```cpp
QPainter painter(&image);
painter.setFont(QFont("Arial", 20));
painter.setPen(Qt::red);
painter.drawText(image.rect(), Qt::AlignCenter, "Hello, Qt!");
painter.end();
image.save("output.png");
```

---

## 动画与过渡效果（Animations & Transitions）

Qt 的动画框架基于 **QPropertyAnimation**、**QGraphicsItemAnimation**、**QParallelAnimationGroup**，常见动画包括：

- **移动动画（QPropertyAnimation::setStartValue, setEndValue）**
- **缩放动画（QGraphicsItem::setScale）**
- **旋转动画（QGraphicsItem::setRotation）**
- **透明度动画（QGraphicsOpacityEffect）**

### 1. 移动动画

```cpp
#include <QPropertyAnimation>

QPushButton *button = new QPushButton("Move");
button->show();

QPropertyAnimation *animation = new QPropertyAnimation(button, "geometry");
animation->setDuration(1000);
animation->setStartValue(QRect(0, 0, 100, 30));
animation->setEndValue(QRect(200, 200, 100, 30));
animation->start();
```

### 2. 透明度动画

```cpp
#include <QGraphicsOpacityEffect>

QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect(button);
button->setGraphicsEffect(effect);

QPropertyAnimation *fade = new QPropertyAnimation(effect, "opacity");
fade->setDuration(1500);
fade->setStartValue(1.0);
fade->setEndValue(0.0);
fade->start();
```

### 3. 旋转动画

```cpp
QGraphicsItem *item = new QGraphicsRectItem(0, 0, 50, 50);
QPropertyAnimation *rotateAnim = new QPropertyAnimation(item, "rotation");
rotateAnim->setDuration(2000);
rotateAnim->setStartValue(0);
rotateAnim->setEndValue(360);
rotateAnim->start();
```

## 小知识点

1. 字符串拼接：ui->label_time->setText(QString("title%1").arg(num++));

2. 尝试使用调试程序，多使用帮助文档Assistant(查找功能)

3. 主函数写法：

   ```c++
   //固定形式
   int main(int argc, char *argv[])
   {
       QApplication a(argc, argv);
       AllMain w;
       w.show();
   
       return a.exec();
   }
   ```

4. exec()退出函数

5. QMessageBox::warning，QMessageBox::Yes

6. QDialog::Accepted

7. setEchoMode(QLineEdit::Password)：设置密码框

8. text().trimmed()：移除字符串开头和结尾的空白字符，tr()

9. setFocus()：设置光标显示位置

10. 解决内存占用过多的问题：

   **延迟加载（懒加载）** 

   只在需要时才创建页面实例。你可以在用户第一次访问某个页面时动态加载和初始化该页面，而不是在启动时一次性加载所有页面。

   **资源回收（惰性卸载）**

   当页面不再需要时，你可以卸载或释放这些页面以回收内存。这样做可以减少内存占用。

   **按需加载与卸载**

   你可以在切换页面时按需加载和卸载页面。这样做可以在用户访问页面时才创建实例，切换到其他页面时释放不需要的页面。

11. message：tr("%1,%2").arg(text1).agr(text2)

12. 在使用如下函数时，对于默认组件，比如QPushButton等，实现点击可调用clicked()默认函数，不能自定义点击函数，也没必要。槽函数可调用本类的函数或者一个发到其他类的信号

    ```
    connect(ui->pushButton_min, SIGNAL(clicked()), this, SLOT(btn_bkg_min()));
    ```

13. 引用\#include <QSqlDatabase>需要加QT += sql

14. 推荐使用.qss文件统一管理样式，比如引入图片等

15. 判断组件存在并设置其显示隐藏基本流程

    volume_slider = this->findChild<QSlider *>("volumeSlider");

    if(volume_slider && volume_slider->isVisible()){

    volume_slider->hide();

    }else{

    volume_slider->show();

    }

16. 旧的信号槽：信号signal与槽机制slot不支持传递参数，

     新的信号槽：使用 Lambda 表达式，提供了更大的灵活性，允许传递额外的参数并确保信号和槽的匹配在编译时检查，比如true，false等

17. 如果槽函数需要传递按钮状态，使用 QPushButton::toggled 信号。如果槽函数不需要传递参数，使用 QPushButton::clicked 信号。

18. lambda表达式使用

    ```c
    ##目前理解
    connect(ui->btnPlayPause, &QPushButton::toggled, [this](bool checked){
            checked?player->play():player->pause();
        });
    ```

19. 条件表达式
    if(a>b) max=a; else max=b;
    可用条件表达式写为 max=(a>b)?a:b;

    其中：

    1. max=(a>b)?a:b 可以去掉括号而写为 max=a>b?a:b

    2. ?和：是一对运算符，不能分开

    3. 运算符的结合方向是自右向左

       a>b?a:c>d?c:d 应理解为 a>b?a:(c>d?c:d)

20. Q_OBJECT

    必须在附属类的头文件中加入这个宏

    这个宏的展开将为我们的类提供信号槽机制、国际化机制以及 Qt 提供的不基于 C++ RTTI 的反射能力

21. QT基本模块

    目前使用了：Qt Core，Qt Gui

22. 如果 Qt 的主版本号（`QT_MAJOR_VERSION`）大于 4，也就是 Qt 5，需要在.pro文件加上

    `greaterThan**(**QT_MAJOR_VERSION, 4**)**: QT += widgets`

23. QKeySequence

    使用了`setShortcut()`函数，用于说明这个`QAction`的快捷键

24. triggered

25. res.qrc，使用方式

    ```c
    //添加语言区分
    //如果本机的本地化信息是fr的话(QLocale::system().name()返回fr_FR()),则使用:/images/fr/doc-open这个图片
    <RCC>
        <qresource prefix="/images">
            <file alias="doc-open">document-open.png</file>
        </qresource>
        <qresource prefix="/images/fr" lang="fr">
            <file alias="doc-open">document-open-fr.png</file>
        </qresource>
    </RCC>
    ```

26. QWidget->QHBosLayout->小组件

27. 事件过滤器：(包括事件处理，一知半解需要后续学习)

    ```c
    //eventFilter()创建了不让textEdit组件处理键盘按下的事件
    //安装过滤器需要调用installEventFilter()函数
    MainWindow::MainWindow()
     {
         textEdit = new QTextEdit;
         setCentralWidget(textEdit);
         textEdit->installEventFilter(this);
     }
     bool MainWindow::eventFilter(QObject *obj, QEvent *event)
     {
         if (obj == textEdit) {
             if (event->type() == QEvent::KeyPress) {
                 QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
                 qDebug() << "Ate key press" << keyEvent->key();
                 return true;
             } else {
                 return false;
             }
         } else {
             // pass the event on to the parent class
             return QMainWindow::eventFilter(obj, event);
         }
     }
    ```

28. 由上延伸：事件处理器常用函数

    Event Classes

    https://subingwen.cn/qt/event_handler/

29. 交叉编译(makefile，mingw64，后续深入学习)

30. Qt 绘制系统：QPainter

31. QT事件：

    ```c
    //key键盘事件
    #include <QKeyEvent>
    void MainWindow::keyPressEvent(QKeyEvent *event)
    {
        //错误案例：k->key()只会返回一个键值
        if(event->key() == Qt::Key_A && event->key() == Qt::Key_Control)
        {
            printf("%s","A");
        }
        //修正：
        if (k->key() == Qt::Key_A && k->modifiers() == Qt::ControlModifier)
        {
            printf("%s", "A");
        }
    }
    
    //鼠标事件
    #include <QMouseEvent>
    void MainWindow::mousePressEvent(QMouseEvent *m)
    {
        QPoint pt = m->pos();
        if(m->button() == Qt::LeftButton)
        {
            printf("%s","A");
        }
    }
    ```


32. TCP客户端

    ```c
    
    ```

33. TCP服务器

    ```c
    
    ```

34. 可以实现服务器和客户端交互，传递信息

    ```
    
    ```

35. 遇到不会的函数，不确定放入什么参数，就按F1查询该函数，将对应的参数转换为对应形式的值放入

36. 函数的默认参数要放在参数列表的后面

37. 数值转换：需要研究

    ```c
    .toString() .toShort() .toInt() QString::number()
    ```

38. Mysql数据库

