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
#include "model/model.h"

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
        friend Sequence;
    protected:
        QString _name;
        SequenceMeta* _meta;
    };

    class MoveAction : public Action
    {
        Q_OBJECT
    public:
        explicit MoveAction(SequenceMeta* meta, QObject* parent = nullptr);
        void populateRow(QListWidget* lyt, int row) override;
    };

    class TrayAction : public Action
    {
        Q_OBJECT
    public:
        explicit TrayAction(SequenceMeta* meta, QObject* parent = nullptr);
        void populateRow(QListWidget* lyt, int row) override;
    protected:
        QHBoxLayout* _drawLayout(int row, bool drawTray = true, bool drawModule = true);
        QPushButton* _drawTraySelector(int row);
        QPushButton* _drawModuleSelector(int row);

        QPoint _pos;
        QPoint _module;
    };

} // sampleride

#endif //SAMPLERIDE_ACTION_H
