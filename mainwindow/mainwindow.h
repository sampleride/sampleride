//
// Created by Flynn on 02.08.2023.
//

#ifndef SAMPLERIDE_MAINWINDOW_H
#define SAMPLERIDE_MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QDockWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QComboBox>
#include <QPushButton>
#include <QSpacerItem>
#include <QOpenGLWidget>
#include <QTabWidget>

#include "preview/preview.h"
#include "api/classes.h"
#include "model/model.h"
#include "module/manager.h"
#include "state/state.h"
#include "sequence/sequence.h"

namespace sampleride
{

    class MainWindow : public QMainWindow
    {
        Q_OBJECT
    public:
        explicit MainWindow(QWidget* parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());
    protected:
        void initToolbar(Preview* preview);

        Model _model;
        ModuleManager _manager;
        State _state;
        ColorFactory _color;
        QOpenGLWidget opengl;
        Preview* preview;
    };


} // namespace sampleride

#endif //SAMPLERIDE_MAINWINDOW_H
