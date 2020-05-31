#pragma once
#include <BLEServer.h>
#include <Arduino.h>
#include <DFRobotDFPlayerMini.h>
#include <HardwareSerial.h>

#include "../header/ble.h"

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
