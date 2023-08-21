//
// Created by Flynn on 02.08.2023.
//

#include "mainwindow.h"

namespace sampleride
{

    MainWindow::MainWindow(QWidget* parent, Qt::WindowFlags flags) : QMainWindow(parent, flags), _model(this), _manager(this),
                                                                     _state(this), _color(this)
    {
        setMinimumSize(800, 600);

        sampleride::Classes::_model = &_model;
        sampleride::Classes::_manager = &_manager;
        sampleride::Classes::_state = &_state;
        sampleride::Classes::_color = &_color;

        _manager.initModules();

        connect(&_state, &State::set_color, &_manager, &ModuleManager::set_color);

        Preview* preview = new Preview(this);
        sampleride::Classes::_preview = preview;
        connect(&_manager, SIGNAL(&ModuleManager::update_preview), preview, SLOT(&Preview::update));

        QDockWidget* sdock = new QDockWidget("Sequence", this);
        sdock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea | Qt::BottomDockWidgetArea | Qt::TopDockWidgetArea);
        sdock->setFeatures(QDockWidget::DockWidgetMovable);
        QWidget* seq = new QWidget();
        seq->setMinimumSize(200, 400);
        sdock->setWidget(seq);
        addDockWidget(Qt::LeftDockWidgetArea, sdock);

        QDockWidget* tdock = new QDockWidget("Timeline", this);
        tdock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea | Qt::BottomDockWidgetArea);
        tdock->setFeatures(QDockWidget::DockWidgetMovable);

        initToolbar(preview);

        QWidget* tl = new QWidget(this);

        tl->setMinimumSize(200, 100);
        tdock->setWidget(tl);
        addDockWidget(Qt::BottomDockWidgetArea, tdock);

        setCentralWidget(preview);
    }

    void MainWindow::initToolbar(Preview* preview)
    {
        QDockWidget* tooldock = new QDockWidget("Tools", this);
        tooldock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea | Qt::TopDockWidgetArea | Qt::BottomDockWidgetArea);
        tooldock->setFeatures(QDockWidget::NoDockWidgetFeatures);
        tooldock->setTitleBarWidget(new QWidget());

        QHBoxLayout* toolWrapper = new QHBoxLayout(this);
        QHBoxLayout* tool = new QHBoxLayout(this);

        QPushButton* home_act = new QPushButton("Home", this);
        connect(home_act, &QPushButton::clicked, preview, &Preview::home);
        QPushButton* halt_act = new QPushButton("Halt", this);
        connect(halt_act, &QPushButton::clicked, preview, &Preview::halt);

        tool->addWidget(home_act);
        tool->addWidget(halt_act);

        QSpacerItem* spacer = new QSpacerItem(40, 20, QSizePolicy::Expanding);

        tool->addSpacerItem(spacer);

        QComboBox* combo = new QComboBox(this);
        QWidget* wid = new QWidget(this);
        wid->setLayout(toolWrapper);

        toolWrapper->addWidget(combo);
        toolWrapper->addLayout(tool);

        tooldock->setWidget(wid);

        addDockWidget(Qt::TopDockWidgetArea, tooldock);
    }

} // namespace sampleride