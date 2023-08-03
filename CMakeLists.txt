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
)
add_executable(sampleride main.cpp renderer/renderer.h renderer/renderer.cpp model/model.h model/model.cpp
        preview/preview.cpp preview/preview.h api/classes.h api/classes.cpp mainwindow/mainwindow.h mainwindow/mainwindow.cpp
        module/module.cpp
        module/module.h
        module/manager.cpp
        module/manager.h)
target_link_libraries(sampleride PRIVATE
  Qt::Core
  Qt::Gui
  Qt::Widgets
  Qt::OpenGL
  Qt::OpenGLWidgets
)

