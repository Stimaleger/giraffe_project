#include "../header/bleclient.h"

#include <QDebug>

bleClient::bleClient() : m_controller(nullptr), m_service(nullptr), m_state_connection(false), m_volume(0)
{
    qDebug("Initializing ble client");
}

bleClient::~bleClient() {
    qDebug("Killing all bleClient");
    if (m_controller) {
        m_controller->disconnectFromDevice();
    }
    delete m_controller;
    qDeleteAll(m_devices);
}

void bleClient::connectDevice() {
    m_controller = new QLowEnergyController(QBluetoothAddress(ESP32_MAC_ADDRESS), this);

    // This is a public BLE MAC address
    m_controller->setRemoteAddressType(QLowEnergyController::PublicAddress);

    if (!m_controller)
        qErrnoWarning("Could not created ble controller");

    // Connect all slots
    QObject::connect(m_controller, &QLowEnergyController::serviceDiscovered, this, &bleClient::addService);
    QObject::connect(m_controller, &QLowEnergyController::connected, this, &bleClient::connectedDevice);
    QObject::connect(m_controller, &QLowEnergyController::disconnected, this, &bleClient::disconnectedDevice);

    m_controller->connectToDevice();
}


void bleClient::addService(QBluetoothUuid serviceUuid) {
    qDebug() << Q_FUNC_INFO  << serviceUuid.toString();
    m_service = m_controller->createServiceObject(serviceUuid);

    if (m_service->state() == QLowEnergyService::DiscoveryRequired) {
        // Connect signal when characteristic change
        QObject::connect(m_service, &QLowEnergyService::characteristicChanged, this, &bleClient::serviceCharacteristicChanged);
        // Connect signal when characteristic change
        QObject::connect(m_service, &QLowEnergyService::stateChanged, this, &bleClient::serviceStateChange);
    } else {
        qDebug() << Q_FUNC_INFO << m_service->state();
    }
}

void bleClient::connectedDevice() {
    qDebug() << Q_FUNC_INFO;
    m_controller->discoverServices();
}

void bleClient::disconnectedDevice() {
    qDebug() << Q_FUNC_INFO;
    m_state_connection = false;
    emit connected();
}
