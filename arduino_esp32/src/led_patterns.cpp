#include "../header/led_patterns.h"

LedPatternVirtual::LedPatternVirtual(Adafruit_NeoPixel* p_led_strip) {
	m_led_strip = *p_led_strip;
}

whiteOverRainbow::whiteOverRainbow(Adafruit_NeoPixel* p_led_strip) : LedPatternVirtual(p_led_strip),  m_white_speed(75), m_white_length(5) {}

void whiteOverRainbow::run(const int p_loops) {
	int      head;
	int      tail          = 0;
	int      loopNum       = 0;
	uint32_t lastTime      = millis();
	uint32_t firstPixelHue = 0;

	if(m_white_length >= m_led_strip.numPixels()) m_white_length = m_led_strip.numPixels() - 1;

	head = m_white_length - 1;

	while(true) {
		for(int i=0; i< m_led_strip.numPixels(); i++) {  											// For each pixel in strip...
			if(((i >= tail) && (i <= head)) || ((tail > head) && ((i >= tail) || (i <= head)))) {  	// If between head & tail...
				m_led_strip.setPixelColor(i, m_led_strip.Color(0, 0, 0, 255)); 						// Set white
			} else {                                             									// else set rainbow
				int pixelHue = firstPixelHue + (i * 65536L / m_led_strip.numPixels());
				m_led_strip.setPixelColor(i, m_led_strip.gamma32(m_led_strip.ColorHSV(pixelHue)));
			}
		}

		m_led_strip.show(); // Update strip with new contents
		// There's no delay here, it just runs full-tilt until the timer and
		// counter combination below runs out.

		firstPixelHue += 40; 							// Advance just a little along the color wheel

		if((millis() - lastTime) > m_white_speed) { 	// Time to update head/tail?
		  if(++head >= m_led_strip.numPixels()) {      	// Advance head, wrap around
			head = 0;
			if(++loopNum >= p_loops) return;
		  }
		  if(++tail >= m_led_strip.numPixels()) tail = 0;	// Advance tail, wrap around
		  lastTime = millis();                   			// Save time of last movement
		}
	}
}

eventPattern::eventPattern(Adafruit_NeoPixel* p_led_strip, uint32_t color) : LedPatternVirtual(p_led_strip), m_color(color) {}

void eventPattern::run(const int p_loops) {
	for (int j = 0 ; j < 4 ; j++ ) {
		m_led_strip.fill(m_color, 0, m_led_strip.numPixels());
		m_led_strip.show();
		delay(100);
		m_led_strip.clear();
		m_led_strip.show();
		delay(100);
	}
}

rainbow::rainbow(Adafruit_NeoPixel* p_led_strip) : LedPatternVirtual(p_led_strip) {}

void rainbow::run(const int p_loops) {
	int      loopNum       = 0;

	while (true) {
		for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
			for(int i = 0 ; i < m_led_strip.numPixels() ; i++) { // For each pixel in strip...
				int pixelHue = firstPixelHue + (i * 65536L / m_led_strip.numPixels());
				m_led_strip.setPixelColor(i, m_led_strip.gamma32(m_led_strip.ColorHSV(pixelHue)));
			}
			m_led_strip.show(); // Update strip with new contents
			delay(500);  // Pause for a moment
		}
		if(++loopNum >= p_loops) return;
	}
}

theaterChaseRainbow::theaterChaseRainbow(Adafruit_NeoPixel* p_led_strip) : LedPatternVirtual(p_led_strip) {}

void theaterChaseRainbow::run(const int p_loops) {
	int      loopNum       = 0;
	int firstPixelHue = 0;     // First pixel starts at red (hue 0)
	while (true) {
		for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
			m_led_strip.clear();         //   Set all pixels in RAM to 0 (off)
			// 'c' counts up from 'b' to end of strip in increments of 3...
			for(int c=b; c<m_led_strip.numPixels(); c += 3) {
				int      hue   = firstPixelHue + c * 65536L / m_led_strip.numPixels();
				uint32_t color = m_led_strip.gamma32(m_led_strip.ColorHSV(hue)); // hue -> RGB
				m_led_strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
			}
			m_led_strip.show();       		// Update strip with new contents
			delay(500);                 	// Pause for a moment
			firstPixelHue += 65536 / 90; 	// One cycle of color wheel over 90 frames
		}

		if(++loopNum >= p_loops) return;
	}
}

rainbowFade2White::rainbowFade2White(Adafruit_NeoPixel* p_led_strip) : LedPatternVirtual(p_led_strip) {}

void rainbowFade2White::run(const int p_loops) {
  int fadeVal=0, fadeMax=100;

  // Hue of first pixel runs 'rainbowLoops' complete loops through the color
  // wheel. Color wheel has a range of 65536 but it's OK if we roll over, so
  // just count from 0 to rainbowLoops*65536, using steps of 256 so we
  // advance around the wheel at a decent clip.
  for(uint32_t firstPixelHue = 0; firstPixelHue < p_loops*65536;
    firstPixelHue += 256) {

    for(int i=0; i<m_led_strip.numPixels(); i++) { // For each pixel in strip...

      // Offset pixel hue by an amount to make one full revolution of the
      // color wheel (range of 65536) along the length of the strip
      // (strip.numPixels() steps):
      uint32_t pixelHue = firstPixelHue + (i * 65536L / m_led_strip.numPixels());

      // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
      // optionally add saturation and value (brightness) (each 0 to 255).
      // Here we're using just the three-argument variant, though the
      // second value (saturation) is a constant 255.
      m_led_strip.setPixelColor(i, m_led_strip.gamma32(m_led_strip.ColorHSV(pixelHue, 255,
        255 * fadeVal / fadeMax)));
    }

    m_led_strip.show();
    delay(3);

    if(firstPixelHue < 65536) {                              // First loop,
      if(fadeVal < fadeMax) fadeVal++;                       // fade in
    } else if(firstPixelHue >= ((p_loops-1) * 65536)) { // Last loop,
      if(fadeVal > 0) fadeVal--;                             // fade out
    } else {
      fadeVal = fadeMax; // Interim loop, make sure fade is at max
    }
  }

  for(int k=0; k<p_loops; k++) {
    for(int j=0; j<256; j++) { // Ramp up 0 to 255
      // Fill entire strip with white at gamma-corrected brightness level 'j':
      m_led_strip.fill(m_led_strip.Color(0, 0, 0, m_led_strip.gamma8(j)));
      m_led_strip.show();
    }
    delay(1000); // Pause 1 second
    for(int j=255; j>=0; j--) { // Ramp down 255 to 0
      m_led_strip.fill(m_led_strip.Color(0, 0, 0, m_led_strip.gamma8(j)));
      m_led_strip.show();
    }
  }

  delay(500); // Pause 1/2 second
}
