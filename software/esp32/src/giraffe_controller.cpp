#include <BLEDevice.h>
#include "Arduino.h"
#include "../header/giraffe_controller.h"

void GiraffeController::onConnect(BLEServer* pServer) {
	e_patterns pattern = POSITIVE;
	xQueueSend(m_queue, &pattern, portMAX_DELAY);
}

void GiraffeController::onDisconnect(BLEServer* pServer) {
	e_patterns pattern = NEGATIVE;
	xQueueSend(m_queue, &pattern, portMAX_DELAY);
}

GiraffeController::~GiraffeController() {
	delete m_led_controller;
	delete m_dfplayer;
}

void GiraffeController::init() {
	Serial.println("Initializing giraffe controller");
	e_patterns pattern = POSITIVE;

	/* Create BLE server */ 
	m_ble_server = static_cast<BleManager*>(BLEDevice::createServer());
	m_ble_server->init();
	m_ble_server->setCallbacks(this);

	/* Create DFPlayer */
	m_dfplayer = new DFPlayer(m_ble_server);

	/* Create LedController */
	m_queue = xQueueCreate(4, sizeof(e_patterns));
	m_led_controller = new LedController(&m_queue, m_ble_server);

	/* Enable BLE */
	m_ble_server->start();
	xQueueSend(m_queue, &pattern, portMAX_DELAY);
}
