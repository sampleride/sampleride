cmake_minimum_required(VERSION 3.25)
project(sampleride)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

include_directories(.)

find_package(Qt6 COMPONENTS
  Core
  Gui
  Widgets
  REQUIRED COMPONENTS
  OpenGL
  OpenGLWidgets
  SerialPort
)
add_executable(sampleride
        main.cpp
        model/model.h
        model/model.cpp
        preview/preview.cpp
        preview/preview.h
        api/classes.h
        api/classes.cpp
        api/enums.h
        mainwindow/mainwindow.h
        mainwindow/mainwindow.cpp
        module/module.cpp
        module/module.h
        module/manager.cpp
        module/manager.h
        server/server.cpp
        server/server.h
        state/state.h
        state/state.cpp
        sequence/sequence.cpp
        sequence/sequence.h
        sequence/action.cpp
        sequence/action.h
        resources/style.h)
target_link_libraries(sampleride PRIVATE
  Qt::Core
  Qt::Gui
  Qt::Widgets
  Qt::OpenGL
  Qt::OpenGLWidgets
  Qt::SerialPort
)

