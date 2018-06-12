#include "mainwindow.h"
#include <QApplication>
#include <QIcon>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString strpath = QApplication::applicationDirPath();
    strpath += "/icon.ico";

    MainWindow w;
    w.setWindowTitle(QStringLiteral("萌新的串口调试工具"));
    a.setWindowIcon(QIcon(strpath));
    w.show();

    return a.exec();
}
