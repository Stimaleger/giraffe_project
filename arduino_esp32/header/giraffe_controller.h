#pragma once

#include <BLEUtils.h>
#include <BLEServer.h>

#include "../header/dfplayer_mp3.h"
#include "../header/led_controller.h"

#define SERVICE_CONTROLLER "232ebdf0-238d-4810-87ce-a12283bfa992"
#define BLE_CHR_RESET "9c4482d0-eeb4-11e9-81b4-2a2ae2dbcce4"

class GiraffeController : public BLEServerCallbacks {
QueueHandle_t m_queue;
public:
	~GiraffeController();
	void onConnect(BLEServer* pServer);
	void onDisconnect(BLEServer* pServer);
	void init();
private:
	BleManager* m_ble_server;
	DFPlayer* m_dfplayer;
	LedController* m_led_controller;
};
