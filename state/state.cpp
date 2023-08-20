//
// Created by Flynn on 20.08.2023.
//

#include "state.h"

namespace sampleride
{

    State::State(QObject* parent) : QObject(parent), module_select(-1, -1), tray_select(-1, -1), module_hover(-1, -1), tray_hover(-1, -1)
    {

    }

} // namespace sampleride