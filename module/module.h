//
// Created by flynn on 8/3/23.
//

#ifndef SAMPLERIDE_MODULE_H
#define SAMPLERIDE_MODULE_H

#include <QObject>
#include <QPoint>
#include <QPainter>
#include <QHash>
#include <QVariant>

#include "api/classes.h"
#include "state/state.h"

namespace sampleride
{
    enum class ModuleTypes
    {
        None = 0,
        Other = 1,
        SingleTray = 2,
        Tray = 3,
        RectTray = 4,
        Container = 5,
    };

    class PhysicalModel : public QObject
    {
        Q_OBJECT
    public:
        explicit PhysicalModel(QObject* parent = nullptr, ModuleTypes* type = new ModuleTypes(ModuleTypes::None));
        void setup_tray(QRectF vial_centers, QPointF spacing, QPoint vials_num, float radius);
        QPointF get_pos() const;

        ModuleTypes* _type;
        QRectF _size;
        QPointF _center;
        QPoint _pos;
        bool init;
    protected:
        QVariantHash _data;
    };

    class Module : public QObject
    {
        Q_OBJECT
    public:
        explicit Module(QObject* parent = nullptr);
        virtual void draw_preview(QPainter* qp) const = 0;

        const int _id = -1;

        QString _name;

        QColor _color;

        ModuleTypes _type;
        PhysicalModel _model;
    };

    class SimpleTray : public Module
    {
        Q_OBJECT
    public:
        explicit SimpleTray(QObject* parent = nullptr);
        void draw_preview(QPainter* qp) const override;

        const int _id = 0;
    };

} // namespace sampleride

#endif //SAMPLERIDE_MODULE_H
