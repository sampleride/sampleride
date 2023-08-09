//
// Created by Flynn on 02.08.2023.
//

#include "model.h"

namespace sampleride
{

    Model::Model(QObject *parent) : QObject(parent), _base_size(350, 350), _table_size(10, 10, 500, 500),
    _module_size(100, 70), _module_spacing(5, 5)
    {

    }

    Model::~Model() noexcept
    {

    }

} // namespace sampleride