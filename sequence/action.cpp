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

    void Action::finishSelection(QListWidget* lyt, int row, SelectorState state, SelectorFlags flags)
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
        connect(btn, &QPushButton::clicked, this, &MoveAction::_getPosition);

        layout->addWidget(x_pos);
        layout->addWidget(y_pos);
        layout->addWidget(btn);
        wrapper->setLayout(layout);

        auto item = new QListWidgetItem();
        item->setSizeHint({0, wrapper->sizeHint().height()});
        lyt->addItem(item);
        lyt->setItemWidget(item, wrapper);
    }

    void MoveAction::finishSelection(QListWidget* lyt, int row, SelectorState state, SelectorFlags flags)
    {
        auto item = lyt->item(row);
        auto wid = lyt->itemWidget(item);

        auto spin_x = qobject_cast<QSpinBox*>(wid->layout()->itemAt(1)->widget());
        auto spin_y = qobject_cast<QSpinBox*>(wid->layout()->itemAt(2)->widget());

        spin_x->setValue(sampleride::Classes::state()->pos_select.x());
        spin_y->setValue(sampleride::Classes::state()->pos_select.y());

        // TODO store this value or add getter function

        sampleride::Classes::state()->set_pos_selection();
    }

    void MoveAction::_getPosition()
    {
        emit setSelectorState(SelectorState::SelectPos, SelectorFlags(0));
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

    ModuleAction::ModuleAction(SequenceMeta* meta, QObject* parent) : TrayAction(meta, parent)
    {

    }

    void ModuleAction::populateRow(QListWidget* lyt, int row)
    {
        auto wrapper = new QWidget();
        auto layout = _drawLayout(row, false, true);
        wrapper->setLayout(layout);

        auto item = new QListWidgetItem();
        item->setSizeHint({0, wrapper->sizeHint().height()});
        lyt->addItem(item);
        lyt->setItemWidget(item, wrapper);
    }
} // sampleride