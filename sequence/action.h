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
#include <QSet>

#include "api/classes.h"
#include "api/enums.h"
#include "model/model.h"
#include "state/state.h"
#include "module/manager.h"

namespace sampleride
{

    class Sequence;

    class Meta : public QObject
    {
        Q_OBJECT
    public:
        Meta(QObject* parent = nullptr, bool cycle = false) : QObject(parent), is_cycle(cycle) {};
        bool is_cycle = false;
    };

    class SequenceMeta : public QObject
    {
        Q_OBJECT
    public:
        explicit SequenceMeta(QObject* parent = nullptr) : QObject(parent) {};
        QList<Meta*> meta;
    };

    class Action : public QObject
    {
        Q_OBJECT
    public:
        explicit Action(SequenceMeta* meta, QObject* parent = nullptr);

        virtual void populateRow(QListWidget* lyt, int row);
        virtual void finishSelection(QListWidget* lyt, int row, SelectorState state, SelectorFlags flags);
        friend Sequence;
    signals:
        void setSelectorState(SelectorState state, SelectorFlags flags);
    protected:
        QString _name;
        SequenceMeta* _meta;
        int row;
    };

    class MoveAction : public Action
    {
        Q_OBJECT
    public:
        explicit MoveAction(SequenceMeta* meta, QObject* parent = nullptr);
        void populateRow(QListWidget* lyt, int row) override;
        void finishSelection(QListWidget* lyt, int row, SelectorState state, SelectorFlags flags) override;
    public slots:
        void _getPosition();
    };

    class TrayAction : public Action
    {
        Q_OBJECT
    public:
        explicit TrayAction(SequenceMeta* meta, QObject* parent = nullptr);
        void populateRow(QListWidget* lyt, int row) override;
        void finishSelection(QListWidget* lyt, int row, SelectorState state, SelectorFlags flags) override;
    public slots:
        void _getPosition();
    protected:
        QHBoxLayout* _drawLayout(int row);
        QPushButton* _drawTraySelector(int row);
        QPushButton* _drawModuleSelector(int row);

        QPoint _pos;
        QPoint _module;
        bool draw_tray;
        bool draw_module;
    };

    class ModuleAction : public TrayAction
    {
        Q_OBJECT
    public:
        explicit ModuleAction(SequenceMeta* meta, QObject* parent = nullptr);
        void populateRow(QListWidget* lyt, int row) override;
    };

} // sampleride

#endif //SAMPLERIDE_ACTION_H
