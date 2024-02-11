//
// Created by Flynn on 02.08.2023.
//

#include "mainwindow.h"

namespace sampleride
{

    MainWindow::MainWindow(QWidget* parent, Qt::WindowFlags flags) : QMainWindow(parent, flags), _model(this), _manager(this),
                                                                     _state(this), _color(this), opengl(this)
    {
        setMinimumSize(800, 600);

        sampleride::Classes::_model = &_model;
        sampleride::Classes::_manager = &_manager;
        sampleride::Classes::_state = &_state;
        sampleride::Classes::_color = &_color;

        _manager.initModules();

        connect(&_state, &State::set_color, &_manager, &ModuleManager::set_color);

        preview = new Preview(this);
        sampleride::Classes::_preview = preview;
        connect(&_manager, &ModuleManager::update_preview, preview, &Preview::repaint_canvas);
        connect(&_state, &State::update_preview, preview, &Preview::repaint_canvas);

        QDockWidget* sdock = new QDockWidget("Sequence", this);
        sdock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea | Qt::BottomDockWidgetArea | Qt::TopDockWidgetArea);
        sdock->setFeatures(QDockWidget::DockWidgetMovable);
        Sequence* seq = new Sequence(this);
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

        QHBoxLayout* opengl_lay = new QHBoxLayout(this);
        opengl_lay->setContentsMargins(0, 0, 0, 0);
        opengl_lay->addWidget(preview);
        opengl.setLayout(opengl_lay);
        setCentralWidget(&opengl);
    }

    void MainWindow::initToolbar(Preview* preview)
    {
        QDockWidget* tooldock = new QDockWidget("Tools", this);
        tooldock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea | Qt::TopDockWidgetArea | Qt::BottomDockWidgetArea);
        tooldock->setFeatures(QDockWidget::NoDockWidgetFeatures);
        tooldock->setTitleBarWidget(new QWidget(this));

        //QHBoxLayout* toolWrapper = new QHBoxLayout(this);
        auto bar = new QTabWidget(this);
        QHBoxLayout* tool = new QHBoxLayout(this);

        QPushButton* home_act = new QPushButton("Home", this);
        connect(home_act, &QPushButton::clicked, preview, &Preview::home);
        QPushButton* halt_act = new QPushButton("Halt", this);
        connect(halt_act, &QPushButton::clicked, preview, &Preview::halt);

        tool->addWidget(home_act);
        tool->addWidget(halt_act);

        QSpacerItem* spacer = new QSpacerItem(40, 20, QSizePolicy::Expanding);

        tool->addSpacerItem(spacer);

        QWidget* wid = new QWidget(this);
        wid->setLayout(tool);
        bar->addTab(wid, "Movement");

        // Initialize execution tab
        QHBoxLayout* tool2 = new QHBoxLayout(this);
        auto cmp_btn = new QPushButton("Compile", this);
        auto run_btn = new QPushButton("Run", this);
        tool2->addWidget(cmp_btn);
        tool2->addWidget(run_btn);

        QSpacerItem* spacer2 = new QSpacerItem(40, 20, QSizePolicy::Expanding);
        tool2->addSpacerItem(spacer2);

        auto wid2 = new QWidget(this);
        wid2->setLayout(tool2);
        bar->addTab(wid2, "Code");

        tooldock->setWidget(bar);

        addDockWidget(Qt::TopDockWidgetArea, tooldock);
    }

} // namespace sampleride