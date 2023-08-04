//
// Created by Flynn on 02.08.2023.
//

#ifndef SAMPLERIDE_PREVIEW_H
#define SAMPLERIDE_PREVIEW_H

#include <QPainter>
#include <QWidget>

#include "api/classes.h"
#include "module/manager.h"
#include "model/model.h"

namespace sampleride
{
    class Module;

    class Preview : public QWidget {
        Q_OBJECT
    public:
        explicit Preview(QWidget* parent = nullptr);
    protected:
        void paintEvent(QPaintEvent* event) override;
    };

} // namespace sampleride

#endif //SAMPLERIDE_PREVIEW_H
