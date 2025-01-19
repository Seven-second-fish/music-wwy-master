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

1. QObject定时器：int start_time = this->startTimer(3000);，this->killTimer(start_time);

2. QTimer定时器：

   ```c
   QTimer *start_timer = new QTimer()，
   //每3秒钟调用一次timeroutslot函数：
   connect(start_timer,&QTimer::timeout,this,&MainWindow::timeroutslot);
   start_timer->start(3000)
   start_timer->stop();
   //等一秒钟后触发timeroutslot函数：
   QTimer::singleShot(1000,this,SLOT(timeroutslot()))
   ```

3. 字符串拼接：ui->label_time->setText(QString("title%1").arg(num++));

4. 文件功能：

   ```c++
   QString filename = QFileDialog::getOpenFileName(this,"choose","path","*.cpp");
   if(filename.isEmpty())
   {
       QMessageBox::waring(this,"警告"，"请选择一个文件")；
   }else{
       QFile file(filename);
       file.open(QIODevice::ReadOnly);
       QByteArray ba = file.readAll();
       ui->textEdit->setText(QString(ba));
       file.close();
   }
   ```

5. 尝试使用调试程序，多使用帮助文档Assistant(查找功能)

6. 主函数写法：

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

7. exec()退出函数

8. QMessageBox::warning，QMessageBox::Yes

9. QDialog::Accepted

10. setEchoMode(QLineEdit::Password)：设置密码框

11. text().trimmed()：移除字符串开头和结尾的空白字符，tr()

12. setFocus()：设置光标显示位置

13. 解决内存占用过多的问题：

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


32. 
=======
32. TCP客户端

    ```c
    //需要连接Tcp服务器，阿里云服务器
    
    //.pro文件添加
    QT += core gui network
    //.h文件
    #include <QTcpSocket>
    #include <QHostAddress>
    //.cpp
    QTcpSocket *m_socket = new QTcpSocket;
    QString IP = ui->label_s1->text();
    QString port = ui->label_s2->text();
    //连接服务器
    m_socket->connectToHost(QHostAddress(IP),port.toShort());
    //连接成功
    connect(m_socket,&QTcpSocket::connected,[this](){
        QMessageBox::information(this,"con","2");
    });
    //连接断开
    connect(m_socket,&QTcpSocket::disconnected,[this](){
        QMessageBox::information(this,"dis","0");
    });
    ```

    

33. TCP服务器

    ```c
    //.h文件
    #include <QTcpServer>
    //.cpp
    QTcpServer *server = new QTcpServer;
    //监听
    server->listen(QHostAddress::AnyIPv4, PORT)
    //客户端发起连接，server发出信号
    connect(server,&QTcpServer:newConnection,this,&Widget::newClientHandler);
    void Widget::newClientHandler()
    {
    	//建立TCP连接
    	QTcpSocket *socket = server->nextPendingConnection()
    	//socket->peerAddress();   //获取客户端地址
    	//socket->peerPort();      //获取客户端的端口号
    }
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

    

39. 

