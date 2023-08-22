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

#include <iostream>

#include "api/classes.h"
#include "module/manager.h"
#include "model/model.h"
#include "server/server.h"
#include "state/state.h"

namespace sampleride
{
    class Module;

    class Preview : public QWidget {
        Q_OBJECT
    public:
        explicit Preview(QWidget* parent = nullptr);
    public slots:
        void home();
        void halt();
        void repaint_canvas();
    protected:
        void paintEvent(QPaintEvent* event) override;
        void mousePressEvent(QMouseEvent* event) override;
        void mouseReleaseEvent(QMouseEvent* event) override;
        void mouseMoveEvent(QMouseEvent* event) override;
        void wheelEvent(QWheelEvent* event) override;

        bool event2pos(QPointF& click_pos) const;
        bool event2module(QPointF& click_pos) const;

        QTransform scale_tr;
        QTransform pos_tr;
        float scale;
        QPointF pos;
        QPointF lastPos;
        QPointF pos_old;
        SamSerial serial;
    };

} // namespace sampleride

#endif //SAMPLERIDE_PREVIEW_H
