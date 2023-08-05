//
// Created by Flynn on 02.08.2023.
//

#ifndef SAMPLERIDE_PREVIEW_H
#define SAMPLERIDE_PREVIEW_H

#include <QPainter>
#include <QWidget>
#include <QTransform>
#include <QMouseEvent>
#include <cmath>

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
        void mousePressEvent(QMouseEvent* event) override;
        void mouseMoveEvent(QMouseEvent* event) override;
        void wheelEvent(QWheelEvent* event) override;

        QTransform scale_tr;
        QTransform pos_tr;
        float scale;
        QPointF pos;
        QPointF lastPos;
    };

} // namespace sampleride

#endif //SAMPLERIDE_PREVIEW_H
