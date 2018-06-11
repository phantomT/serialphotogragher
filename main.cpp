#include "mainwindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("萌新的串口调试工具");
    QIcon icon(":/serial_icon.ico");
    w.setWindowIcon(icon);
    w.show();

    return a.exec();
}
