#pragma once

#include <QLowEnergyController>

#define ESP32_MAC_ADDRESS       "A4:CF:12:63:11:D2"
#define MY_BLE_SERVICE          "{232ebdf8-238d-4810-87ce-a12283bfa992}"
#define VOLUME_CHARACTERISTIC   "{9c4482c2-eeb4-11e9-81b4-2a2ae2dbcce4}"
#define PLAY_CHARACTERISTIC     "{9c4482c1-eeb4-11e9-81b4-2a2ae2dbcce4}"
#define LED_CHARACTERISTIC      "{9c4482d1-eeb4-11e9-81b4-2a2ae2dbcce4}"


class bleClient: public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool state_connection MEMBER m_state_connection NOTIFY connected)

public:
    bleClient();
    ~bleClient();
    Q_INVOKABLE void connect();
    Q_INVOKABLE void disconnect();
    Q_INVOKABLE void play(const QByteArray &data);
    Q_INVOKABLE void set_volume(const QByteArray &data);

protected:
    void connectService(QLowEnergyService *service);
    void addService(QBluetoothUuid serviceUuid);
    void serviceStateChange(QLowEnergyService::ServiceState newState);
    void connectedDevice();
    void disconnectedDevice();

private:
    QList<QObject*>                 m_devices;
    QLowEnergyController            *m_controller;
    QLowEnergyService               *m_service;
    bool                             m_state_connection;
    int                              m_volume;
    QLowEnergyCharacteristic         m_characteristic;

signals:
    void connected();
};
