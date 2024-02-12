//
// Created by Flynn on 20.08.2023.
//

#ifndef SAMPLERIDE_STATE_H
#define SAMPLERIDE_STATE_H

#include <QObject>
#include <QPoint>
#include <QSet>

#include "api/classes.h"
#include "api/enums.h"

namespace sampleride
{

    class State : public QObject
    {
        Q_OBJECT
    public:
        explicit State(QObject* parent = nullptr);
        void set_selection(QPoint module);
        void set_selection();
        void set_hover(QPoint module);
        void set_hover();
        void set_comp_hover(QPoint comp);
        void set_comp_hover();
        void set_comp_selection(QPoint comp);
        void unset_comp_selection(QPoint comp);
        void set_comp_selection();
        void set_pos_selection(QPoint pos);
        void set_pos_selection();
        void drop_selection_state();

        QPoint module_select;
        QPoint module_hover;

        QSet<QPoint> comp_select;
        QPoint comp_hover;
        QPoint pos_select;
        SelectorState s_state;
        SelectorFlags s_flags;

        static QPoint none_pos;
    public slots:
        void setSelectorState(SelectorState state, SelectorFlags flags);
        void forceDropSelector();
    signals:
        void set_color(QPoint module, ColorTypes col);
        void update_preview();
        void selectionFinished(SelectorState state, SelectorFlags flags);
    };

} // namespace sampleride

#endif //SAMPLERIDE_STATE_H
