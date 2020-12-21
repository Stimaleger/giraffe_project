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

void bleClient::connect() {
    m_controller = new QLowEnergyController(QBluetoothAddress(ESP32_MAC_ADDRESS), this);

    // This is a public BLE MAC address
    m_controller->setRemoteAddressType(QLowEnergyController::PublicAddress);

    if (!m_controller)
        qErrnoWarning("Could not created ble controller");

    // Connect all slots
    QObject::connect(m_controller, &QLowEnergyController::serviceDiscovered, this, &bleClient::addService);
    QObject::connect(m_controller, &QLowEnergyController::connected, this, [this]() {
        m_controller->discoverServices();
        m_state_connection = true;
        emit connected();
    });
    QObject::connect(m_controller, &QLowEnergyController::disconnected, this, [this]() {
        qDebug() << Q_FUNC_INFO;
        m_state_connection = false;
        emit connected();
    });
    m_controller->connectToDevice();
}

void bleClient::disconnect() {
    qDebug() << Q_FUNC_INFO << "Disconnecting from device ...";
    m_controller->disconnectFromDevice();
}

void bleClient::play(const QByteArray &data) {
    if (m_state_connection && m_service) {
        m_service->writeCharacteristic(m_service->characteristic(QBluetoothUuid(QString(PLAY_CHARACTERISTIC))), QByteArray(data), QLowEnergyService::WriteWithoutResponse);
        m_service->writeCharacteristic(m_service->characteristic(QBluetoothUuid(QString(LED_CHARACTERISTIC))), QByteArray("2"), QLowEnergyService::WriteWithoutResponse);
    }
}

void bleClient::set_volume(const QByteArray &data) {
    if (m_state_connection && m_service) {
        qDebug() << data;
        m_service->writeCharacteristic(m_characteristic, data, QLowEnergyService::WriteWithoutResponse);
    }
}

void bleClient::addService(QBluetoothUuid serviceUuid) {
    qDebug() << Q_FUNC_INFO  << serviceUuid.toString();
    if (serviceUuid.toString() == MY_BLE_SERVICE) {
        m_service = m_controller->createServiceObject(serviceUuid);
        qDebug() << "Found dfplay service";
        if (m_service->state() == QLowEnergyService::DiscoveryRequired) {
            // Connect signal when characteristic change
            QObject::connect(m_service, &QLowEnergyService::stateChanged, this, &bleClient::serviceStateChange);
        } else {
            qDebug() << Q_FUNC_INFO << m_service->state();
        }
        m_service->discoverDetails();
    }
}

void bleClient::serviceStateChange(QLowEnergyService::ServiceState newState) {
    qDebug() << Q_FUNC_INFO << newState;
    if (newState != QLowEnergyService::ServiceDiscovered) return;

    QLowEnergyService *service = qobject_cast<QLowEnergyService *>(sender());

    qDebug() << Q_FUNC_INFO << service->serviceUuid().toString();
    if (service->serviceUuid().toString() == MY_BLE_SERVICE) {
        foreach (QLowEnergyCharacteristic c, service->characteristics()) {
            qDebug() << Q_FUNC_INFO << "characteristic " << c.uuid().toString();
            if (c.uuid().toString() == VOLUME_CHARACTERISTIC) {
                m_characteristic = c;
            }
            qDebug() << Q_FUNC_INFO << "my characteristic" << c.uuid().toString() << c.properties();
        }
    }
}
