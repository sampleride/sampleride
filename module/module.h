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
#include "api/enums.h"
#include "state/state.h"

namespace sampleride
{

    class PhysicalModel : public QObject
    {
        // Handles real coordinates of the module
        Q_OBJECT
    public:
        explicit PhysicalModel(QObject* parent = nullptr, ModuleTypes type = ModuleTypes::None, ModuleFlags flags = ModuleFlags(0));
        void setup_tray(QRectF vial_centers, QPoint vials_num, float radius);
        QPointF get_pos() const;
        QHash<QPoint, QRectF>* get_vials() const;
        bool hover(QPointF pos);
        bool click(QPointF pos);

        ModuleTypes _type;
        ModuleFlags _flags;
        QRectF _size;
        QPointF _center;
        QPoint _pos;
        float height;
        bool init;
        QVariantHash _data;
    protected:
        QPoint _tray_vial(QPointF pos);
    };

    class Vial : public QObject
    {
        Q_OBJECT
    public:
        explicit Vial(QObject* parent = nullptr);

        int liquid;
        QSet<int> liquids;
        int volume_ml;
    };

    class Module : public QObject
    {
        Q_OBJECT
    public:
        explicit Module(QObject* parent = nullptr, QPoint vials = QPoint(0, 0));
        virtual void draw_preview(QPainter* qp) const = 0;

        int _id = -1;

        QString _name;

        QColor* _color;

        ModuleTypes _type;
        ModuleFlags _flags;
        PhysicalModel _model;
        QList<QList<Vial*>> _vials;
        QPoint vials_size;
    };

    class SimpleTray : public Module
    {
        Q_OBJECT
    public:
        explicit SimpleTray(QObject* parent = nullptr);
        void draw_preview(QPainter* qp) const override;
    };

} // namespace sampleride

#endif //SAMPLERIDE_MODULE_H
