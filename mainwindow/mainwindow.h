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

#include "preview/preview.h"
#include "api/classes.h"
#include "model/model.h"
#include "module/manager.h"
#include "state/state.h"

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
    };


} // namespace sampleride

#endif //SAMPLERIDE_MAINWINDOW_H
