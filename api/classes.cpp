//
// Created by Flynn on 02.08.2023.
//

#include "classes.h"

namespace sampleride
{
    Classes::Classes(Model* m, ModuleManager* mm, QObject *parent) : QObject(parent), _model(m), _manager(mm)
    {

    }

} // namespace sampleride