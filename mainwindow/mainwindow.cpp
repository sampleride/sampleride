//
// Created by Flynn on 02.08.2023.
//

#include "mainwindow.h"

namespace sampleride
{

    MainWindow::MainWindow(QWidget* parent, Qt::WindowFlags flags) : QMainWindow(parent, flags), _model(this), _classes(&_model, this)
    {
        setMinimumSize(800, 600);

        Preview* preview = new Preview(this, &_classes);

        QDockWidget *sdock = new QDockWidget("Sequence", this);
        sdock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea | Qt::BottomDockWidgetArea | Qt::TopDockWidgetArea);
        sdock->setFeatures(QDockWidget::DockWidgetMovable);
        QWidget* seq = new QWidget();
        seq->setMinimumSize(200, 400);
        sdock->setWidget(seq);
        addDockWidget(Qt::LeftDockWidgetArea, sdock);

        QDockWidget *tdock = new QDockWidget("Timeline", this);
        tdock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea | Qt::BottomDockWidgetArea);
        tdock->setFeatures(QDockWidget::DockWidgetMovable);
        QWidget* tl = new QWidget();
        tl->setMinimumSize(200, 100);
        tdock->setWidget(tl);
        addDockWidget(Qt::BottomDockWidgetArea, tdock);

        setCentralWidget(preview);
    }

} // namespace sampleride