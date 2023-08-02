//
// Created by Flynn on 02.08.2023.
//

#ifndef SAMPLERIDE_CLASSES_H
#define SAMPLERIDE_CLASSES_H

#include <QWidget>

#include "model/model.h"

namespace sampleride
{

    class Classes : public QWidget
    {
    public:
        explicit Classes(Model* m, QWidget *parent = nullptr);

        const Model& model() const
        { return *_model; };
    protected:
        Model* _model = nullptr;
    };

} // namespace sampleride

#endif //SAMPLERIDE_CLASSES_H
