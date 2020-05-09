#include "../header/led_controller.h"


LedController::LedController(QueueHandle_t *p_queue) : 
m_led_strip(NB_LED, LED_PIN), 
m_ble_event_positive(m_led_strip, RgbColor(0, 128, 0)), 
m_ble_event_negative(m_led_strip, RgbColor(128, 0, 0)), 
m_fadein_fadeout(m_led_strip)  {
	m_led_strip.Begin();							// initialize NeoPixel strip object
	m_led_strip.Show();								// Turn OFF all pixels

	// Create event queue & associated task
	m_queue = *p_queue;
	xTaskCreate(
		this->task_wrapper,     /* Task function. */
		"task_event",        	/* String with name of task. */
		2048,            		/* Stack size in bytes. */
		this,		            /* Parameter passed as input of the task */
		32, /* Priority of the task. */
		NULL);            		/* Task handle. */
}

void LedController::task_event() {
	bool run = true;
	e_patterns pattern;
	TaskHandle_t task_current_pattern;

	Serial.println("Creating ledcontroller task");
	while(run) {
		xQueueReceive(m_queue, &pattern, portMAX_DELAY);
		Serial.print("We receive a pattern command: ");
		Serial.println(pattern);
		switch(pattern) {
			case POSITIVE: 
				m_ble_event_positive.run();
				break;
			case NEGATIVE:
				m_ble_event_negative.run();
				break;
			case FADEINFADEOUT:
				xTaskCreate(handle_task_curr_pattern<fadeInFadeOut>, "curr_pattern", 1024, &m_fadein_fadeout, 5, &task_current_pattern);
				break;
			default:
				Serial.print("Invalid pattern: ");
				Serial.println(pattern);
		}
	}
}

void LedController::task_wrapper(void *_this) {
	// Trick to create task using a class method
	static_cast<LedController*>(_this)->task_event();
	vTaskDelete(NULL); // Make sure to delete task before ending
}

template <typename T>
void LedController::handle_task_curr_pattern(void* _pattern) {
	static_cast<T*>(_pattern)->run();
	vTaskDelete(NULL); // Make sure to delete task before ending
}
