QT5教程 完整版

+[QT指南]https://github.com/Nitrosaccharose/qt-learning-guide/blob/main/Qt%E6%8C%87%E5%8D%97.md

+[QT学习之路]https://www.devbean.net/2012/08/qt-study-road-2-catelog/

进度：60  页

整理：

1. 尝试使用调试程序，多使用帮助文档Assistant(查找功能)

2. 主函数写法：

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

3. exec()退出函数

4. QMessageBox::warning，QMessageBox::Yes

5. QDialog::Accepted

6. setEchoMode(QLineEdit::Password)：设置密码框

7. text().trimmed()：移除字符串开头和结尾的空白字符，tr()

8. setFocus()：设置光标显示位置

9. 解决内存占用过多的问题：

   **延迟加载（懒加载）** 

   只在需要时才创建页面实例。你可以在用户第一次访问某个页面时动态加载和初始化该页面，而不是在启动时一次性加载所有页面。

   **资源回收（惰性卸载）**

   当页面不再需要时，你可以卸载或释放这些页面以回收内存。这样做可以减少内存占用。

   **按需加载与卸载**

   你可以在切换页面时按需加载和卸载页面。这样做可以在用户访问页面时才创建实例，切换到其他页面时释放不需要的页面。

10. message：tr("%1,%2").arg(text1).agr(text2)

11. 在使用如下函数时，对于默认组件，比如QPushButton等，实现点击可调用clicked()默认函数，不能自定义点击函数，也没必要。槽函数可调用本类的函数或者一个发到其他类的信号

    ```
    connect(ui->pushButton_min, SIGNAL(clicked()), this, SLOT(btn_bkg_min()));
    ```

12. 引用\#include <QSqlDatabase>需要加QT += sql

13. 推荐使用.qss文件统一管理样式，比如引入图片等

14. 判断组件存在并设置其显示隐藏基本流程

    volume_slider = this->findChild<QSlider *>("volumeSlider");

    if(volume_slider && volume_slider->isVisible()){

    volume_slider->hide();

    }else{

    volume_slider->show();

    }

15. 旧的信号槽：信号signal与槽机制slot不支持传递参数，

     新的信号槽：使用 Lambda 表达式，提供了更大的灵活性，允许传递额外的参数并确保信号和槽的匹配在编译时检查，比如true，false等

16. 如果槽函数需要传递按钮状态，使用 QPushButton::toggled 信号。如果槽函数不需要传递参数，使用 QPushButton::clicked 信号。

17. lambda表达式使用

    ```c
    ##目前理解
    connect(ui->btnPlayPause, &QPushButton::toggled, [this](bool checked){
            checked?player->play():player->pause();
        });
    ```

18. 条件表达式
    if(a>b) max=a; else max=b;
    可用条件表达式写为 max=(a>b)?a:b;

    其中：

    1. max=(a>b)?a:b 可以去掉括号而写为 max=a>b?a:b

    2. ?和：是一对运算符，不能分开

    3. 运算符的结合方向是自右向左

       a>b?a:c>d?c:d 应理解为 a>b?a:(c>d?c:d)

19. Q_OBJECT

    必须在附属类的头文件中加入这个宏

    这个宏的展开将为我们的类提供信号槽机制、国际化机制以及 Qt 提供的不基于 C++ RTTI 的反射能力

20. QT基本模块

    目前使用了：Qt Core，Qt Gui

21. 如果 Qt 的主版本号（`QT_MAJOR_VERSION`）大于 4，也就是 Qt 5，需要在.pro文件加上

    `greaterThan**(**QT_MAJOR_VERSION, 4**)**: QT += widgets`

22. QKeySequence

    使用了`setShortcut()`函数，用于说明这个`QAction`的快捷键

23. 

