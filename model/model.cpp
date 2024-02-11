//
// Created by Flynn on 02.08.2023.
//

#include "model.h"

namespace sampleride
{

    Model::Model(QObject *parent) : QObject(parent), _base_size(350, 350), _table_size(10, 10, 500, 500),
    _module_size(100, 70), _module_spacing(5, 5),
    _table_start_offset(10, 10, 0), _head_offset_home(30, 30, 30), _z_movement_height(35),
    _machine_limit_start({0, 0, 0}), _machine_limit_end({200, 200, 30}),
    _is_z_inverting(true), gen_state(this)
    {
        _nozzle_lengths.append(10);
        _pipettes.append(new Pipette(this, {10, -5, -50}));
        gen_state._cur_head_pos = {0, 0, 30};
    }

    Model::~Model() noexcept
    {

    }

    float Model::map(float value, float in_min, float in_max, float out_min, float out_max)
    {
        return out_min + (out_max - out_min) * ((value - in_min) / (in_max - in_min));
    }

    QVector3D Model::get_nozzle_pos() const
    {
        QVector3D res = _head_offset_home + gen_state._cur_head_pos + _pipettes[gen_state._cur_pipette]->_head_offset;
        if (gen_state._cur_pipette_nozzle >= 0)
            res.setZ(res.z() - _nozzle_lengths[gen_state._cur_pipette_nozzle]);
        return res;
    }

    bool Model::move_nozzle(const QVector3D &pos)
    {
        QVector3D res = pos;
        if (gen_state._cur_pipette_nozzle >= 0)
            res.setZ(res.z() + _nozzle_lengths[gen_state._cur_pipette_nozzle]);
        res -= _head_offset_home + _pipettes[gen_state._cur_pipette]->_head_offset;

        if (res.x() < _machine_limit_start.x() || res.y() < _machine_limit_start.y() || res.z() < _machine_limit_start.z())
            return false;

        if (res.x() > _machine_limit_end.x() || res.y() > _machine_limit_end.y() || res.z() > _machine_limit_end.z())
            return false;

        gen_state._cur_head_pos = res;
        return true;
    }

    ModelState::ModelState(QObject* parent) : QObject(parent), _cur_pipette(0), _cur_pipette_nozzle(-1)
    {

    }

    Pipette::Pipette(QObject* parent, QVector3D offset) : QObject(parent), _head_offset(offset)
    {

    }
} // namespace sampleride