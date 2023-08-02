//
// Created by Flynn on 02.08.2023.
//

#include "preview.h"

namespace sampleride
{

    Preview::Preview(QWidget* parent, Classes* _classes) : QWidget(parent)
    {
        classes = _classes;
        QPainter qp(this);
    }
} // namespace sampleride