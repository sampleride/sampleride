//
// Created by Flynn on 20.08.2023.
//

#ifndef SAMPLERIDE_STATE_H
#define SAMPLERIDE_STATE_H

#include <QObject>
#include <QPoint>

#include "api/classes.h"
#include "api/enums.h"

namespace sampleride
{

    class State : public QObject
    {
        Q_OBJECT
    public:
        explicit State(QObject* parent = nullptr);
        void set_selection(QPoint module, QPoint tray = none_pos);
        void set_selection();
        void set_hover(QPoint module, QPoint tray = none_pos);
        void set_hover();

        QPoint module_select;
        QPoint tray_select;
        QPoint module_hover;
        QPoint tray_hover;

        static QPoint none_pos;
    signals:
        void set_color(QPoint module, ColorTypes col);
    };

} // namespace sampleride

#endif //SAMPLERIDE_STATE_H
