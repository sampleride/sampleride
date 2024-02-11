//
// Created by Flynn on 02.08.2023.
//

#ifndef SAMPLERIDE_MODEL_H
#define SAMPLERIDE_MODEL_H

#include <QPoint>
#include <QRect>
#include <QObject>
#include <QVector3D>

namespace sampleride
{

    class Model;

    class ModelState : public QObject
    {
        Q_OBJECT
    public:
        explicit ModelState(QObject* parent = nullptr);
        friend Model;

    protected:
        int _cur_pipette;
        int _cur_pipette_nozzle;
        QVector3D _cur_head_pos;
    };

    class Pipette : public QObject
    {
        Q_OBJECT
    public:
        explicit Pipette(QObject* parent = nullptr, QVector3D offset = {0, 0, 0});
        friend Model;

    protected:
        QVector3D _head_offset; // pipette offset from head
    };

    class Model : public QObject
    {
        Q_OBJECT
    public:
        explicit Model(QObject *parent = nullptr);

        ~Model() noexcept;

        const QPointF& base_size() const
        { return _base_size; }

        const QRectF& table_size() const
        { return _table_size; }

        const QPointF& module_size() const
        { return _module_size; }

        const QPointF& module_spacing() const
        { return _module_spacing; }

        static float map(float value, float in_min, float in_max, float out_min, float out_max);

        QVector3D get_nozzle_pos() const;
        bool move_nozzle(const QVector3D& pos);
        //QVector3D nozzle2machine(const QVector3D& pos);
        //QVector3D machine2nozzle(const QVector3D& pos);

    protected:
        QPointF _base_size;
        QRectF _table_size;
        QPointF _module_size;
        QPointF _module_spacing;

        QVector3D _table_start_offset; // table start offset from 0
        QVector3D _head_offset_home; // actual head position after homing
        QVector3D _machine_limit_start; // machine limit in firmware coordinates
        QVector3D _machine_limit_end;
        float _z_movement_height; // max Z movement height
        bool _is_z_inverting; // is Z home at its lowest position
        QList<float> _nozzle_lengths; // List of nozzles
        QList<Pipette*> _pipettes;
        ModelState gen_state;
    };



} // namespace sampleride

#endif //SAMPLERIDE_MODEL_H
