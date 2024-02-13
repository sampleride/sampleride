//
// Created by Flynn on 11.02.2024.
//

#include "sequence.h"

namespace sampleride
{
    Sequence::Sequence(QWidget* parent) : QWidget(parent), _meta(this), cur_act(-1)
    {
        // TODO add new QHBoxLayout to this one and add "Add", "Delete" buttons
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
        connect(act, &Action::setSelectorState, this, &Sequence::actionActivated);
        _actions.append(act);
        act->row = 0;
        act->populateRow(_lyt, 0);

        _meta.meta.append(new Meta(&_meta, false));
        auto act2 = new TrayAction(&_meta, this);
        connect(act2, &Action::setSelectorState, this, &Sequence::actionActivated);
        _actions.append(act2);
        act2->row = 1;
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

    void Sequence::actionActivated(SelectorState state, SelectorFlags flags)
    {
        // Make sure that row matches with the selection
        cur_act = qobject_cast<Action*>(sender())->row;

        _lyt->blockSignals(true);
        _lyt->setCurrentRow(cur_act);
        _lyt->blockSignals(false);

        emit setSelectorState(state, flags);
    }

    void Sequence::compile()
    {
        // TODO finish this compile function and connect it to "Compile" button
        // Run over each action and execute them
        // All warnings/errors should be added to the Compilation tab
    }

    void Sequence::run()
    {
        // TODO finish this execution function and connect it to "Run" button
        // Compile the program and then send gcode
    }

} // sampleride