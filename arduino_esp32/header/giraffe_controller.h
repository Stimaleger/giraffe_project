#pragma once

#include <BLEUtils.h>
#include <BLEServer.h>

#include "../header/dfplayer_mp3.h"

class GiraffeController {

public:
	GiraffeController();
	~GiraffeController();

	void init();

private:
	BLEServer* m_ble_server;
	DFPlayer* m_dfplayer;
};
