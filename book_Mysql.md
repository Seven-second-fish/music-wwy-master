### 1.在 Ubuntu 上安装 MySQL

```
## 1. 更新软件包索引
首先，更新系统软件包：
sudo apt update
```

### 2. 安装 MySQL 服务器

使用以下命令安装 MySQL 服务器：

```
sudo apt install mysql-server -y
```

> 说明：Ubuntu 默认安装的是 `mysql-server`，它包含了 MySQL Server 和客户端等必要组件。

### 3. 启动并检查 MySQL 服务

启动 MySQL 服务并设置为开机自启：

```
sudo systemctl start mysql   # 启动 MySQL 服务
sudo systemctl enable mysql  # 设置开机自启
sudo systemctl status mysql  # 检查 MySQL 服务状态
```

如果 MySQL 正常运行，你会看到类似于：

```
Active: active (running) since ...
```

### 4. 设置 root 密码（如果没有设置）

如果你没有在安装时设置 root 密码，可以通过以下步骤设置：

1. 登录 MySQL：

   ```
   sudo mysql
   ```

2. 设置 root 密码：

   ```
   ALTER USER 'root'@'localhost' IDENTIFIED WITH mysql_native_password BY 'your_new_password';
   FLUSH PRIVILEGES;
   ```

   替换 `'your_new_password'` 为你希望设置的密码。

3. 退出 MySQL：

   ```
   EXIT;
   ```

### 5. 配置 MySQL 安全性（可选）

你可以运行 `mysql_secure_installation` 来增强 MySQL 的安全性：

```
sudo mysql_secure_installation
```

按照提示进行配置：

- 设置 root 密码（如果未设置）
- 移除匿名用户
- 禁止 root 远程登录（推荐）
- 删除测试数据库
- 刷新权限

### 6. 登录 MySQL

现在你可以使用以下命令登录 MySQL：

```
sudo mysql -u root -p
```

输入你刚刚设置的 root 密码。

### 7. 创建新用户并授权（可选）

如果你不想使用 root 用户，而是创建一个新用户，可以按照以下步骤操作：

1. 创建用户：

   ```
   CREATE USER 'myuser'@'localhost' IDENTIFIED BY 'mypassword';
   ```

2. 授权用户：

   ```
   GRANT ALL PRIVILEGES ON *.* TO 'myuser'@'localhost' WITH GRANT OPTION;
   FLUSH PRIVILEGES;
   ```

3. 使用新用户登录：

   ```
   mysql -u myuser -p
   ```

### 8. 开放远程访问（可选）

如果需要远程访问 MySQL，可以按照以下步骤操作：

1. 修改配置文件，开放远程访问：

   ```
   sudo nano /etc/mysql/mysql.conf.d/mysqld.cnf
   ```

   找到 `bind-address = 127.0.0.1`，改为：

   ```
   bind-address = 0.0.0.0
   ```

2. 重启 MySQL：

   ```
   sudo systemctl restart mysql
   ```

3. 允许远程用户访问：

   ```
   GRANT ALL PRIVILEGES ON *.* TO 'myuser'@'%' IDENTIFIED BY 'mypassword';
   FLUSH PRIVILEGES;
   ```

### 9. 卸载 MySQL（如果需要）

如果你以后不再需要 MySQL，可以卸载它：

```
sudo apt remove --purge mysql-server mysql-client mysql-common -y
sudo rm -rf /etc/mysql /var/lib/mysql
sudo apt autoremove -y
```

### 10. 关闭默认Mysql默认启动

```bash
sudo systemctl disable mysql   //禁用
sudo systemctl enable mysql  //启用
systemctl is-enabled mysql   //查看是否禁用
```



## 常见问题

### 1. 如何查看 MySQL 版本？

```
mysql --version
```

### 2. 如何检查 MySQL 启动日志？

```
sudo journalctl -xeu mysql
```

### 3. 如何重置 MySQL root 密码？

```
sudo mysql
ALTER USER 'root'@'localhost' IDENTIFIED WITH mysql_native_password BY 'newpassword';
FLUSH PRIVILEGES;

这样你就可以按照上述步骤在 Ubuntu 上安装并配置 MySQL 了！
```





# Qt 连接 MySQL 教程

## **1. 前置准备**

在 Qt 中使用 MySQL 需要以下环境：

- Qt 安装（建议 Qt 5 或 Qt 6）
- MySQL 数据库（确保 MySQL Server 正常运行）
- MySQL 连接驱动

### **安装 MySQL 连接驱动（Ubuntu）**

```bash
sudo apt update
sudo apt install libqt5sql5-mysql # Qt 5
sudo apt install libqt6sql6-mysql # Qt 6
```

### **安装 MySQL 连接驱动（Windows）**

如果是 Windows，你可能需要手动下载 `qsqlmysql.dll` 并将其放入 Qt 目录（如 `C:\Qt\5.x.x\mingwxx_64\plugins\sqldrivers`）。

## **2. 在 Qt 项目中使用 MySQL**

### **（1）. pro 文件配置**

在 `.pro` 文件中添加 SQL 模块支持：

```pro
QT += sql
```

### **（2）. 代码示例**

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

## **3. 在 Qt UI 中显示 MySQL 数据**

### **（1）. 在 Qt Designer 中添加控件**

- 打开 Qt Designer。
- 添加一个 `QTableView` 控件到 UI 界面。
- 在代码中获取 `QTableView` 组件的对象。

### **（2）. 使用 `QSqlTableModel` 绑定数据**

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

## **4. 运行程序**

### **（1）. 启动 MySQL 服务器**

```bash
sudo systemctl start mysql
```

### **（2）. 运行 Qt 项目**

编译并运行 Qt 代码，观察终端输出。

## **5. 可能遇到的问题及解决方案**

### **（1）. 无法加载 QMYSQL 驱动**

**错误信息：**

```
QSqlDatabase: QMYSQL driver not loaded
```

**解决方案：**

1. 确保已安装 `libqt5sql5-mysql`（Linux）或 `qsqlmysql.dll`（Windows）。
2. 确保 `mysqlclient.dll` 或 `libmysqlclient.so` 在 `PATH` 环境变量中。

### **（2）. 连接失败（认证方式问题）**

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

### **总结**

- **安装 MySQL 驱动**（`libqt5sql5-mysql` / `qsqlmysql.dll`）。
- **在 Qt 项目中配置 `.pro` 文件**。
- **使用 `QSqlDatabase` 连接 MySQL 并执行 SQL 语句**。
- **在 `QTableView` 中显示 MySQL 数据**。
- **排查 `QMYSQL` 驱动问题和数据库权限问题**。
