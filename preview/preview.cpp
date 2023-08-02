//
// Created by Flynn on 02.08.2023.
//

#include "preview.h"

namespace sampleride
{

    Preview::Preview(QWidget* parent, Classes* _classes) : QWidget(parent)
    {
        classes = _classes;
        setMinimumSize(QSize(classes->model().base_size().x(), classes->model().base_size().y()));
        //setStyleSheet("background-color: #ffffff;");
        QPalette pal = QPalette();
        pal.setColor(QPalette::Window, QColor(40, 40, 40));
        setAutoFillBackground(true);
        setPalette(pal);
    }

    void Preview::paintEvent(QPaintEvent* event)
    {
        QPainter qp(this);
        qp.setRenderHint(QPainter::Antialiasing);

        int modules_num = int(classes->model().table_size().width() / classes->model().module_size().x());

        for (int i = 0; i < modules_num; i++)
        {
            qp.setPen(QPen(QBrush(QColor(100 * i, 240 - 20 * i, 120 * i)), 2));
            qp.drawRect(QRectF(i * (classes->model().module_size().x() + classes->model().module_spacing().x()),
                               classes->model().module_spacing().y(), classes->model().module_size().x(), classes->model().module_size().y()));
        }
    }
} // namespace sampleride