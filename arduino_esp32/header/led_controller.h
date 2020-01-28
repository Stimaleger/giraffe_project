#pragma once

#include <BLEServer.h>
#include <Arduino.h>
#include <vector>
#include <Adafruit_NeoPixel.h>
#include <BLEServer.h>
#include "led_patterns.h"

#define LED_PIN		13
#define NB_LED		9


class LedController {
	Adafruit_NeoPixel m_led_strip;

public:
	LedController();
	void turn_off();
	void initialize_patterns();
	void run_positive_pattern();
	void run_negative_pattern();
	void run_patterns();
private:
	eventPattern m_ble_event_positive;
	eventPattern m_ble_event_negative;
	std::vector<LedPatternVirtual*> m_patterns;
};
