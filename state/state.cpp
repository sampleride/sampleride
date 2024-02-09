//
// Created by Flynn on 20.08.2023.
//

#include "state.h"

namespace sampleride
{
    QPoint State::none_pos = QPoint(-1, -1);

    State::State(QObject* parent) : QObject(parent), module_select(none_pos), module_hover(none_pos), comp_hover(none_pos)
    {

    }

    void State::set_selection()
    {
        if (module_select != none_pos)
            emit set_color(module_select, ColorTypes::FG);
        module_select = none_pos;

        comp_hover = none_pos;
        comp_select.clear();
        emit update_preview();
    }

    void State::set_comp_hover(QPoint comp)
    {
        if (module_hover != none_pos && comp_hover != comp)
            emit set_color(module_hover, ColorTypes::FG_COMP_HOVER);
        comp_hover = comp;
    }

    void State::set_comp_selection(QPoint comp)
    {
        comp_select.insert(comp);
        update_preview();
    }

    void State::unset_comp_selection(QPoint comp)
    {
        comp_select.remove(comp);
        update_preview();
    }

    void State::set_comp_hover()
    {
        comp_hover = none_pos;
        update_preview();
    }

    void State::set_hover(QPoint module)
    {
        if (module_hover != none_pos && module_hover != module_select && module_hover != module)
            emit set_color(module_hover, ColorTypes::FG);
        module_hover = module;
        if (module_hover != none_pos && module_hover != module_select)
            emit set_color(module_hover, ColorTypes::FG_HOVER);
    }

    void State::set_hover()
    {
        if (module_hover != none_pos && module_hover != module_select)
            emit set_color(module_hover, ColorTypes::FG);
        module_hover = none_pos;
    }

    void State::set_selection(QPoint module)
    {
        if (module_select != none_pos && module_hover != module)
            emit set_color(module_select, ColorTypes::FG);

        if (module_select != module)
        {
            comp_select.clear();
            comp_hover = none_pos;
        }

        module_select = module;
        if (module_select != none_pos)
            emit set_color(module_select, ColorTypes::FG_SELECT);
    }

    void State::set_comp_selection()
    {
        comp_select.clear();
    }

} // namespace sampleride