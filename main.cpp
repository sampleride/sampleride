#include <QApplication>
#include <QPushButton>

#include "renderer/renderer.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    s_preview::Renderer renderer;
    renderer.show();
    return QApplication::exec();
}
