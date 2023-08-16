#include <QApplication>
#include <QStyleFactory>

#include "mainwindow/mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    //QApplication::setStyle(QStyleFactory::create("macos"));

    sampleride::MainWindow wid(nullptr);
    wid.show();

    return QApplication::exec();
}
