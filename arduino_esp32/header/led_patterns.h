#pragma once

#include <NeoPixelBus.h>
#include <NeoPixelAnimator.h>
typedef  NeoPixelBus<NeoGrbFeature, NeoEsp32I2s1800KbpsMethod> NeoPixelBusType;

class LedPatternVirtual {
public:
	LedPatternVirtual(NeoPixelBusType& p_led_strip) : m_black(0), m_led_strip(p_led_strip) {}
	virtual void run() = 0;

protected:
	NeoPixelBusType& m_led_strip;
	RgbColor m_black;
};
/*
class whiteOverRainbow : public LedPatternVirtual {
public:
	whiteOverRainbow(Adafruit_NeoPixel* p_led_strip);
	void run();
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
};*/

class eventPattern : public LedPatternVirtual {
public:
	eventPattern(NeoPixelBusType& p_led_strip, RgbColor color) : LedPatternVirtual(p_led_strip), m_color(color) {}
	void run();
private:
	RgbColor m_color;
};

class fadeInFadeOut : public LedPatternVirtual {
public:
	fadeInFadeOut(NeoPixelBusType& p_led_strip) : LedPatternVirtual(p_led_strip), m_fadeToColor(true), m_animations(1) {}
	void run();
private:
	NeoPixelAnimator m_animations; // NeoPixel animation management object
	boolean m_fadeToColor;
	void FadeInFadeOutRinseRepeat(float luminance);
	struct MyAnimationState
	{
	    RgbColor StartingColor;
	    RgbColor EndingColor;
	};
	// one entry per pixel to match the animation timing manager
	MyAnimationState m_animationState[1];
};
