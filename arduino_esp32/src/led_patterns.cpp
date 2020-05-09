#include "../header/led_patterns.h"
#include <Arduino.h>

void eventPattern::run() {
	for (int j = 0 ; j < 3 ; j++ ) {
		m_led_strip.ClearTo(m_color);
		m_led_strip.Show();
		delay(200);
		m_led_strip.ClearTo(m_black);
		m_led_strip.Show();
		delay(200);
	}
}

void fadeInFadeOut::run() {
	while (true) {
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
