#pragma once

#include <BLEUtils.h>
#include <BLEServer.h>

#include "../header/dfplayer_mp3.h"
#include "../header/led_controller.h"

class GiraffeController {
public:
	GiraffeController();
	~GiraffeController();
	void init();
private:
	BLEServer* m_ble_server;
	DFPlayer* m_dfplayer;
	LedController* m_led_controller;
};

class StateBleServer: public BLEServerCallbacks {
public:
	StateBleServer(LedController* led_controller, DFPlayer* dfplayer);
	void onConnect(BLEServer* pServer);
	void onDisconnect(BLEServer* pServer);
private:
	DFPlayer* m_dfplayer;
	LedController* m_led_controller;
};
