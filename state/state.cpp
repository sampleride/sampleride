//
// Created by Flynn on 20.08.2023.
//

#include "state.h"

namespace sampleride
{
    QPoint State::none_pos = QPoint(-1, -1);

    State::State(QObject* parent) : QObject(parent), module_select(none_pos), tray_select(none_pos), module_hover(none_pos), tray_hover(none_pos)
    {

    }

    void State::set_selection()
    {
        if (module_select != none_pos)
            emit set_color(module_select, ColorTypes::FG);
        module_select = none_pos;
        tray_select = none_pos;
    }

    void State::set_hover(QPoint module, QPoint tray)
    {
        if (module_hover != none_pos && module_hover != module_select)
            emit set_color(module_hover, ColorTypes::FG);
        module_hover = module;
        tray_hover = tray;
        if (module_hover != none_pos && module_hover != module_select)
            emit set_color(module_hover, ColorTypes::FG_HOVER);
    }

    void State::set_hover()
    {
        if (module_hover != none_pos && module_hover != module_select)
            emit set_color(module_hover, ColorTypes::FG);
        module_hover = none_pos;
        tray_hover = none_pos;
    }

    void State::set_selection(QPoint module, QPoint tray)
    {
        if (module_select != none_pos)
            emit set_color(module_select, ColorTypes::FG);
        module_select = module;
        tray_select = tray;
        if (module_select != none_pos)
            emit set_color(module_select, ColorTypes::FG_SELECT);
    }

} // namespace sampleride