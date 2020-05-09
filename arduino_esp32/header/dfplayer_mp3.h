#pragma once

#include <BLEServer.h>
#include <Arduino.h>
#include <DFRobotDFPlayerMini.h>
#include <HardwareSerial.h>

#include "../header/ble.h"

#define UUID_VOLUME "9c4482c2-eeb4-11e9-81b4-2a2ae2dbcce4"
#define UUID_PLAY "9c4482c1-eeb4-11e9-81b4-2a2ae2dbcce4"
#define FILE_COUNT "9c4482c3-eeb4-11e9-81b4-2a2ae2dbcce4"

#define MAX_VOLUME 20

class DFPlayer {
	HardwareSerial m_serial;
public:
	DFPlayer(BleManager* pServer);
	~DFPlayer();
	static void play(BLECharacteristic* pCharacteristic, void* param);
	static void volume_changed(BLECharacteristic* pCharacteristic, void* param);
private:
	DFRobotDFPlayerMini m_dfplayer;
};
