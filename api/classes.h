//
// Created by Flynn on 02.08.2023.
//

#ifndef SAMPLERIDE_CLASSES_H
#define SAMPLERIDE_CLASSES_H

#include <QObject>

namespace sampleride
{
    class ModuleManager;
    class Model;
    class MainWindow;
    class State;
    class ColorFactory;
    class Preview;

    class Classes : public QObject
    {
    public:
        explicit Classes(QObject *parent = nullptr);

        static Model* model()
        { return _model; };
        static ModuleManager* modulemanager()
        { return _manager; };
        static State* state()
        { return _state; }
        static ColorFactory* color()
        { return _color; }
        static Preview* preview()
        { return _preview; }
    protected:
        static Model* _model;
        static ModuleManager* _manager;
        static State* _state;
        static ColorFactory* _color;
        static Preview* _preview;

        friend MainWindow;
    };

} // namespace sampleride

#endif //SAMPLERIDE_CLASSES_H
