//
// C++ Implementation: gps
//
// Description: 
//
//
// Author: wolfgang Ostes <wolfostes@hotmail.com>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "gps.h"

GPS::GPS()
{
    QBluetoothLocalDeviceManager mgr; // find bluetooth local adapter
    QString device = mgr.defaultDevice();
    localDevice = new QBluetoothLocalDevice(device);
    NMEAProcess = new QProcess();

//     rfcommSocket = new QBluetoothRfcommSocket(); 
    GPSModule   = new QBluetoothRfcommSerialPort(); // rfcommSocket,QBluetoothRfcommSerialPort::KeepAlive
    if (device.isEmpty()) // No GPS adapter found
    {
        qDebug()<<"No GPS adapter found";
    }
}
void GPS::connectGPSModule(QBluetoothAddress addrGPS, int channel)
{
    m_fake = false;
    if (GPSModule->connect(localDevice->address() ,addrGPS,channel)) 
    {
        connect(GPSModule,SIGNAL(connected(QString)),   this, SLOT(messageConnected(QString)));
        connect(GPSModule,SIGNAL(disconnected()),       this, SLOT(connectionLost() ));
        connect(GPSModule,SIGNAL(error(QBluetoothRfcommSerialPort::Error)),this,SLOT( connectionError(QBluetoothRfcommSerialPort::Error) ));
    }
    else 
    {
        QMessageBox::warning(0, tr("Bluetooth"),
                             "<qt>" + tr("Could not connect to the remote service!") + "</qt>",
                             QMessageBox::Ok, QMessageBox::NoButton, QMessageBox::NoButton);
    }
}
void GPS::updatePosition()
{
    QByteArray GPSData( NMEAProcess->readAllStandardOutput());
 
    QString strGPS(GPSData);
    if (getCheck(strGPS))
    {
        QStringList GPSList= strGPS.split(",");

        if (GPSList.size()>8 && GPSList.at(GPGGA::GPGA) =="$GPGGAkk") // ??? 
        {
                        m_latitude  = ddMmtoDd( GPSList.at(GPGGA::Latitude));
                        m_longitude = ddMmtoDd( GPSList.at(GPGGA::Longitude));
                        m_time      = GPSList.at(GPGGA::Time);
                        m_altitude  = GPSList.at(GPGGA::Altitude).toDouble();
                        emitNewPosition();
        }
        else if (GPSList.size()>8 && GPSList.at(GPRMC::TYPE) =="$GPRMC") 
        {
                        m_latitude   = ddMmtoDd( GPSList.at(GPRMC::Latitude) );
                        m_longitude  = ddMmtoDd( GPSList.at(GPRMC::Longitude) );
                        m_time       = GPSList.at(GPRMC::Time);
                        m_altitude   = GPSList.at(GPRMC::Altitude).toDouble();
                        emitNewPosition();
        }
    }
    else
        qDebug()<<"NMEA check fail";
}
void GPS::emitNewPosition()
{
    if ((m_longitude || m_latitude))
    {
        qDebug()<<"emit GPS x:"<<m_longitude<<"y:"<<m_latitude<<" Time:"<<m_time;
        emit(new_position(QPointF(m_longitude,m_latitude)));
    }
    else
       qDebug()<<"Position not changed "<<" Time:"<<m_time;
    m_longitudePrevious = m_longitude;
    m_latitudePrevious = m_latitude;
}
bool GPS::getCheck(QString sentence)
{
    unsigned char Checksum = 0;
    int checksumNMEA=0;
//      qDebug()<<"nmea sentance:"<<sentence;
    for(int loop=0;loop<sentence.size();loop++)
    {
        QChar Character2=sentence[loop];
        unsigned char Character = Character2.unicode();
        if (Character == '$')
        {
            // Ignore the dollar sign
        }
        else if (Character == '*')
        {
            QString str;
            str.resize(2);
            str[0] = QChar(sentence[loop+1]);
            str[1] = QChar(sentence[loop+2]);
            checksumNMEA=str.toInt(0,16);
            return true;
        }
        else
        {
            // Is this the first value for the checksum?
            if (Checksum == 0)
            {
                Checksum = Character;
            }
            else
            {
                Checksum = Checksum ^ Character;
            }
        }
    }
//     qDebug()<<"sentance::"<<sentence<<"::checksum::"<<Checksum<<"::"<<checksumNMEA;
    return false;
}
void GPS::NMEAProcessError(QProcess::ProcessError)
{
    qDebug()<<"GPS Process Error";
}
void GPS::NMEAProcessOutputError()
{
    QByteArray GPSData( NMEAProcess->readAllStandardOutput());
    QString strGPS(GPSData);
    qDebug()<<"OutputError :"<<strGPS;
}
void GPS::NMEAProcessExit(int exitCode, QProcess::ExitStatus status)
{
    if (QProcess::CrashExit==status) //Connection Error occurred
        qDebug()<<"crash exit";
    if (QProcess::NormalExit==status)
        qDebug()<<"QProcess::NormalExit";

    QMessageBox::warning(0, tr("Bluetooth"),
                             "<qt>" + tr("Connection Error occurred!") + "</qt>",
                             QMessageBox::Ok, QMessageBox::NoButton, QMessageBox::NoButton);
}
void GPS::messageConnected(QString device)
{
    qDebug()<<"Buetooth GPS signal Connected on channel:"<<GPSModule->remoteChannel();
    QMessageBox::warning(0, tr("Bluetooth"),"<qt>"+tr("connected")+"</qt>",
                          QMessageBox::Ok, QMessageBox::NoButton);

    NMEAProcess->start("cat "+GPSModule->device());
    connect(NMEAProcess,SIGNAL(error(QProcess::ProcessError)),  this, SLOT(NMEAProcessError(QProcess::ProcessError)));
    connect(NMEAProcess,SIGNAL(readyReadStandardOutput()),      this, SLOT(updatePosition()));
    connect(NMEAProcess,SIGNAL(readyReadStandardError()),       this, SLOT(NMEAProcessOutputError()));
    connect(NMEAProcess,SIGNAL(finished(int, QProcess::ExitStatus)),       this, SLOT(NMEAProcessExit(int, QProcess::ExitStatus)));
}
void GPS::connectionLost()
{
    qDebug()<<"disconnected";
}
void GPS::connectionError(QBluetoothRfcommSerialPort::Error)
{
    qDebug()<<"connection error";
    QMessageBox::warning(0, tr("Bluetooth"),"<qt>"+tr("Unable to connect.  Please ensure the Bluetooth device is in range and try again.")+"</qt>",
                          QMessageBox::Ok, QMessageBox::NoButton, QMessageBox::NoButton);
}
void GPS::searchCompleted(const QBluetoothSdpQueryResult &result)
{
    int channel = -1;
    foreach (QBluetoothSdpRecord record, result.services()) {
        if (record.isInstance(QBluetooth::SerialPortProfile)) {
            channel = QBluetoothSdpRecord::rfcommChannel(record);
            break;
        }
    }
    if (channel == -1) 
    {
        QMessageBox::warning(0, tr("Bluetooth"),
                             "<qt>"+tr("The selected device does not support this service!")+"</qt>",
                             QMessageBox::Ok, QMessageBox::NoButton, QMessageBox::NoButton);
    }
    else
         connectGPSModule(*m_GPSModule,channel);
}
void GPS::selectGPSDevice()
{
    qDebug()<<"select new device";
    gpsDisconnect();
    QSet<QBluetooth::SDPProfile> profiles;
    m_GPSModule = new QBluetoothAddress (QBluetoothRemoteDeviceDialog::getRemoteDevice(0, profiles));

    if (m_GPSModule->isValid()) 
    {
        m_sdap = new QBluetoothSdpQuery(this);
        connect(m_sdap,SIGNAL(searchComplete(QBluetoothSdpQueryResult)),
                this, SLOT(searchCompleted(QBluetoothSdpQueryResult)));
        qDebug()<<"searchservices";
        m_sdap->searchServices(*m_GPSModule, *localDevice, QBluetooth::SerialPortProfile);
    }
    else
        qDebug()<<"invalid bluetooth Device";
}
void GPS::gpsDisconnect()
{
    NMEAProcess->kill();
    disconnect(NMEAProcess,0,0,0);
    disconnect(GPSModule,0,0,0);
    m_longitudePrevious=m_latitudePrevious=0;
     if (GPSModule->disconnect())
         qDebug()<<"disconnected";
}
void GPS::fake(bool fake)
{
    m_fake = fake;
    m_longitude = 4.47;//8.2606;
    m_latitude = 51.02;//50.0051;
    if (fake)
        updateFakePosition();
}
void GPS::updateFakePosition()
{
    m_latitude+=0.0001;
    m_longitude+=0.0001;
    emit(new_position(QPointF(m_longitude,m_latitude)));
    if (m_fake)
        QTimer::singleShot(300, this, SLOT(updateFakePosition())); 
}
double GPS::ddMmtoDd( QString data )
{
    double deg, min, sec;
    int decimalPoint = data.indexOf(".");

    deg = data.mid(decimalPoint-4,2).toDouble();
    min = data.mid(decimalPoint-2,2).toDouble();
    sec = data.mid(decimalPoint,4).toDouble();

    return deg + min/60 +sec/60;
}
double GPS::getLatitude()
{
    return m_latitude;
}
double GPS::getLongitude()
{
    return m_longitude;
}
double GPS::getAltitude()
{
    return m_altitude;
}
QString GPS::getTime()
{
    return m_time;
}
GPS::~GPS()
{

}