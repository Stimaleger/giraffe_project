#pragma once

#include <BLEServer.h>
#include <string>
#include <functional>

#define BLE_READ	BLECharacteristic::PROPERTY_READ
#define BLE_WRITE	BLECharacteristic::PROPERTY_WRITE


typedef std::function<void(BLECharacteristic* pCharacteristic, void* param)> Callback;

class BleCharac {
public:
	BleCharac(char* p_uuid_charac, Callback p_write_cb, Callback p_read_cb, void* param);	
	std::string m_uuid_charac;
	Callback m_write_cb;
	Callback m_read_cb;
	void* m_param;
};

class BleCallack : public BLECharacteristicCallbacks {
public:
	void onWrite(BLECharacteristic* pCharacteristic);
	void onRead(BLECharacteristic* pCharacteristic);
};

class BleManager : public BLEServer {
public:
	void populate_ble(char* p_uuid_charac, Callback p_write_cb, Callback p_read_cb, void* param, int ble_properties = BLE_READ|BLE_WRITE); 
    void start();
    void init();
private:
	BLEService* m_service;
	BleCallack* m_callback;
};
