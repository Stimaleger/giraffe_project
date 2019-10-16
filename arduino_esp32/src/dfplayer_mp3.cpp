#include <string>
#include "../header/dfplayer_mp3.h"

VolumeCallback::VolumeCallback(DFRobotDFPlayerMini* myDFPlayer) {
	m_dfplayer = *myDFPlayer;
}

void VolumeCallback::onWrite(BLECharacteristic* pCharacteristic) {
	String value = pCharacteristic->getValue().c_str();

	Serial.print("Setting volume to: ");
	Serial.println(value);
	m_dfplayer.volume(value.toInt());
}

void VolumeCallback::onRead(BLECharacteristic* pCharacteristic) {}

PlayCallback::PlayCallback(DFRobotDFPlayerMini* myDFPlayer) {
	m_dfplayer = *myDFPlayer;
}

void PlayCallback::onWrite(BLECharacteristic* pCharacteristic) {
	m_dfplayer.play(1);
}

void PlayCallback::onRead(BLECharacteristic* pCharacteristic) {}

DFPlayer::DFPlayer(BLEServer* pServer) : m_serial(1) {
	/* Create DFPlayer */
	m_serial.begin(9600, SERIAL_8N1, 16, 17);  				// speed, type, RX, TX
	Serial.println("Initializing DFPlayer module");
	if (!m_dfplayer.begin(m_serial, false)) {  				//Use HardwareSerial to communicate with DFPlayer.
	    Serial.println("Unable to begin:");
	    Serial.println("Check SD card");
		while(true){
			delay(0);
		}
  	}
  	m_dfplayer.setTimeOut(500); 							// Set serial communictaion timeout to 500ms
  	m_dfplayer.EQ(DFPLAYER_EQ_NORMAL); 						// Set EQ to normal
  	m_dfplayer.outputDevice(DFPLAYER_DEVICE_SD); 			// Set device we use SD as default
  	m_dfplayer.volume(10); 									// Set volume to 15 by default
  	Serial.println("DFPlayer module correctly initialized");

	/* Create volume characteristic */
	m_service = pServer->createService(DFPLAYER_SERVICE);
	m_characteristic_vol = m_service->createCharacteristic(UUID_VOLUME, 
						                                  BLECharacteristic::PROPERTY_READ | 
						                                  BLECharacteristic::PROPERTY_WRITE);
	m_characteristic_vol->setCallbacks(new VolumeCallback(&m_dfplayer));

	/* Create play characteristic */
	m_play = m_service->createCharacteristic(UUID_PLAY, 
			                                  BLECharacteristic::PROPERTY_READ | 
			                                  BLECharacteristic::PROPERTY_WRITE);
	m_play->setCallbacks(new PlayCallback(&m_dfplayer));

	/* Enable this service */ 
	m_service->start();
}
