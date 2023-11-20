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
        setMouseTracking(true);

        scale_tr = scale_tr.scale(1.1, 1.1);
        std::srand(std::time(nullptr));
    }

    void Preview::paintEvent(QPaintEvent* event)
    {
        //std::cout << ".";
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

            update();
        }
        else
        {
            QPointF m_pos = event->position();
            if (event2module(m_pos))
            {
                QPoint module(int(m_pos.x()), int(m_pos.y()));

                if (sampleride::Classes::modulemanager()->module_pos.contains(module))
                {
                    sampleride::Classes::state()->set_hover(module);
                    event2modulesize(m_pos);
                    sampleride::Classes::modulemanager()->module_pos[module]->_model.hover(m_pos);
                    return;
                }
            }
            sampleride::Classes::state()->set_hover();
            sampleride::Classes::state()->set_comp_hover();
        }
    }

    void Preview::mousePressEvent(QMouseEvent* event)
    {
        if (event->buttons() & Qt::LeftButton)
        {
            lastPos = event->position() - pos;
            pos_old = pos;
        }
        else if (event->buttons() & Qt::RightButton)
        {
            QPointF xy = event->position();
            if (event2pos(xy))
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

    void Preview::home()
    {
        serial.home();
    }

    void Preview::halt()
    {
        serial.halt();
    }

    void Preview::mouseReleaseEvent(QMouseEvent* event)
    {
        // Check if there was no drag
        if (pos == pos_old)
        {
            QPointF m_pos = event->position();
            if (event2module(m_pos))
            {
                QPoint module(int(m_pos.x()), int(m_pos.y()));

                if (sampleride::Classes::modulemanager()->module_pos.contains(module))
                {
                    sampleride::Classes::state()->set_selection(module);
                    return;
                }
            }
            sampleride::Classes::state()->set_selection();
        }
    }

    bool Preview::event2pos(QPointF &click_pos) const
    {
        click_pos = (click_pos - pos) / scale;
        QPointF topleft = sampleride::Classes::model()->table_size().topLeft(),
        bottomright = sampleride::Classes::model()->table_size().bottomRight();

        return (click_pos - topleft).x() >= 0 && (click_pos - topleft).y() >= 0 &&
            (bottomright - click_pos).x() >= 0 && (bottomright - click_pos).y() >= 0;
    }

    bool Preview::event2module(QPointF &click_pos) const
    {
        bool ok = event2pos(click_pos);
        click_pos = QPointF((click_pos.x() - sampleride::Classes::model()->module_spacing().x() - sampleride::Classes::model()->table_size().x())
                / (sampleride::Classes::model()->module_size().x() + sampleride::Classes::model()->module_spacing().x()),
                       (click_pos.y() - sampleride::Classes::model()->module_spacing().y() - sampleride::Classes::model()->table_size().y())
                  / (sampleride::Classes::model()->module_size().y() + sampleride::Classes::model()->module_spacing().y()));

        return ok;
    }

    void Preview::repaint_canvas()
    {
        update();
    }

    void Preview::event2modulesize(QPointF &module_pos) const
    {
        module_pos.setX(module_pos.x() * sampleride::Classes::model()->module_size().x());
        module_pos.setY(module_pos.y() * sampleride::Classes::model()->module_size().y());
    }
} // namespace sampleride