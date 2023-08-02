//
// Created by Flynn on 02.08.2023.
//

#ifndef SAMPLERIDE_MODEL_H
#define SAMPLERIDE_MODEL_H

#include <QPoint>
#include <QRect>
#include <QWidget>

namespace sampleride
{

    class Model : public QWidget
    {
    public:
        explicit Model(QWidget *parent = nullptr);

        ~Model() noexcept;

        QPointF base_size() const
        { return _base_size; }

        QRectF table_size() const
        { return _table_size; }

        QPointF module_size() const
        { return _module_size; }

        QPointF module_spacing() const
        { return _module_spacing; }

    protected:
        QPointF _base_size;
        QRectF _table_size;
        QPointF _module_size;
        QPointF _module_spacing;
    };

} // namespace sampleride

#endif //SAMPLERIDE_MODEL_H
