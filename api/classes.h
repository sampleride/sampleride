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

    class Classes : public QObject
    {
    public:
        explicit Classes(QObject *parent = nullptr);

        static Model* model()
        { return _model; };
        static ModuleManager* modulemanager()
        { return _manager; };
    protected:
        static Model* _model;
        static ModuleManager* _manager;

        friend MainWindow;
    };

} // namespace sampleride

#endif //SAMPLERIDE_CLASSES_H
