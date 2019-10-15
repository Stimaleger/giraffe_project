#include <BLEDevice.h>
#include "Arduino.h"
#include "../header/giraffe_controller.h"

GiraffeController::GiraffeController() {
	Serial.println("I'm the constructor of GiraffeController");
}

GiraffeController::~GiraffeController() {
	Serial.println("I'm the destructor of GiraffeController");
}

void GiraffeController::init() {
	Serial.println("Initializing giraffe controller");

	/* Create BLE server */ 
	m_ble_server = BLEDevice::createServer();

	/* Create DFplayer */
	m_dfplayer = new DFPlayer(m_ble_server);

	/* Enable BLE */
	m_ble_server->getAdvertising()->start();
}
