//
// Created by Flynn on 02.08.2023.
//

#ifndef SAMPLERIDE_CLASSES_H
#define SAMPLERIDE_CLASSES_H

#include <QObject>

#include "model/model.h"

namespace sampleride
{
    class ModuleManager;

    class Classes : public QObject
    {
    public:
        explicit Classes(Model* m, ModuleManager* mm, QObject *parent = nullptr);

        Model* model()
        { return _model; };
        ModuleManager* modulemanager()
        { return _manager; };
    protected:
        Model* _model = nullptr;
        ModuleManager* _manager = nullptr;
    };

} // namespace sampleride

#endif //SAMPLERIDE_CLASSES_H
