//
// Created by Flynn on 11.02.2024.
//

#include "action.h"

namespace sampleride
{

    Action::Action(QObject* parent) : QObject(parent)
    {

    }

    void Action::populateRow(QListWidget* lyt, int row)
    {

    }

    MoveAction::MoveAction(QObject* parent) : Action(parent)
    {
        _name = "move";
    }

    void MoveAction::populateRow(QListWidget* lyt, int row)
    {
        //auto name = new QLabel(_name);
        auto layout = new QHBoxLayout();
        auto wrapper = new QWidget();
        //layout->addWidget(name);
        auto spacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);
        layout->addSpacerItem(spacer);

        auto x_pos = new QSpinBox();
        x_pos->setMinimum(0);
        x_pos->setMaximum(sampleride::Classes::model()->base_size().x());
        auto y_pos = new QSpinBox();
        y_pos->setMinimum(0);
        y_pos->setMaximum(sampleride::Classes::model()->base_size().y());

        auto btn = new QPushButton("...");

        layout->addWidget(x_pos);
        layout->addWidget(y_pos);
        layout->addWidget(btn);
        wrapper->setLayout(layout);

        auto item = new QListWidgetItem();
        item->setText(_name);
        item->setSizeHint(wrapper->sizeHint());
        lyt->addItem(item);
        lyt->setItemWidget(item, wrapper);
    }
} // sampleride