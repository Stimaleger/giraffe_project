#include <string>
#include "../header/dfplayer_mp3.h"

VolumeCallback::VolumeCallback(DFRobotDFPlayerMini* myDFPlayer) {
	m_dfplayer = *myDFPlayer;
}

void VolumeCallback::onWrite(BLECharacteristic* pCharacteristic) {
	String value = pCharacteristic->getValue().c_str();

	// Change value only if it matchs with max value
	if (value.toInt() <= max_value) {
		m_dfplayer.volume(value.toInt());
	}
}

void VolumeCallback::onRead(BLECharacteristic* pCharacteristic) {}

DFPlayer::DFPlayer(BLEServer* pServer) : m_serial(1) {
	/* Create DFPlayer */
	m_serial.begin(9600, SERIAL_8N1, 16, 17);  				// speed, type, RX, TX
	Serial.println("Initializing DFPlayer module");
	if (!m_dfplayer.begin(m_serial, false)) {  				// Enable UART
	    Serial.println("Unable to begin:");
	    Serial.println("Check SD card");
		delay(5000);
		ESP.restart();
  	}
  	m_dfplayer.setTimeOut(500); 								// Set serial communictaion timeout to 500ms
  	m_dfplayer.EQ(DFPLAYER_EQ_NORMAL); 							// Set EQ to normal
  	m_dfplayer.outputDevice(DFPLAYER_DEVICE_SD); 				// Set device we use SD as default
  	m_dfplayer.volume(15); 										// Set volume to default value
  	Serial.println("DFPlayer module correctly initialized");

	/* Create volume characteristic */
	m_service = pServer->createService(DFPLAYER_SERVICE);
	m_characteristic_vol = m_service->createCharacteristic(UUID_VOLUME, 
						                                  BLECharacteristic::PROPERTY_READ | 
						                                  BLECharacteristic::PROPERTY_WRITE);
	m_characteristic_vol->setCallbacks(new VolumeCallback(&m_dfplayer));

	/* Enable this service */ 
	m_service->start();
	Serial.println("DFPlayer BLE service enabled");
}
