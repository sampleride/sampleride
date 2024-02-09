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
        // TODO load from config
        SimpleTray* tray = new SimpleTray(this);
        tray->_id = 0;
        Module* mod = qobject_cast<Module*>(tray);

        if (!mod)
        {
            // could not cast
        }
        // TODO add runtime id management
        modules[tray->_id] = mod;
        module_pos[tray->_model._pos] = mod;
        sampleride::Classes::color()->module_map.insert(tray->_id, 0);
        mod->_color = sampleride::Classes::color()->getColor(tray->_id, ColorTypes::FG);
        sampleride::Classes::color()->used_colors++;
    }

    void ModuleManager::set_color(QPoint module, ColorTypes col)
    {
        if (!module_pos.contains(module))
            return;
        Module* mod = module_pos[module];
        QColor* new_color = sampleride::Classes::color()->getColor(mod->_id, col);
        if (mod->_color != new_color)
        {
            if (col == ColorTypes::FG || col == ColorTypes::FG_HOVER || col == ColorTypes::FG_SELECT)
                mod->_color = new_color;
            emit update_preview();
        }
    }

    bool ModuleManager::same_module(int id, QPoint rhs)
    {
        if (module_pos.contains(rhs) && module_pos[rhs]->_id == id)
        {
            return true;
        }
        return false;
    }

    ColorFactory::ColorFactory(QObject* parent) : QObject(parent), used_colors(0), _palette({new QColor(44, 209, 35)})
    {
        for (QColor* col : _palette)
        {
            _hover.push_back(new QColor(col->toHsl().lighter(125)));
            _select.push_back(new QColor(col->toHsl().lighter(175)));
            _comp_hover.push_back(new QColor(col->toHsl().lighter(200)));
            _comp_select.push_back(new QColor(col->toHsl().lighter(250)));
        }
    }

    QColor* ColorFactory::getColor(int id, ColorTypes type)
    {
        switch(type)
        {
            case ColorTypes::FG:
                return _palette[module_map[id]];
            case ColorTypes::FG_HOVER:
                return _hover[module_map[id]];
            case ColorTypes::FG_SELECT:
                return _select[module_map[id]];
            case ColorTypes::FG_COMP_HOVER:
                return _comp_hover[module_map[id]];
            case ColorTypes::FG_COMP_SELECT:
                return _comp_select[module_map[id]];
        }
        return _palette[module_map[id]];
    }

} // namespace sampleride