### QT5教程 完整版



> 下方为教程路径地址

[QT指南](https://github.com/Nitrosaccharose/qt-learning-guide/blob/main/Qt%E6%8C%87%E5%8D%97.md)

[QT学习之路](https://www.devbean.net/2012/08/qt-study-road-2-catelog/)

[QT入门](https://subingwen.cn/qt/qt-primer/)

[CSDN教程](https://blog.csdn.net/m0_65635427/article/details/130780280?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522D4A398FD-F4BA-4351-B985-6B431FF8BEFA%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=D4A398FD-F4BA-4351-B985-6B431FF8BEFA&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~top_positive~default-1-130780280-null-null.142^v100^pc_search_result_base8&utm_term=qt&spm=1018.2226.3001.4187)

[视频教程](https://www.bilibili.com/video/BV1GW42197ff/?spm_id_from=333.337.search-card.all.click&vd_source=5cfc5f3807f31b335afa03d3ac5d692f)

------

进度：60  页

视频：C++QT2024年最新版，QT5



book_qt_2



#### QT知识点：

1. Qt 定时器使用指南：

   ## 1. Qt 定时器简介

   Qt 提供了多种定时器机制来执行定时任务，主要包括：

   - `QTimer`（最常用）
   - `QBasicTimer`
   - `QElapsedTimer`
   - `QThread::msleep()` / `QThread::usleep()`
   - `QTime`

   ## 2. QTimer 详解

   ### 2.1 QTimer 基本用法

   QTimer 是 Qt 中最常用的定时器，可以用来触发特定时间间隔的操作。

   #### **示例 1：单次定时器**

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

   #### **示例 2：周期性定时器**

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

   ### 2.2 停止定时器

   使用 `QTimer::stop()` 方法可以停止定时器。

   ```cpp
   timer->stop();
   ```

   ## 3. QBasicTimer

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

   ## 4. QElapsedTimer

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

   ## 5. QTime 计时

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

   ## 6. 线程中的定时器

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

   ## 7. 总结

   - `QTimer` 适用于大多数定时任务，支持单次和周期性触发。
   - `QBasicTimer` 适用于性能要求高的场景。
   - `QElapsedTimer` 适用于测量时间间隔。
   - `QTime` 适用于低精度计时。
   - `QThread::msleep()` 可用于线程休眠。

   合理选择定时器可以提升 Qt 应用的性能和响应速度。

2. 字符串拼接：ui->label_time->setText(QString("title%1").arg(num++));

3. 尝试使用调试程序，多使用帮助文档Assistant(查找功能)

4. 主函数写法：

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

5. exec()退出函数

6. QMessageBox::warning，QMessageBox::Yes

7. QDialog::Accepted

8. setEchoMode(QLineEdit::Password)：设置密码框

9. text().trimmed()：移除字符串开头和结尾的空白字符，tr()

10. setFocus()：设置光标显示位置

11. 解决内存占用过多的问题：

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

    ```c
    
    ```

    

39. Qt 多线程开发指南

    ## 1. 引言
    在 Qt 进行多线程编程时，可以使用 `QThread` 直接继承或移动到新线程，也可以使用 `QRunnable` 结合 `QThreadPool` 进行轻量级任务管理。本指南将介绍 Qt 多线程的基础知识，并通过示例进行讲解。

    ---

    ## 2. 使用 QThread 继承方式

    ### 2.1 QThread 介绍
    `QThread` 是 Qt 提供的线程类，通常有两种使用方式：
    - 继承 `QThread`，重写 `run()` 方法
    - 继承 `QObject`，将对象移动到 `QThread`

    ### 2.2 继承 QThread 实现线程
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

    ### 2.3 使用 QObject + QThread
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

    ## 3. 使用 QRunnable 和 QThreadPool

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

    ## 4. 线程间通信（信号与槽）
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

    ## 5. 线程管理
    ### 5.1 停止线程
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

    ## 6. 结论
    - `QThread` 适用于长期运行的线程
    - `QRunnable` + `QThreadPool` 适用于短时间任务
    - `moveToThread()` 提供更好的面向对象方式
    - `Qt::QueuedConnection` 实现线程安全的信号槽通信

    以上内容涵盖了 Qt 多线程的基础用法，可根据需求选择合适的方法。

40. QT文件操作

    ## 1. 引言
    Qt 提供了 `QFile`、`QTextStream`、`QFileInfo`、`QDir` 等类用于文件操作，支持读取、写入、删除文件，以及操作目录。

    ## 2. 读取文件内容
    ### 2.1 逐行读取文本文件
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

    ### 2.2 读取整个文件内容
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

    ## 3. 写入文件内容
    ### 3.1 覆盖写入文件
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

    ### 3.2 追加写入文件
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

    ## 4. 删除文件
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

    ## 5. 目录操作
    ### 5.1 创建目录
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

    ### 5.2 遍历目录
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

    ### 5.3 删除目录及其内容
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

    ## 6. 获取文件信息
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

    ## 7. 结论
    Qt 提供了丰富的文件操作接口，包括文件读取、写入、删除、目录操作等，使用 `QFile`、`QDir` 和 `QFileInfo` 可以方便地处理文件系统任务。

41. 

