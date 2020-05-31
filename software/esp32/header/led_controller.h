#pragma once
#include <Arduino.h>
#include <vector>
#include <NeoPixelBus.h>
#include "led_patterns.h"
#include "../header/ble.h"

#define LED_PIN		13
#define NB_LED		9
#define DEFAULT_BRIGHTNESS 128

typedef enum patterns {
	POSITIVE=0,
	NEGATIVE,
	WHITEOVERRAINBOW,
	FADEINFADEOUT,
	RAINBOW,
	THEATERCHASERAINBOW,
	RAINBOWFADE2WHITE
} e_patterns;

class LedController {
	NeoPixelBusType m_led_strip;
	QueueHandle_t m_queue;
public:
	LedController(QueueHandle_t *p_queue, BleManager* pServer);
	static void pattern_changed(BLECharacteristic* pCharacteristic, void* param);
private:
	void set_curr_pattern(e_patterns p_pattern);
	LedPatternVirtual* m_curr_pattern;
	static void task_wrapper(void*);
	void task_event();
};
