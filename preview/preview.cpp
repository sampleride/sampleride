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
            pos = event->position() - lastPos;

            pos_tr = QTransform::fromTranslate(pos.x(), pos.y());
        }

        update();
    }

    void Preview::mousePressEvent(QMouseEvent* event)
    {
        if (event->buttons() & Qt::LeftButton)
        {
            lastPos = event->position() - pos;
        }
        else if (event->buttons() & Qt::RightButton)
        {
            QPointF xy = (event->position() - pos) / scale;
            QPointF topleft = sampleride::Classes::model()->table_size().topLeft(), bottomright = sampleride::Classes::model()->table_size().bottomRight();

            if ((xy - topleft).x() >= 0 && (xy - topleft).y() >= 0 &&
                    (bottomright - xy).x() >= 0 && (bottomright - xy).y() >= 0)
            {
                std::cout << xy.x() << "; " << xy.y() << std::endl;
                serial.move(QVector3D(0, 0, 0), QVector3D(xy.x(), xy.y(), 0));
            }
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