//
// Created by flynn on 8/3/23.
//

#include "module.h"
#include "model/model.h"
#include "module/manager.h"

namespace sampleride
{

    sampleride::Module::Module(QObject* parent, QPoint vials) : QObject(parent), _type(ModuleTypes::None), _model(this, &_type), vials_size(vials), _vials(vials.x(), QList<Vial*>(vials.y(),
                                                                                                                                                                                        nullptr))
    {

    }

    SimpleTray::SimpleTray(QObject* parent) : Module(parent)
    {
        _type = ModuleTypes::Tray;
        _model._type = &_type;

        _model._size = QRectF(0, 0, 100, 70);
        _model._pos = QPoint(0, 0);

        _name = QString("Simple tray");
        _model.setup_tray(QRectF(10.0, 10.0, 90.0, 60.0), QPoint((90-10)/10, (60-10)/10), 3.5);
        //_color = new QColor(50, 230, 40);
    }

    void SimpleTray::draw_preview(QPainter* qp) const
    {
        qp->setPen(QPen(QBrush(*_color), 2));
        QPointF pt = _model.get_pos();
        qp->drawRect(int(pt.x()), int(pt.y()), _model._size.width(), _model._size.height());
        qp->drawText(int(pt.x()), int(pt.y()) - 5, _name);

        //for (QRectF rect : *_model.get_vials())
        QPoint vials_num = _model._data["vials_num"].value<QPoint>();
        for (size_t i = 0; i < _model.get_vials()->size(); i++)
        {
            QRectF rect = _model.get_vials()->at(i);
            QPoint comp = QPoint(i % vials_num.x(), i / vials_num.y());
            if (sampleride::Classes::state()->comp_hover == comp)
                qp->setPen(QPen(QBrush(*sampleride::Classes::color()->getColor(_id, ColorTypes::FG_COMP_HOVER)), 2));
            else
                qp->setPen(QPen(QBrush(*_color), 2));
            qp->drawEllipse(rect);
        }
    }

    PhysicalModel::PhysicalModel(QObject* parent, ModuleTypes* type) : QObject(parent), _type(type), init(false)
    {

    }

    void PhysicalModel::setup_tray(QRectF vial_centers, QPoint vials_num, float radius)
    {
        if (*_type != ModuleTypes::Tray)
        {
            // TODO raise exception
            return;
        }

        init = true;
        QPointF spacing = QPointF((vial_centers.bottomRight().x() - vial_centers.topLeft().x() + 1)/float(vials_num.x()),
                                  (vial_centers.bottomRight().y() - vial_centers.topLeft().y() + 1)/float(vials_num.y()));

        _data.insert("vial_centers", QVariant::fromValue(vial_centers));
        _data.insert("spacing", QVariant::fromValue(spacing));
        _data.insert("vials_num", QVariant::fromValue(vials_num));
        _data.insert("radius", QVariant::fromValue(radius));

        QList<QRectF>* vials = new QList<QRectF>;

        QPointF r = QPointF(radius, radius);
        for (size_t i = 0; i < vials_num.x(); i++)
        {
            for (size_t j = 0; j < vials_num.y(); j++)
            {
                QPointF s = QPointF(spacing.x() * float(i), spacing.y() * float(j));
                vials->push_back(QRectF(get_pos() + vial_centers.topLeft() - r + s,
                                       get_pos() + vial_centers.topLeft() + r + s));
            }
        }

        _data.insert("vials", QVariant::fromValue(vials));
    }

    QPointF PhysicalModel::get_pos() const
    {
        return {int(sampleride::Classes::model()->module_size().x() + sampleride::Classes::model()->module_spacing().x()) * _pos.x() +
                 sampleride::Classes::model()->module_spacing().x() + sampleride::Classes::model()->table_size().x(),
                 int(sampleride::Classes::model()->module_size().y() + sampleride::Classes::model()->module_spacing().y()) * _pos.y() +
                 sampleride::Classes::model()->module_spacing().y() + sampleride::Classes::model()->table_size().y()};
    }

    QList<QRectF>* PhysicalModel::get_vials() const
    {
        if (*_type != ModuleTypes::Tray || !init)
        {
            // TODO raise exception
            return nullptr;
        }
        return _data["vials"].value<QList<QRectF>*>();
    }

    void PhysicalModel::hover(QPointF pos)
    {
        switch (*_type)
        {
            case ModuleTypes::Tray:
                QRectF centers = _data["vial_centers"].value<QRectF>();
                QPointF spacing = _data["spacing"].value<QPointF>();
                float radius = _data["radius"].value<float>();

                QPointF vial = QPointF(pos.x() / (2 * radius + spacing.x()), pos.y() / (2 * radius + spacing.y()));
                // TODO add spacing check
                sampleride::Classes::state()->set_comp_hover(vial.toPoint());
                break;
        }
    }

    void PhysicalModel::click(QPointF pos)
    {

    }

    Vial::Vial(QObject* parent) : QObject(parent), liquid(-1), volume_ml(0)
    {

    }
} // namespace sampleride