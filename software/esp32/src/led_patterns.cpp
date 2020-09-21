#include "../header/led_patterns.h"
#include <Arduino.h>

LedPatternVirtual::~LedPatternVirtual() {
	stop();
}

void LedPatternVirtual::stop() {
	m_running = false;
	delay(500);
	m_led_strip.ClearTo(m_black);
	m_led_strip.Show();
}

template <typename T>
void LedPatternVirtual::handle_task_curr_pattern(void* _pattern) {
	static_cast<T*>(_pattern)->_run();
	vTaskDelete(NULL); // Make sure to delete task before ending
}

void eventPattern::run() {
	m_running = true;
	xTaskCreate(handle_task_curr_pattern<eventPattern>, "curr_pattern", 1024, this, 5, NULL);
}

void eventPattern::_run() {
	for (int j = 0 ; j < 3 ; j++ ) {
		m_led_strip.ClearTo(m_color);
		m_led_strip.Show();
		delay(150);
		m_led_strip.ClearTo(m_black);
		m_led_strip.Show();
		delay(150);
	}
}

void fadeInFadeOut::run() {
	m_running = true;
	xTaskCreate(handle_task_curr_pattern<fadeInFadeOut>, "curr_pattern", 1024, this, 5, NULL);
}

void fadeInFadeOut::_run() {
	while (m_running) {
		if (m_animations.IsAnimating()) {
			// the normal loop just needs these two to run the active animations
			m_animations.UpdateAnimations();
			m_led_strip.Show();
		} else {
			// no animation runnning, start some 
			FadeInFadeOutRinseRepeat(0.25); // 0.0 = black, 0.25 is normal, 0.5 is bright
		}
	}
}

void fadeInFadeOut::FadeInFadeOutRinseRepeat(float luminance) {
	AnimUpdateCallback animUpdate = [=](const AnimationParam& param) {
		// this gets called for each animation on every time step
		// progress will start at 0.0 and end at 1.0
		// we use the blend function on the RgbColor to mix
		// color based on the progress given to us in the animation
		RgbColor updatedColor = RgbColor::LinearBlend(
			m_animationState[param.index].StartingColor,
			m_animationState[param.index].EndingColor,
			param.progress);

		// apply the color to the strip
		for (uint16_t pixel = 0; pixel < m_led_strip.PixelCount(); pixel++)
			m_led_strip.SetPixelColor(pixel, updatedColor);
	};

	if (m_fadeToColor) {
		// Fade upto a random color
		// we use HslColor object as it allows us to easily pick a hue
		// with the same saturation and luminance so the colors picked
		// will have similiar overall brightness
		RgbColor target = HslColor(random(360) / 360.0f, 1.0f, luminance);
		uint16_t time = random(800, 2000);

		m_animationState[0].StartingColor = m_led_strip.GetPixelColor(0);
		m_animationState[0].EndingColor = target;

		m_animations.StartAnimation(0, time, animUpdate);
	} else {
		// fade to black
		uint16_t time = random(600, 700);

		m_animationState[0].StartingColor = m_led_strip.GetPixelColor(0);
		m_animationState[0].EndingColor = RgbColor(0);

		m_animations.StartAnimation(0, time, animUpdate);
	}

	// toggle to the next effect state
	m_fadeToColor = !m_fadeToColor;
}

void funRandomChange::run() {
	m_running = true;
	xTaskCreate(handle_task_curr_pattern<funRandomChange>, "curr_pattern", 1024, this, 5, NULL);
}

void funRandomChange::_run() {
	AnimUpdateCallback animUpdate = [=](const AnimationParam& param) {
	    // this gets called for each animation on every time step
	    // progress will start at 0.0 and end at 1.0
	    // we use the blend function on the RgbColor to mix
	    // color based on the progress given to us in the animation
	    RgbColor updatedColor = RgbColor::LinearBlend(
	        m_animationState[param.index].StartingColor,
	        m_animationState[param.index].EndingColor,
	        param.progress);
	    // apply the color to the strip
	    m_led_strip.SetPixelColor(param.index, updatedColor);
	};

	while(m_running) {
	    if (m_animations.IsAnimating())
	    {
	        // the normal loop just needs these two to run the active animations
	        m_animations.UpdateAnimations();
	        m_led_strip.Show();
	    }
	    else
	    {
		    // pick random count of pixels to animate
		    uint16_t count = random(m_led_strip.PixelCount());
		    while (count > 0)
		    {
		        // pick a random pixel
		        uint16_t pixel = random(m_led_strip.PixelCount());

		        // pick random time and random color
		        // we use HslColor object as it allows us to easily pick a color
		        // with the same saturation and luminance 
		        uint16_t time = random(100, 400);
		        m_animationState[pixel].StartingColor = m_led_strip.GetPixelColor(pixel);
		        m_animationState[pixel].EndingColor = HslColor(random(360) / 360.0f, 1.0f, 0.25);

		        m_animations.StartAnimation(pixel, time, animUpdate);

		        count--;
		    }
		}
	}
}