#include "../header/led_controller.h"
#include "../header/led_patterns.h"


LedController::LedController() : m_led_strip(NB_LED, LED_PIN, NEO_GRB + NEO_KHZ800), m_ble_event_negative(&m_led_strip, m_led_strip.Color(150, 0, 0)), 	m_ble_event_positive(&m_led_strip, m_led_strip.Color(0, 150, 0))  {
	m_led_strip.begin();				// initialize NeoPixel strip object
	m_led_strip.show();					// Turn OFF all pixels
	m_led_strip.setBrightness(100); 	// Set default brightness (max = 255)
	initialize_patterns();

	// Run turn on led pattern
	Serial.println("Led controller correctly initialized !");
}

void LedController::initialize_patterns() {
	// Initialize led patterns
	m_patterns.push_back(new whiteOverRainbow(&m_led_strip));
	m_patterns.push_back(new rainbow(&m_led_strip));
	m_patterns.push_back(new theaterChaseRainbow(&m_led_strip));
	m_patterns.push_back(new rainbowFade2White(&m_led_strip));
}

void LedController::run_positive_pattern() {
	m_ble_event_positive.run();
}

void LedController::run_negative_pattern() {
	m_ble_event_negative.run();
}

void LedController::run_patterns() {
    for (auto pattern : m_patterns) 
    	pattern->run();
}

void LedController::turn_off() {
	Serial.print("Truning off leds ...");
	m_led_strip.clear();
	m_led_strip.show();
}
