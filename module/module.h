//
// Created by flynn on 8/3/23.
//

#ifndef SAMPLERIDE_MODULE_H
#define SAMPLERIDE_MODULE_H

#include <QObject>
#include <QPoint>
#include <QPainter>

#include "api/classes.h"

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

    class Module : public QObject
    {
        Q_OBJECT
    public:
        explicit Module(QObject* parent = nullptr, Classes* _classes = nullptr);
        virtual void draw_preview(QPainter* qp) const = 0;

        const int _id = -1;
    protected:
        Classes* classes;
        QString _name;

        QPoint _pos; // TODO add temporary data model
        QColor _color;

        ModuleTypes _type;

        QRectF _size;
        QPointF _center; // TODO add physical model
    };

    class SimpleTray : public Module
    {
        Q_OBJECT
    public:
        explicit SimpleTray(QObject* parent = nullptr, Classes* _classes = nullptr);
        void draw_preview(QPainter* qp) const override;

        const int _id = 0;
    };

} // namespace sampleride

#endif //SAMPLERIDE_MODULE_H
