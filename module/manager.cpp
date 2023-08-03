//
// Created by flynn on 8/3/23.
//

#include "manager.h"

namespace sampleride
{

    sampleride::ModuleManager::ModuleManager(QObject* parent, Classes* _classes) : QObject(parent), classes(_classes)
    {
        SimpleTray* tray = new SimpleTray(this, classes);
        Module* mod = qobject_cast<Module*>(tray);

        if (!mod)
        {
            // could not cast
        }
        modules[tray->_id] = mod;
    }

    Module* ModuleManager::getModule(int id)
    {
        return modules[id];
    }

} // namespace sampleride