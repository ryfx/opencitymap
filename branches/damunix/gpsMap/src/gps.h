//
// C++ Interface: gps
//
// Description: 
//
//
// Author: wolfgang Ostes <wolfostes@hotmail.com>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef GPS_H
#define GPS_H

#include <QString>
#include <QDialog>
#include <QString>
#include <QStringList>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QProcess>
#include <QObject>
#include <QTimer>
#include <QMessageBox>


#include "QBluetoothRfcommSerialPort"

#include <QBluetoothAbstractService>
#include <QBluetoothRfcommSocket>
#include <QBluetoothRfcommServer>
#include <QBluetoothLocalDevice>
#include <QBluetoothAddress>
#include <QBluetoothLocalDeviceManager>
#include <QBluetoothRemoteDevice>
#include <QBluetoothRemoteDeviceDialog>
#include <QBluetoothSdpQuery>
/**
	@author wolfgang Ostes <wolfostes@hotmail.com>
*/
#include <QPointF>

class GPS : public QObject
{
        Q_OBJECT
    public:
        GPS();
        double getLongitude();
        double getLatitude();
        double ddMmtoDd(QString);
        double getAltitude();
//         bool updatePosition();
        QString getTime();
        void gpsDisconnect();
        void fake(bool);
        ~GPS();
    private:
        void connectGPSModule(QBluetoothAddress addrGPS,int);
        bool getCheck(QString);
        void emitNewPosition();

        QBluetoothRfcommSerialPort* GPSModule;
        QBluetoothRfcommSocket*     rfcommSocket;
        QBluetoothRemoteDeviceDialog *BLdialog;
        QBluetoothLocalDevice*      localDevice;
        QBluetoothSdpQuery*         m_sdap;
        QBluetoothAddress* m_GPSModule;
        QFile*   m_file;
        QTextStream* in;
        QProcess* NMEAProcess;
        double  m_latitude,m_latitudePrevious;
        double  m_longitude,m_longitudePrevious;
        double  m_elevation;
        double  m_altitude;
        bool    m_fake;
        QString m_time;
        int m_divider;

    private slots:
        void updatePosition();
        void updateFakePosition();
        void messageConnected(QString);
        void searchCompleted(const QBluetoothSdpQueryResult &);
        void connectionLost();
        void connectionError(QBluetoothRfcommSerialPort::Error);
        void NMEAProcessError(QProcess::ProcessError);
        void NMEAProcessOutputError();
        void NMEAProcessExit(int exitCode, QProcess::ExitStatus status);

    public slots:
        void selectGPSDevice();

    signals:
        void new_position(QPointF);
};

//#endif

class GPGGA
 {
 public:
    enum Option {
        GPGA = 0x00,
        Time = 0x01,
        Latitude = 0x02,
        Longitude = 0x04,
        Quality = 0x06,
        Satellites = 0x07,
        Dilution = 0x08,
        Altitude = 0x09,
        Height = 0x0A,
        Checksum = 0x0D,
     };
     Q_DECLARE_FLAGS(Options, Option)
};
Q_DECLARE_OPERATORS_FOR_FLAGS(GPGGA::Options)

class GPRMC
 {
 public:
    enum Option {
        TYPE = 0x00,
        Time = 0x01,
        Latitude = 0x03,
        Longitude = 0x05,
        Quality = 0x06,
        Speed = 0x07,
        Dilution = 0x08,
        Altitude = 0x09,
     };
     Q_DECLARE_FLAGS(Options, Option)
};
Q_DECLARE_OPERATORS_FOR_FLAGS(GPRMC::Options)

#endif
