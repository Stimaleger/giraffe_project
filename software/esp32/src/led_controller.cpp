#include "../header/led_controller.h"
#include "../share/ble_interface.h"


LedController::LedController(QueueHandle_t *p_queue, BleManager* pServer) : 
	m_led_strip(NB_LED, LED_PIN),
	m_curr_pattern(NULL) 
{
	m_led_strip.Begin();							// initialize NeoPixel strip object
	m_led_strip.Show();								// Turn OFF all pixels

	// Create event queue & associated task
	m_queue = *p_queue;
	xTaskCreate(
		this->task_wrapper,	/* Task function. */
		"task_event",       /* String with name of task. */
		1024,            	/* Stack size in bytes. */
		this,		        /* Parameter passed as input of the task */
		32, 				/* Priority of the task. */
		NULL);            	/* Task handle. */

	pServer->populate_ble(BLE_PATTERN, pattern_changed, pattern_changed, this);
}

void LedController::task_wrapper(void *_this) {
	// Trick to create task using a class method
	static_cast<LedController*>(_this)->task_event();
	vTaskDelete(NULL); // Make sure to delete task before ending
}

void LedController::task_event() {
	e_patterns e_pattern;

	Serial.println("LedController task waiting for new pattern");
	while(true) {
		xQueueReceive(m_queue, &e_pattern, portMAX_DELAY);
		Serial.print("We receive a pattern command: ");
		Serial.println(e_pattern);

		set_curr_pattern(e_pattern);
		if (m_curr_pattern)
			m_curr_pattern->run();
	}
}

void LedController::set_curr_pattern(e_patterns p_pattern) {
	if (m_curr_pattern) {
		Serial.println("Deleting previous pattern");
		m_curr_pattern->stop();
		delete(m_curr_pattern);
	}

	switch(p_pattern) {
		case POSITIVE:
			m_curr_pattern = new eventPattern(m_led_strip, RgbColor(0, 128, 0));
			break;
		case NEGATIVE:
			m_curr_pattern = new eventPattern(m_led_strip, RgbColor(128, 0, 0));
			break;
		case FADEINFADEOUT:
			m_curr_pattern = new fadeInFadeOut(m_led_strip);
			break;
		case FUNRANDOMCHANGE:
			m_curr_pattern = new funRandomChange(m_led_strip);
			break;
		default:
			Serial.print("Invalid pattern: ");
			Serial.println(p_pattern);
	}
}

void LedController::pattern_changed(BLECharacteristic* pCharacteristic, void* param) {
	LedController* _this = static_cast<LedController*>(param);

	String value = pCharacteristic->getValue().c_str();
	int int_value = value.toInt();
	xQueueSend(_this->m_queue, &int_value, portMAX_DELAY);
}
