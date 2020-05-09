#pragma once

#include <BLEServer.h>
#include <Arduino.h>
#include <vector>
#include <NeoPixelBus.h>
#include <BLEServer.h>
#include "led_patterns.h"

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
	LedController(QueueHandle_t *p_queue);
private:
	eventPattern m_ble_event_positive;
	eventPattern m_ble_event_negative;
	fadeInFadeOut m_fadein_fadeout;
	static void task_wrapper(void*);
	void task_event();
	template <typename T>
	static void handle_task_curr_pattern(void*);
};
