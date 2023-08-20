//
// Created by flynn on 8/3/23.
//

#include "module.h"
#include "model/model.h"

namespace sampleride
{

    sampleride::Module::Module(QObject* parent) : QObject(parent), _type(ModuleTypes::None), _model(this, &_type)
    {

    }

    SimpleTray::SimpleTray(QObject* parent) : Module(parent)
    {
        _type = ModuleTypes::Tray;
        _model._type = &_type;

        _model._size = QRectF(0, 0, 100, 70);
        _model._pos = QPoint(0, 0);

        _name = QString("Simple tray");
        _color = QColor(50, 230, 40);
    }

    void SimpleTray::draw_preview(QPainter* qp) const
    {
        QColor fg(_color);
        if (sampleride::Classes::state()->module_select == _model._pos)
            fg = QColor(240, 240, 240);
        // TODO move to ColorFactory

        qp->setPen(QPen(QBrush(fg), 2));
        QPointF pt = _model.get_pos();
        qp->drawRect(int(pt.x()), int(pt.y()), _model._size.width(), _model._size.height());
        qp->drawText(int(pt.x()), int(pt.y()) - 5, _name);
    }

    PhysicalModel::PhysicalModel(QObject* parent, ModuleTypes* type) : QObject(parent), _type(type), init(false)
    {

    }

    void PhysicalModel::setup_tray(QRectF vial_centers, QPointF spacing, QPoint vials_num, float radius)
    {
        if (*_type != ModuleTypes::Tray)
        {
            // TODO raise exception
            return;
        }

        init = true;

        _data.insert("vial_centers", QVariant::fromValue(vial_centers));
        _data.insert("spacing", QVariant::fromValue(spacing));
        _data.insert("vials_num", QVariant::fromValue(vials_num));
        _data.insert("radius", QVariant::fromValue(radius));
    }

    QPointF PhysicalModel::get_pos() const
    {
        return {int(sampleride::Classes::model()->module_size().x() + sampleride::Classes::model()->module_spacing().x()) * _pos.x() +
                 sampleride::Classes::model()->module_spacing().x() + sampleride::Classes::model()->table_size().x(),
                 int(sampleride::Classes::model()->module_size().y() + sampleride::Classes::model()->module_spacing().y()) * _pos.y() +
                 sampleride::Classes::model()->module_spacing().y() + sampleride::Classes::model()->table_size().y()};
    }
} // namespace sampleride