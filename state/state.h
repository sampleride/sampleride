//
// Created by Flynn on 20.08.2023.
//

#ifndef SAMPLERIDE_STATE_H
#define SAMPLERIDE_STATE_H

#include <QObject>
#include <QPoint>

namespace sampleride
{

    class State : public QObject
    {
    public:
        explicit State(QObject* parent = nullptr);

        QPoint module_select;
        QPoint tray_select;
        QPoint module_hover;
        QPoint tray_hover;
    };

} // namespace sampleride

#endif //SAMPLERIDE_STATE_H
