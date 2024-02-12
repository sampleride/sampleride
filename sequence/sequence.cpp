//
// Created by Flynn on 11.02.2024.
//

#include "sequence.h"

namespace sampleride
{
    Sequence::Sequence(QWidget* parent) : QWidget(parent), _meta(this), cur_act(-1)
    {
        auto layout = new QVBoxLayout(this);

        setLayout(layout);

        _lyt = new QListWidget(this);
        layout->addWidget(_lyt);
        connect(_lyt, &QListWidget::currentRowChanged, this, &Sequence::actionSelected);

        connect(this, &Sequence::setSelectorState, sampleride::Classes::state(), &State::setSelectorState);
        connect(this, &Sequence::finishSelection, sampleride::Classes::state(), &State::forceDropSelector);
        connect(sampleride::Classes::state(), &State::selectionFinished, this, &Sequence::selectorFinished);

        // Initializing actions
        _meta.meta.append(new Meta(&_meta, false));
        auto act = new MoveAction(&_meta, this);
        connect(act, &Action::setSelectorState, this, &Sequence::setSelectorState);
        _actions.append(act);
        act->populateRow(_lyt, 0);

        _meta.meta.append(new Meta(&_meta, false));
        auto act2 = new TrayAction(&_meta, this);
        connect(act, &Action::setSelectorState, this, &Sequence::setSelectorState);
        _actions.append(act2);
        act2->populateRow(_lyt, 1);
    }

    void Sequence::selectorFinished(SelectorState state, SelectorFlags flags)
    {
        if (cur_act == -1)
            return;

        _actions[cur_act]->finishSelection(_lyt, cur_act, state, flags);
    }

    void Sequence::actionSelected(int pos)
    {
        emit finishSelection();
        cur_act = pos;
    }

} // sampleride