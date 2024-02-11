//
// Created by Flynn on 11.02.2024.
//

#ifndef SAMPLERIDE_ACTION_H
#define SAMPLERIDE_ACTION_H

#include <QObject>
#include <QListWidget>
#include <QLabel>
#include <QSpinBox>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QPushButton>

#include "api/classes.h"
#include "model/model.h"

namespace sampleride
{

    class Sequence;

    class Action : public QObject
    {
        Q_OBJECT
    public:
        explicit Action(QObject* parent = nullptr);

        virtual void populateRow(QListWidget* lyt, int row);
        friend Sequence;
    protected:
        QString _name;
    };

    class MoveAction : public Action
    {
        Q_OBJECT
    public:
        explicit MoveAction(QObject* parent = nullptr);
        void populateRow(QListWidget* lyt, int row) override;
    };

} // sampleride

#endif //SAMPLERIDE_ACTION_H
