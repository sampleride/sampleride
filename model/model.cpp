//
// Created by Flynn on 02.08.2023.
//

#include "model.h"

namespace sampleride
{

    Model::Model(QWidget *parent) : QWidget(parent)
    {
        _base_size = QPointF(350, 350);
        _table_size = QRectF(10, 10, 300, 300);
        _module_size = QPointF(50, 100);
        _module_spacing = QPointF(5, 5);
    }

    Model::~Model() noexcept
    {

    }

} // namespace sampleride