#pragma once

#include <NeoPixelBus.h>
#include <NeoPixelAnimator.h>
typedef  NeoPixelBus<NeoGrbFeature, NeoEsp32Rmt0800KbpsMethod> NeoPixelBusType;

class LedPatternVirtual {
public:
	LedPatternVirtual(NeoPixelBusType& p_led_strip) : m_black(0), m_led_strip(p_led_strip), m_running(false) {}
	~LedPatternVirtual();
	virtual void run() = 0;

	void stop();
	virtual void _run() = 0;

	template <typename T>
	static void handle_task_curr_pattern(void*);

protected:
	NeoPixelBusType& m_led_strip;
	RgbColor m_black;
	bool m_running;
};

class eventPattern : public LedPatternVirtual {
public:
	eventPattern(NeoPixelBusType& p_led_strip, RgbColor color) : LedPatternVirtual(p_led_strip), m_color(color) {}
	void _run();
	void run();
private:
	RgbColor m_color;
};

class fadeInFadeOut : public LedPatternVirtual {
public:
	fadeInFadeOut(NeoPixelBusType& p_led_strip) : LedPatternVirtual(p_led_strip), m_fadeToColor(true), m_animations(1) {}
	void _run();
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

class funRandomChange : public LedPatternVirtual {
public:
	funRandomChange(NeoPixelBusType& p_led_strip) : LedPatternVirtual(p_led_strip), m_animations(p_led_strip.PixelCount()) {}
	void _run();
	void run();
private:
	NeoPixelAnimator m_animations; // NeoPixel animation management object
	struct MyAnimationState
	{
	    RgbColor StartingColor;
	    RgbColor EndingColor;
	};
	// one entry per pixel to match the animation timing manager
	MyAnimationState m_animationState[16];
};