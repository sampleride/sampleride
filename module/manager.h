//
// Created by flynn on 8/3/23.
//

#ifndef SAMPLERIDE_MANAGER_H
#define SAMPLERIDE_MANAGER_H

#include <QObject>
#include <QHash>
#include <iostream>

#include "api/classes.h"
#include "api/enums.h"
#include "module/module.h"

namespace sampleride
{

    class ModuleManager : public QObject
    {
        Q_OBJECT
    public:
        explicit ModuleManager(QObject* parent = nullptr);
        void initModules();
        Module* getModule(int id);

        QHash<int, Module*> modules;
        QHash<QPoint, Module*> module_pos;
    public slots:
        void set_color(QPoint module, ColorTypes col);
    signals:
        void update_preview();
    };

    class ColorFactory : public QObject
    {
        Q_OBJECT
    public:
        explicit ColorFactory(QObject* parent = nullptr);
        QColor* getColor(int id, ColorTypes type);

        QList<QColor*> _palette;
        QList<QColor*> _hover;
        QList<QColor*> _select;
        QHash<int, size_t> module_map;
        size_t used_colors;
    };

} // namespace sampleride

#endif //SAMPLERIDE_MANAGER_H
