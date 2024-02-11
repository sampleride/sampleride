//
// Created by Flynn on 11.02.2024.
//

#include "sequence.h"

namespace sampleride
{
    Sequence::Sequence(QWidget* parent) : QWidget(parent)
    {
        auto layout = new QVBoxLayout(this);

        setLayout(layout);

        _lyt = new QListWidget(this);
        layout->addWidget(_lyt);

        auto act = new MoveAction(this);
        _actions.append(act);
        act->populateRow(_lyt, 0);
    }

} // sampleride