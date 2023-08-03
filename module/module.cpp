//
// Created by flynn on 8/3/23.
//

#include "module.h"

namespace sampleride
{

    sampleride::Module::Module(QObject* parent, Classes* _classes) : QObject(parent), classes(_classes), _type(ModuleTypes::None)
    {

    }

    SimpleTray::SimpleTray(QObject* parent, Classes* _classes) : Module(parent, _classes)
    {
        QRectF _size(0, 0, 100, 70);
        QString _name("Simple tray");
        QPoint _pos(0, 0);
        QColor _color(50, 230, 40);
    }

    void SimpleTray::draw_preview(QPainter* qp) const
    {
        qp->setPen(QPen(QBrush(_color), 2));
        int px = int(classes->model().module_size().x() + classes->model().module_spacing().x()) * _pos.x();
        int py = int(classes->model().module_size().y() + classes->model().module_spacing().y()) * _pos.y();
        qp->drawRect(px, py,_size.width(), _size.height());
        qp->drawText(px + 5, py + 14, _name);
    }
} // namespace sampleride