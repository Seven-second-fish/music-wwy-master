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

9. 
