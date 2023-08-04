//
// Created by Flynn on 02.08.2023.
//

#ifndef SAMPLERIDE_PREVIEW_H
#define SAMPLERIDE_PREVIEW_H

#include <QPainter>
#include <QWidget>

#include "api/classes.h"
#include "module/manager.h"

namespace sampleride
{
    class Module;

    class Preview : public QWidget {
        Q_OBJECT
    public:
        explicit Preview(QWidget* parent = nullptr, Classes* _classes = nullptr);
    protected:
        void paintEvent(QPaintEvent* event) override;
        Classes* classes = nullptr;
    };

} // namespace sampleride

#endif //SAMPLERIDE_PREVIEW_H
