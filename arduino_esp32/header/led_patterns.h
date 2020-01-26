#pragma once

#include <Adafruit_NeoPixel.h>
#define DEFAULT_LOOP_NB 10

class LedPatternVirtual {
public:
	LedPatternVirtual(Adafruit_NeoPixel* p_led_strip);
	void run(const int p_loops = DEFAULT_LOOP_NB);

protected:
	Adafruit_NeoPixel m_led_strip;
	bool m_is_running;
};

class whiteOverRainbow : public LedPatternVirtual {
public:
	whiteOverRainbow(Adafruit_NeoPixel* p_led_strip);
	void run(const int p_loops = DEFAULT_LOOP_NB);

private:
	int m_white_speed;
	int m_white_length;
};

class rainbow : public LedPatternVirtual {
public:
	rainbow(Adafruit_NeoPixel* p_led_strip);
	void run(const int p_loops = DEFAULT_LOOP_NB);
};

class theaterChaseRainbow : public LedPatternVirtual {
public:
	theaterChaseRainbow(Adafruit_NeoPixel* p_led_strip);
	void run(const int p_loops = DEFAULT_LOOP_NB);
};

class rainbowFade2White : public LedPatternVirtual {
public:
	rainbowFade2White(Adafruit_NeoPixel* p_led_strip);
	void run(const int p_loops = DEFAULT_LOOP_NB);
};

class eventPattern : public LedPatternVirtual {
public:
	eventPattern(Adafruit_NeoPixel* p_led_strip, uint32_t color);
	void run(const int p_loops = DEFAULT_LOOP_NB);
private:
	uint32_t m_color;
};
