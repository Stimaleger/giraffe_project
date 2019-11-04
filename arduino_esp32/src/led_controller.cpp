#include "../header/led_controller.h"

LedController::LedController(BLEServer* pServer) : m_led_strip(NB_LED, LED_PIN, NEO_GRBW + NEO_KHZ800) {
	// initialize NeoPixel strip object
	m_led_strip.begin();
	
	// Turn OFF all pixels
	m_led_strip.show();
	
	// Set default brightness to about 1/5 (max = 255)
	m_led_strip.setBrightness(50); 
}
