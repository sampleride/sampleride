//
// Created by Flynn on 11.02.2024.
//

#ifndef SAMPLERIDE_SEQUENCE_H
#define SAMPLERIDE_SEQUENCE_H

#include <QWidget>
#include <QListWidget>
#include <QVBoxLayout>
#include <QWidget>

#include "action.h"
#include "api/enums.h"
#include "state/state.h"

namespace sampleride
{

    class Sequence : public QWidget
    {
        Q_OBJECT
    public:
        explicit Sequence(QWidget* parent = nullptr);
        void addAction(Action act);

    public slots:
        void selectorFinished(SelectorState state, SelectorFlags flags);
        void actionSelected(int pos);
        void actionActivated(SelectorState state, SelectorFlags flags);
    signals:
        void setSelectorState(SelectorState state, SelectorFlags flags);
        void finishSelection();

    protected:
        QList<Action*> _actions;
        int cur_act;
        QListWidget* _lyt;
        SequenceMeta _meta;
    };

} // sampleride

#endif //SAMPLERIDE_SEQUENCE_H
