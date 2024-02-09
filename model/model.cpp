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

    float Model::map(float value, float in_min, float in_max, float out_min, float out_max)
    {
        return out_min + (out_max - out_min) * ((value - in_min) / (in_max - in_min));
    }

} // namespace sampleride