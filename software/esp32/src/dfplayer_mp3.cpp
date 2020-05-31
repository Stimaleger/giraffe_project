#include <string>
#include "../header/dfplayer_mp3.h"
#include "../share/ble_interface.h"

DFPlayer::~DFPlayer() {}

DFPlayer::DFPlayer(BleManager* pServer) : m_serial(1) {
	/* Create DFPlayer */
	m_serial.begin(9600, SERIAL_8N1, 16, 17);  					// speed, type, RX, TX
	Serial.println("Initializing DFPlayer module");
	if (!m_dfplayer.begin(m_serial, false)) {  					// Enable UART
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

	/* Create BLE characteristic */
	pServer->populate_ble(BLE_MP3_VOLUME, volume_changed, volume_changed, this);
	pServer->populate_ble(BLE_MP3_PLAY, play, play, this);
	
	/* Enable this service */ 
	Serial.println("DFPlayer succesfully initialized");
}

void DFPlayer::volume_changed(BLECharacteristic* pCharacteristic, void* param) {
	String value = pCharacteristic->getValue().c_str();

	// Change value only if it matchs with max value
	if (value.toInt() <= (int)MAX_VOLUME)
		static_cast<DFPlayer *>(param)->m_dfplayer.volume(value.toInt());
}

void DFPlayer::play(BLECharacteristic* pCharacteristic, void* param) {
	String value = pCharacteristic->getValue().c_str();

	static_cast<DFPlayer *>(param)->m_dfplayer.playMp3Folder(value.toInt());
}
