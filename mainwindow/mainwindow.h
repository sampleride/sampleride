//
// Created by Flynn on 02.08.2023.
//

#ifndef SAMPLERIDE_MAINWINDOW_H
#define SAMPLERIDE_MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QDockWidget>

#include "preview/preview.h"
#include "api/classes.h"
#include "model/model.h"

namespace sampleride
{

    class MainWindow : public QMainWindow
    {
    public:
        explicit MainWindow(QWidget* parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());

    protected:
        Model _model;
        Classes _classes;
    };


} // namespace sampleride

#endif //SAMPLERIDE_MAINWINDOW_H
