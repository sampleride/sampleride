//
// Created by Flynn on 02.08.2023.
//

#include "preview.h"

namespace sampleride
{

    Preview::Preview(QWidget* parent) : QWidget(parent), scale(1.1)
    {
        setMinimumSize(QSize(sampleride::Classes::model()->base_size().x(), sampleride::Classes::model()->base_size().y()));
        //setStyleSheet("background-color: #ffffff;");
        QPalette pal = QPalette();
        pal.setColor(QPalette::Window, QColor(10, 10, 10));
        setAutoFillBackground(true);
        setPalette(pal);

        scale_tr = scale_tr.scale(1.1, 1.1);
    }

    void Preview::paintEvent(QPaintEvent* event)
    {
        QPainter qp(this);
        qp.setRenderHint(QPainter::Antialiasing);

        qp.setViewTransformEnabled(true);

        qp.setTransform(scale_tr * pos_tr);

        qp.setPen(QPen());
        qp.setBrush(QBrush(QColor(40, 40, 40)));

        qp.drawRect(sampleride::Classes::model()->table_size());

        for (Module* m : sampleride::Classes::modulemanager()->modules)
        {
            m->draw_preview(&qp);
        }
    }

    void Preview::mouseMoveEvent(QMouseEvent* event)
    {
        if (event->buttons() & Qt::LeftButton)
        {
            if (lastPos.x() - event->position().x() > 0)
                pos.setX(pos.x() - event->position().x() / 100);
            else
                pos.setX(pos.x() + event->position().x() / 100);

            if (lastPos.y() - event->position().y() > 0)
                pos.setY(pos.y() - event->position().y() / 100);
            else
                pos.setY(pos.y() + event->position().y() / 100);

            pos_tr = QTransform::fromTranslate(pos.x(), pos.y());
        }

        update();
    }

    void Preview::mousePressEvent(QMouseEvent* event)
    {
        if (event->buttons() & Qt::LeftButton)
        {
            lastPos = event->position();
        }
    }

    void Preview::wheelEvent(QWheelEvent* event)
    {
        QPoint pix = event->pixelDelta();
        QPoint deg = event->angleDelta();

        if (!pix.isNull())
        {
            scale = std::fmax(0.6, std::fmin(scale + float(pix.y()) / 600, 1.7));
            scale_tr = QTransform::fromScale(scale, scale);
        }
        else if (!deg.isNull())
        {
            scale = std::fmax(0.6, std::fmin(scale + float(deg.y()) / 600, 1.7));
            scale_tr = QTransform::fromScale(scale, scale);
        }

        event->accept();

        update();
    }
} // namespace sampleride