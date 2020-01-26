#include <BLEDevice.h>
#include "Arduino.h"
#include "../header/giraffe_controller.h"

void StateBleServer::onConnect(BLEServer* pServer) {
	Serial.println("We are connected");
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
	m_ble_server->setCallbacks(new StateBleServer());

	/* Create DFPlayer */
	m_dfplayer = new DFPlayer(m_ble_server);

	/* Create LedController */
	m_led_controller = new LedController();

	/* Enable BLE */
	m_ble_server->getAdvertising()->start();
}
