#pragma once

#include <BLEServer.h>
#include <Arduino.h>
#include <DFRobotDFPlayerMini.h>
#include <HardwareSerial.h>

#define DFPLAYER_SERVICE "232ebdf8-238d-4810-87ce-a12283bfa992"
#define UUID_VOLUME "9c4482c2-eeb4-11e9-81b4-2a2ae2dbcce4"
#define UUID_PLAY "9c4482c1-eeb4-11e9-81b4-2a2ae2dbcce4"

class VolumeCallback : public BLECharacteristicCallbacks {
public:
	VolumeCallback(DFRobotDFPlayerMini* myDFPlayer);
    void onWrite(BLECharacteristic* pCharacteristic);
    void onRead(BLECharacteristic* pCharacteristic);

private:
	DFRobotDFPlayerMini m_dfplayer;
};

class PlayCallback : public BLECharacteristicCallbacks {
public:
	PlayCallback(DFRobotDFPlayerMini* myDFPlayer);
    void onWrite(BLECharacteristic* pCharacteristic);
    void onRead(BLECharacteristic* pCharacteristic);

private:
	DFRobotDFPlayerMini m_dfplayer;
};

class DFPlayer {
	HardwareSerial m_serial;
public:
	DFPlayer(BLEServer* pServer);
	~DFPlayer();

private:
	DFRobotDFPlayerMini m_dfplayer;
	BLEService *m_service;
	BLECharacteristic* m_characteristic_vol;
	BLECharacteristic* m_play;
};
