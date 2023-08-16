//
// Created by Flynn on 09.08.2023.
//

#include "server.h"

namespace sampleride
{
    Server::Server(QObject* parent) : QThread(parent)
    {

    }

    SamSerial::SamSerial(QObject* parent) : Server(parent), wait_timeout(100), exit(false), port_name("tty.usbmodem2075324E42421")
    {

    }

    void SamSerial::move(QVector3D src, QVector3D dst)
    {
        QString res = QString("G1 X%1 Y%2 Z%3\n").arg(QString::number(int(dst.x())), QString::number(int(dst.y())), QString::number(int(dst.z())));
        send_gcode(res);
    }

    void SamSerial::run()
    {
        mut.lock();

        QString curPayload = payload;

        mut.unlock();

        QSerialPort serial;

        if (port_name.isEmpty())
        {
            std::cout << "Port is empty" << std::endl;
            return;
        }

        serial.setPortName(port_name);
        if (!serial.open(QIODevice::ReadWrite))
        {
            std::cout << tr("Can't open %1, error code %2").arg(port_name).arg(serial.error()).toStdString() << std::endl;
            return;
        }

        while(!exit)
        {
            const QByteArray request = curPayload.toUtf8();
            serial.write(request);

            if (serial.waitForBytesWritten(wait_timeout))
            {

            }
            else
            {
                std::cout << tr("Wait write request timeout %1").arg(QTime::currentTime().toString()).toStdString() << std::endl;
            }

            mut.lock();

            wait_cond.wait(&mut);
            curPayload = payload;

            mut.unlock();
        }
    }

    SamSerial::~SamSerial() noexcept
    {
        mut.lock();
        exit = true;
        wait_cond.wakeOne();
        mut.unlock();
        wait();
    }

    void SamSerial::home()
    {
        QString res = "G28\n";
        send_gcode(res);
    }

    void SamSerial::send_gcode(QString &s)
    {
        const QMutexLocker locker(&mut);
        payload = s;
        if (!isRunning())
            start();
        else
            wait_cond.wakeOne();
    }

    void SamSerial::halt()
    {
        QString res = "M18\n";
        send_gcode(res);
    }
} // sampleride