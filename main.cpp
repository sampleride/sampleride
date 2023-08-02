#include <QApplication>
#include <QPushButton>

#include "mainwindow/mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    sampleride::MainWindow wid;
    wid.show();

    return QApplication::exec();
}
