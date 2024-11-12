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

#### C++知识点：

1. 命名空间：using namespace std;：允许在不显式指定std::的情况下使用std命名空间中的所有元素

2. 内联函数：inline Function，通常用于优化小型、频繁调用的函数，比如add，max等

3. Lambda表达式：

   ```c
   //捕获列表(Capture clause):用于捕获外部变量
   //参数列表(Parameters):与普通函数的参数列表类似，可以为空或包含参数列表
   //返回类型(Return type):默认auto，可以显示指定，如果只用一条返回语句，可以省略
   //函数体(Body):包含需要执行的代码
   
   //如果捕获列表和参数列表都不为空，由返回值决定
   //如果Capture clause不为引用&，函数体内不能对传入的数据进行改变
   //如果Capture clause为=，表示捕获所有变量，不需要在列表中写明
   [capture clause](parameters) -> return_type{
   	//函数体
       //可以使用捕获列表中的变量
       return expression; //可选的返回语句
   }
   //记忆：[]()->type{}
   ```

4. 指针：用于实参和形参的区分等

5. new和malloc：目前理解（new适用于C++,malloc适用于C）

6. 字符串使用：string，头文件：#include <string>

7. 字符串拼接：常用str = "new" + name + "year"；每个字符之间都要有变量

8. ：：称为作用域解析运算符，用于指定一个成员(如函数或变量)属于特定的类或命名空间

#### QT知识点：

1. 

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

