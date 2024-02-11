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

namespace sampleride
{

    class Sequence : public QWidget
    {
        Q_OBJECT
    public:
        explicit Sequence(QWidget* parent = nullptr);
        void addAction(Action act);

    protected:
        QList<Action*> _actions;
        QListWidget* _lyt;
    };

} // sampleride

#endif //SAMPLERIDE_SEQUENCE_H
