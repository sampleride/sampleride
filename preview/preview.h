//
// Created by Flynn on 02.08.2023.
//

#ifndef SAMPLERIDE_PREVIEW_H
#define SAMPLERIDE_PREVIEW_H

#include <QPainter>
#include <QWidget>

#include "api/classes.h"

namespace sampleride
{

    class Preview : public QWidget {
    public:
        explicit Preview(QWidget* parent = nullptr, Classes* _classes = nullptr);

    protected:
        Classes* classes = nullptr;
        QPainter qp;
    };

} // namespace sampleride

#endif //SAMPLERIDE_PREVIEW_H
