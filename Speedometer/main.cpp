#include "speedometer.h"

#include <QApplication>
#include <QVBoxLayout>
#include <QSlider>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Speedometer w;
    w.show();
    return a.exec();
}
