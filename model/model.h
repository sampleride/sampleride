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
        Q_OBJECT
    public:
        explicit Model(QWidget *parent = nullptr);

        ~Model() noexcept;

        const QPointF& base_size() const
        { return _base_size; }

        const QRectF& table_size() const
        { return _table_size; }

        const QPointF& module_size() const
        { return _module_size; }

        const QPointF& module_spacing() const
        { return _module_spacing; }

    protected:
        QPointF _base_size;
        QRectF _table_size;
        QPointF _module_size;
        QPointF _module_spacing;
    };

} // namespace sampleride

#endif //SAMPLERIDE_MODEL_H
