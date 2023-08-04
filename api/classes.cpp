//
// Created by Flynn on 02.08.2023.
//

#include "classes.h"

namespace sampleride
{
    Classes::Classes(QObject *parent) : QObject(parent)
    {

    }

    Model* Classes::_model = nullptr;
    ModuleManager* Classes::_manager = nullptr;

} // namespace sampleride