#pragma once

#include <Adafruit_NeoPixel.h>
#include <BLEServer.h>

#define LED_PIN		13
#define NB_LED		10

class LedController {
	Adafruit_NeoPixel m_led_strip;
public:
	LedController(BLEServer* pServer);
	~LedController();
};
