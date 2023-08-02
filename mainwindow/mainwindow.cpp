//
// Created by Flynn on 02.08.2023.
//

#include "mainwindow.h"

namespace sampleride
{

    MainWindow::MainWindow(QWidget* parent, Qt::WindowFlags flags) : QMainWindow(parent, flags)
    {
        Classes _classes(&_model, this);
        Preview preview(this, &_classes);

        QDockWidget *dock = new QDockWidget("Dock", this);
        dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea | Qt::BottomDockWidgetArea);
        dock->setWidget(new QWidget());
        addDockWidget(Qt::LeftDockWidgetArea, dock);

        setCentralWidget(&preview);
    }

} // namespace sampleride