//
// Created by flynn on 8/3/23.
//

#include "manager.h"

namespace sampleride
{

    sampleride::ModuleManager::ModuleManager(QObject* parent) : QObject(parent)
    {

    }

    Module* ModuleManager::getModule(int id)
    {
        return modules[id];
    }

    void ModuleManager::initModules()
    {
        SimpleTray* tray = new SimpleTray(this);
        Module* mod = qobject_cast<Module*>(tray);

        if (!mod)
        {
            // could not cast
        }
        modules[tray->_id] = mod;
        module_pos[tray->_model._pos] = mod;
    }

} // namespace sampleride