#include <Arduino.h>
#include "../header/ble.h"


static std::vector<BleCharac*> m_vect_charact;


BleCharac::BleCharac(char* p_uuid_charac, Callback p_write_cb, Callback p_read_cb, void* param) : m_uuid_charac(p_uuid_charac) {
	m_write_cb = p_write_cb;
	m_read_cb = p_read_cb;
	m_param = param;
}

void BleCallack::onWrite(BLECharacteristic* pCharacteristic) {
	/* Parse all BleCharac objects stored in vector and execute callback for this characteristic */
	for(std::size_t i = 0; i < m_vect_charact.size(); ++i) {
		if (pCharacteristic->getUUID().toString() == m_vect_charact[i]->m_uuid_charac) {
			m_vect_charact[i]->m_read_cb(pCharacteristic, m_vect_charact[i]->m_param);
		}
	}
}

void BleCallack::onRead(BLECharacteristic* pCharacteristic) {
	Serial.println("BLE read event");
}

void BleManager::init() {
	m_service = createService(MY_SERVICE);
	m_callback = new BleCallack();
}

void BleManager::populate_ble(char* p_uuid_charac, Callback p_write_cb, Callback p_read_cb, void* param) {
	BLECharacteristic* m_charact = m_service->createCharacteristic(p_uuid_charac, BLECharacteristic::PROPERTY_READ |BLECharacteristic::PROPERTY_WRITE);
	m_charact->setCallbacks(m_callback);
	m_vect_charact.push_back(new BleCharac(p_uuid_charac, p_write_cb, p_read_cb, param));
	Serial.println(m_vect_charact.back()->m_uuid_charac.c_str());
}

void BleManager::start() {
	// Start service
	m_service->start();
	// Start ble advertising
	Serial.println("Starting ble advertising");
	startAdvertising();
}
