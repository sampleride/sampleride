//
// Created by Flynn on 09.08.2023.
//

#ifndef SAMPLERIDE_SERVER_H
#define SAMPLERIDE_SERVER_H

#include <QObject>
#include <QThread>
#include <QVector3D>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QMutex>
#include <QWaitCondition>
#include <QTime>

#include <iostream>

namespace sampleride
{

    class Server : public QThread
    {
        Q_OBJECT
    public:
        explicit Server(QObject* parent = nullptr);
        virtual void move(QVector3D src, QVector3D dst) = 0;

    protected:
        QMutex mut;
        QWaitCondition wait_cond;
    };

    class SamSerial : protected Server
    {
        Q_OBJECT
    public:
        explicit SamSerial(QObject* parent = nullptr);
        ~SamSerial() noexcept override;
        void move(QVector3D src, QVector3D dst) override;

    protected:
        void run() override;

        QString port_name;
        QString payload;
        int wait_timeout;
        bool exit;
    };

} // namespace sampleride

#endif //SAMPLERIDE_SERVER_H
