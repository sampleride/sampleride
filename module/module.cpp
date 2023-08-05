//
// Created by flynn on 8/3/23.
//

#include "module.h"
#include "model/model.h"

namespace sampleride
{

    sampleride::Module::Module(QObject* parent) : QObject(parent), _type(ModuleTypes::None)
    {

    }

    SimpleTray::SimpleTray(QObject* parent) : Module(parent)
    {
        _type = ModuleTypes::Tray;
        _size = QRectF(0, 0, 100, 70);
        _name = QString("Simple tray");
        _pos = QPoint(0, 0);
        _color = QColor(50, 230, 40);
    }

    void SimpleTray::draw_preview(QPainter* qp) const
    {
        qp->setPen(QPen(QBrush(_color), 2));
        int px = int(sampleride::Classes::model()->module_size().x() + sampleride::Classes::model()->module_spacing().x()) * _pos.x() +
                sampleride::Classes::model()->module_spacing().x() + sampleride::Classes::model()->table_size().x();
        int py = int(sampleride::Classes::model()->module_size().y() + sampleride::Classes::model()->module_spacing().y()) * _pos.y() +
                sampleride::Classes::model()->module_spacing().y() + sampleride::Classes::model()->table_size().y();
        qp->drawRect(px, py,_size.width(), _size.height());
        qp->drawText(px, py - 5, _name);
    }
} // namespace sampleride