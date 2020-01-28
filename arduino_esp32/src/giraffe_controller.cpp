#include <BLEDevice.h>
#include "Arduino.h"
#include "../header/giraffe_controller.h"

StateBleServer::StateBleServer(LedController* p_led_controller, DFPlayer* p_dfplayer) {
	m_dfplayer = p_dfplayer;
	m_led_controller = p_led_controller;
}

void StateBleServer::onConnect(BLEServer* pServer) {
	Serial.println("We are connected");
	m_led_controller->run_positive_pattern();
}

void StateBleServer::onDisconnect(BLEServer* pServer) {
	Serial.println("We are disconnected");
}

GiraffeController::GiraffeController() {}

GiraffeController::~GiraffeController() {
	delete m_led_controller;
	delete m_dfplayer;
}

void GiraffeController::init() {
	Serial.println("Initializing giraffe controller");

	/* Create BLE server */ 
	m_ble_server = BLEDevice::createServer();

	/* Create DFPlayer */
	m_dfplayer = new DFPlayer(m_ble_server);

	/* Create LedController */
	m_led_controller = new LedController();

	/* Enable BLE */
	m_ble_server->setCallbacks(new StateBleServer(m_led_controller, m_dfplayer));
	m_ble_server->getAdvertising()->start();
}
