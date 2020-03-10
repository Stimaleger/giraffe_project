#pragma once

#include <QLowEnergyController>


#define ESP32_MAC_ADDRESS  "XX:XX:XX:XX:XX:XX"  // TODO add ble mac address


class bleClient: QObject
{
    Q_OBJECT
    Q_PROPERTY(bool state_connection MEMBER m_state_connection NOTIFY connect)
    Q_PROPERTY(bool volume MEMBER m_volume NOTIFY volumeChange)

public:
    bleClient();
    ~bleClient();
    Q_INVOKABLE void setVolume();
    Q_INVOKABLE void connect();
    Q_INVOKABLE void disconnect();

protected:
    void connectDevice();
    void connectService(QLowEnergyService *service);
    void addService(QBluetoothUuid serviceUuid);
    void serviceStateChange(QLowEnergyService::ServiceState newState);
    void serviceCharacteristicChanged(const QLowEnergyCharacteristic &c, const QByteArray &value);
    void connectedDevice();
    void disconnectedDevice();

private:
    QList<QObject*> m_devices;
    QLowEnergyController            *m_controller;
    QLowEnergyService               *m_service;
    bool                             m_state_connection;
    int                              m_volume;
    QLowEnergyCharacteristic         m_characteristic;

signals:
    void connected();
};
