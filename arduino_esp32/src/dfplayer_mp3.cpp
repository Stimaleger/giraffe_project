#include <string>
#include "../header/dfplayer_mp3.h"

VolumeCallback::VolumeCallback(DFRobotDFPlayerMini* myDFPlayer) {
	m_dfplayer = myDFPlayer;
}

void VolumeCallback::onWrite(BLECharacteristic* pCharacteristic) {
	std::string str_value = pCharacteristic->getValue();
	int int_value = int(str_value.c_str());
	Serial.print("Setting volume to ");
	Serial.println(str_value.c_str());

	if (int_value >= 30) {
		m_dfplayer->volume(30);
	}
	else {
		m_dfplayer->volume(int_value);
	}
}

void VolumeCallback::onRead(BLECharacteristic* pCharacteristic) {
}

PlayCallback::PlayCallback(DFRobotDFPlayerMini* myDFPlayer) {
	m_dfplayer = myDFPlayer;
}

void PlayCallback::onWrite(BLECharacteristic* pCharacteristic) {
	Serial.print(m_dfplayer->readVolume());
}

void PlayCallback::onRead(BLECharacteristic* pCharacteristic) {}

DFPlayer::DFPlayer(BLEServer* pServer) {
	HardwareSerial serial(1);
	DFRobotDFPlayerMini* m_dfplayer = new DFRobotDFPlayerMini();
	m_service = pServer->createService(DFPLAYER_SERVICE);

	/* Create DFPlayer */
	serial.begin(9600, SERIAL_8N1, 16, 17);  					// speed, type, RX, TX
	Serial.println("Initializing DFPlayer module");
	if (!m_dfplayer->begin(serial, false)) {  					//Use HardwareSerial to communicate with DFPlayer.
	    Serial.println("Unable to begin:");
	    Serial.println("Check SD card");
		while(true){
			delay(0);
		}
  	}
  	m_dfplayer->setTimeOut(500); 								// Set serial communictaion timeout to 500ms
  	m_dfplayer->EQ(DFPLAYER_EQ_NORMAL); 						// Set EQ to normal
  	m_dfplayer->outputDevice(DFPLAYER_DEVICE_SD); 				// Set device we use SD as default
  	m_dfplayer->volume(15); 									// Set volume to 15 by default
  	Serial.println("DFPlayer module correctly initialized");

	/* Create volume characteristic */
	m_characteristic_vol = m_service->createCharacteristic(UUID_VOLUME, 
						                                  BLECharacteristic::PROPERTY_READ | 
						                                  BLECharacteristic::PROPERTY_WRITE);
	m_characteristic_vol->setCallbacks(new VolumeCallback(m_dfplayer));

	m_play = m_service->createCharacteristic(UUID_PLAY, 
			                                  BLECharacteristic::PROPERTY_READ | 
			                                  BLECharacteristic::PROPERTY_WRITE);

	m_play->setCallbacks(new PlayCallback(m_dfplayer));

	m_service->start();
}
