#include "allmain.h"
#include "loadfileqss.h"
#include <QApplication>
#include <QDebug>

void customMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg) {
    Q_UNUSED(context);
    switch (type) {
    case QtDebugMsg:
        fprintf(stderr, "Debug: %s\n", msg.toLocal8Bit().constData());
        break;
    case QtWarningMsg:
        fprintf(stderr, "Warning: %s\n", msg.toLocal8Bit().constData());
        break;
    case QtCriticalMsg:
        fprintf(stderr, "Critical: %s\n", msg.toLocal8Bit().constData());
        break;
    case QtFatalMsg:
        fprintf(stderr, "Fatal: %s\n", msg.toLocal8Bit().constData());
        abort();
    }
}

int main(int argc, char *argv[])
{
    qInstallMessageHandler(customMessageHandler);
    QApplication a(argc, argv);
    LoadFileQss::setStyle("./Allthe.qss"); //加载qss 样式表，用静态方式
    AllMain w;
    w.show();

    return a.exec();
}
