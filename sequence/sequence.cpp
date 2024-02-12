//
// Created by Flynn on 11.02.2024.
//

#include "sequence.h"

namespace sampleride
{
    Sequence::Sequence(QWidget* parent) : QWidget(parent), _meta(this)
    {
        auto layout = new QVBoxLayout(this);

        setLayout(layout);

        _lyt = new QListWidget(this);
        layout->addWidget(_lyt);

        // Initializing actions
        _meta.meta.append(new Meta(&_meta, false));
        auto act = new MoveAction(&_meta, this);
        _actions.append(act);
        act->populateRow(_lyt, 0);

        _meta.meta.append(new Meta(&_meta, false));
        auto act2 = new TrayAction(&_meta, this);
        _actions.append(act2);
        act2->populateRow(_lyt, 1);
    }

} // sampleride