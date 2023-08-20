//
// Created by flynn on 8/3/23.
//

#ifndef SAMPLERIDE_MANAGER_H
#define SAMPLERIDE_MANAGER_H

#include <QObject>
#include <QHash>

#include "api/classes.h"
#include "module/module.h"

namespace sampleride
{

    class ModuleManager : public QObject
    {
        Q_OBJECT
    public:
        explicit ModuleManager(QObject* parent = nullptr);
        void initModules();
        Module* getModule(int id);

        QHash<int, Module*> modules;
        QHash<QPoint, Module*> module_pos;
    };

} // namespace sampleride

#endif //SAMPLERIDE_MANAGER_H
