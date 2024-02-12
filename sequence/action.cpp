//
// Created by Flynn on 11.02.2024.
//

#include "action.h"

namespace sampleride
{

    Action::Action(SequenceMeta* meta, QObject* parent) : QObject(parent), _meta(meta)
    {

    }

    void Action::populateRow(QListWidget* lyt, int row)
    {

    }

    MoveAction::MoveAction(SequenceMeta* meta, QObject* parent) : Action(meta, parent)
    {
        _name = "Move to";
    }

    void MoveAction::populateRow(QListWidget* lyt, int row)
    {
        //auto name = new QLabel(_name);
        auto layout = new QHBoxLayout();
        auto wrapper = new QWidget();
        //layout->addWidget(name);
        auto label = new QLabel(_name);
        layout->addWidget(label);

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
        item->setSizeHint({0, wrapper->sizeHint().height()});
        lyt->addItem(item);
        lyt->setItemWidget(item, wrapper);
    }

    TrayAction::TrayAction(SequenceMeta* meta, QObject* parent) : Action(meta, parent)
    {
        _name = "Go to";
    }

    void TrayAction::populateRow(QListWidget* lyt, int row)
    {
        auto wrapper = new QWidget();
        auto layout = _drawLayout(row);
        wrapper->setLayout(layout);

        auto item = new QListWidgetItem();
        item->setSizeHint({0, wrapper->sizeHint().height()});
        lyt->addItem(item);
        lyt->setItemWidget(item, wrapper);
    }

    QPushButton* TrayAction::_drawTraySelector(int row)
    {
        QString text = "...";
        if (_meta->meta[row]->is_cycle)
            text = "each";
        auto btn = new QPushButton(text);
        return btn;
    }

    QPushButton* TrayAction::_drawModuleSelector(int row)
    {
        QString text = "...";
        if (_meta->meta[row]->is_cycle)
            text = "each";
        auto btn = new QPushButton(text);
        return btn;
    }

    QHBoxLayout* TrayAction::_drawLayout(int row, bool drawTray, bool drawModule)
    {
        auto layout = new QHBoxLayout();
        auto nlabel = new QLabel(_name);
        layout->addWidget(nlabel);
        auto spacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);
        layout->addSpacerItem(spacer);

        if (drawTray)
        {
            auto btn = _drawTraySelector(row);
            layout->addWidget(btn);
        }
        if (drawModule)
        {
            auto label = new QLabel("in");
            layout->addWidget(label);
            auto btn = _drawModuleSelector(row);
            layout->addWidget(btn);
            auto label2 = new QLabel("module");
            layout->addWidget(label2);
        }

        return layout;
    }
} // sampleride