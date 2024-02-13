//
// Created by flynn on 8/3/23.
//

#include "module.h"
#include "model/model.h"
#include "module/manager.h"

namespace sampleride
{

    sampleride::Module::Module(QObject* parent, QPoint vials) : QObject(parent), _type(ModuleTypes::None), _flags(ModuleFlags(0)), _model(this, _type, _flags), vials_size(vials), _vials(vials.x(), QList<Vial*>(vials.y(),
                                                                                                                                                                                        nullptr))
    {

    }

    SimpleTray::SimpleTray(QObject* parent) : Module(parent)
    {
        _type = ModuleTypes::Tray;
        _model._type = _type;

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
        if (sampleride::Classes::modulemanager()->same_module(_id, sampleride::Classes::state()->module_hover)
        || sampleride::Classes::modulemanager()->same_module(_id, sampleride::Classes::state()->module_select))
        {
            qp->drawText(int(pt.x()), int(pt.y()) - 5, _name);
        }

        QPoint vials_num = _model._data["vials_num"].value<QPoint>();
        for (size_t i = 0; i < vials_num.x(); i++)
        {
            for (size_t j = 0; j < vials_num.y(); j++)
            {
                QPoint comp = QPoint(i, j);
                QRectF rect = _model.get_vials()->value(comp);
                if (sampleride::Classes::state()->comp_hover == comp)
                    qp->setPen(QPen(QBrush(*sampleride::Classes::color()->getColor(
                            _id, ColorTypes::FG_COMP_HOVER)), 2));
                else
                {
                    if (sampleride::Classes::state()->comp_select.contains(comp))
                        qp->setPen(QPen(QBrush(*sampleride::Classes::color()->getColor(
                                _id, ColorTypes::FG_COMP_SELECT)), 2));
                    else
                        qp->setPen(QPen(QBrush(*_color), 2));
                }
                qp->drawEllipse(rect);
            }
        }
    }

    PhysicalModel::PhysicalModel(QObject* parent, ModuleTypes type, ModuleFlags flags) : QObject(parent), _type(type), _flags(flags), init(false)
    {

    }

    void PhysicalModel::setup_tray(QRectF vial_centers, QPoint vials_num, float radius)
    {
        // Configure the tray parameters
        // Each vial here is actually a tray, so we take dimensions of the tray

        // vial_centers: Rectangle between the center of top left vial and the bottom right vial
        // vials_num: number of vials (x, y)
        // radius: radius of each vial

        if (_type != ModuleTypes::Tray)
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

        QHash<QPoint, QRectF>* vials = new QHash<QPoint, QRectF>;

        QPointF r = QPointF(radius, radius);
        for (size_t i = 0; i < vials_num.x(); i++)
        {
            for (size_t j = 0; j < vials_num.y(); j++)
            {
                QPointF s = QPointF(spacing.x() * float(i), spacing.y() * float(j));
                vials->insert(QPoint(i, j), QRectF(get_pos() + vial_centers.topLeft() - r + s,
                                       get_pos() + vial_centers.topLeft() + r + s));
            }
        }

        _data.insert("vials", QVariant::fromValue(vials));
    }

    QPointF PhysicalModel::get_pos() const
    {
        // Get module position
        return {int(sampleride::Classes::model()->module_size().x() + sampleride::Classes::model()->module_spacing().x()) * _pos.x() +
                 sampleride::Classes::model()->module_spacing().x() + sampleride::Classes::model()->table_size().x(),
                 int(sampleride::Classes::model()->module_size().y() + sampleride::Classes::model()->module_spacing().y()) * _pos.y() +
                 sampleride::Classes::model()->module_spacing().y() + sampleride::Classes::model()->table_size().y()};
    }

    QHash<QPoint, QRectF>* PhysicalModel::get_vials() const
    {
        if (_type != ModuleTypes::Tray || !init)
        {
            // TODO raise exception
            return nullptr;
        }
        return _data["vials"].value<QHash<QPoint, QRectF>*>();
    }

    bool PhysicalModel::hover(QPointF pos)
    {
        switch (_type)
        {
            case ModuleTypes::Tray:
                QPoint num = _data["vials_num"].value<QPoint>();

                QPoint res = _tray_vial(pos);
                if (res.x() < 0 || res.y() < 0 || res.x() >= num.x() || res.y() >= num.y())
                {
                    sampleride::Classes::state()->set_comp_hover();
                    return false;
                }

                sampleride::Classes::state()->set_comp_hover(res);
                return true;
        }
        return false;
    }

    bool PhysicalModel::click(QPointF pos)
    {
        switch (_type)
        {
            case ModuleTypes::Tray:
                QPoint num = _data["vials_num"].value<QPoint>();

                QPoint res = _tray_vial(pos);
                if (res.x() < 0 || res.y() < 0 || res.x() >= num.x() || res.y() >= num.y())
                {
                    return false;
                }

                if (sampleride::Classes::state()->comp_select.contains(res))
                    sampleride::Classes::state()->unset_comp_selection(res);
                else
                    sampleride::Classes::state()->set_comp_selection(res);
                return true;
        }
        return false;
    }

    QPoint PhysicalModel::_tray_vial(QPointF pos)
    {
        QRectF centers = _data["vial_centers"].value<QRectF>();
        QPoint num = _data["vials_num"].value<QPoint>();

        return QPoint((sampleride::Model::map(pos.x(), centers.x(), centers.width(), 0, num.x())),
                               (sampleride::Model::map(pos.y(), centers.y(), centers.height(), 0, num.y())));
    }

    Vial::Vial(QObject* parent) : QObject(parent), liquid(-1), volume_ml(0)
    {

    }
} // namespace sampleride