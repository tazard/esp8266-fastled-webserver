uint8_t coordsX[NUM_LEDS] = { 151, 188, 199, 199, 171, 147, 131, 119, 124, 179, 200, 217, 237, 249, 242, 234, 255, 148, 175, 177, 150, 143, 171, 153, 155, 106, 110, 102, 75, 86, 106, 108, 88, 90, 84, 78, 107, 98, 121, 128, 80, 69, 134, 159, 192, 202, 195, 218, 61, 32, 18, 26, 39, 20, 3, 0, 48, 52, 61, 54, 33, 20, 7, 8 };
uint8_t coordsY[NUM_LEDS] = { 190, 204, 225, 252, 255, 236, 216, 191, 166, 147, 154, 170, 173, 156, 131, 107, 106, 148, 121, 86, 81, 63, 56, 36, 17, 145, 120, 96, 55, 23, 18, 0, 2, 112, 77, 31, 35, 49, 51, 30, 124, 103, 101, 98, 80, 58, 40, 69, 134, 124, 107, 81, 56, 43, 50, 70, 156, 180, 202, 219, 213, 195, 197, 215 };
uint8_t angles[NUM_LEDS] = { 0, 249, 241, 232, 223, 200, 208, 217, 226, 235, 212, 203, 194, 185, 176, 162, 171, 180, 188, 197, 174, 165, 156, 147, 139, 124, 133, 142, 151, 136, 128, 119, 110, 101, 78, 86, 95, 104, 113, 99, 90, 81, 72, 63, 40, 49, 58, 67, 75, 52, 43, 34, 25, 17, 2, 11, 20, 29, 38, 14, 6, 255, 246, 237 };
uint8_t body[NUM_LEDS] = { 0, 16, 32, 48, 64, 80, 96, 112, 128, 143, 159, 175, 191, 207, 223, 239, 255, 143, 159, 175, 191, 207, 223, 239, 255, 143, 159, 175, 191, 207, 223, 239, 255, 143, 159, 175, 191, 207, 223, 239, 143, 159, 175, 191, 207, 223, 239, 255, 143, 159, 175, 191, 207, 223, 239, 255, 143, 159, 175, 191, 207, 223, 239, 255 };

// uint8_t head[9] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
// uint8_t tentacle0[8] = { 9, 10, 11, 12, 13, 14, 15, 16 };
// uint8_t tentacle1[8] = { 17, 18, 19, 20, 21, 22, 23, 24 };
// uint8_t tentacle2[8] = { 25, 26, 27, 28, 29, 30, 31, 32 };
// uint8_t tentacle3[8] = { 33, 34, 35, 36, 37, 38, 39 };
// uint8_t tentacle4[8] = { 40, 41, 42, 43, 44, 45, 46, 47 };
// uint8_t tentacle5[8] = { 48, 49, 50, 51, 52, 53, 54, 55 };
// uint8_t tentacle6[8] = { 56, 57, 58, 59, 60, 61, 62, 63 };

void setPixelAR(uint8_t angle, uint8_t dAngle, uint8_t radius, uint8_t dRadius, CRGB color)
{
  uint16_t amax = qadd8(angle, dAngle);
  uint8_t amin = qsub8(angle, dAngle);

  uint16_t rmax = qadd8(radius, dRadius);
  uint16_t rmin = qsub8(radius, dRadius);

  for (uint16_t i = 0; i < NUM_LEDS; i++) {
    uint8_t o = i;

    uint8_t ao = angles[o];

    if (ao <= amax && ao >= amin) {
      uint8_t ro = body[o];

      if (ro <= rmax && ro >= rmin) {
        leds[i] = color;
      }
    }
  }
}

void andPixelAR(uint8_t angle, uint8_t dAngle, uint8_t startRadius, uint8_t endRadius, CRGB color)
{
  uint16_t amax = qadd8(angle, dAngle);
  uint8_t amin = qsub8(angle, dAngle);

  for (uint16_t i = 0; i < NUM_LEDS; i++) {
    uint8_t o = i;

    uint8_t ao = angles[o];

    if (ao <= amax && ao >= amin) {
      uint8_t ro = body[o];

      if (ro <= endRadius && ro >= startRadius) {
        leds[i] += color;
      }
    }
  }
}

void antialiasPixelAR(uint8_t angle, uint8_t dAngle, uint8_t startRadius, uint8_t endRadius, CRGB color)
{
  uint16_t amax = qadd8(angle, dAngle);
  uint8_t amin = qsub8(angle, dAngle);

  for (uint16_t i = 0; i < NUM_LEDS; i++) {
    uint8_t o = i;

    uint8_t ao = angles[o];

    uint8_t adiff = qsub8(max(ao, angle), min(ao, angle));
    uint8_t fade = qmul8(adiff, 32);
    CRGB faded = color;
    faded.fadeToBlackBy(fade);

    if (ao <= amax && ao >= amin) {
      uint8_t ro = body[o];

      if (ro <= endRadius && ro >= startRadius) {
        leds[i] += faded;
      }
    }
  }
}

void bodyPalette() {
  uint8_t hues = 1;

  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    uint8_t x = body[i];

    leds[i] = ColorFromPalette(palettes[currentPaletteIndex], beat8(speed) - (x * hues));
  }
}

void anglePalette() {
  uint8_t hues = 1;

  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    uint8_t x = angles[i];

    leds[i] = ColorFromPalette(palettes[currentPaletteIndex], beat8(speed) - (x * hues));
  }
}

void radiusPalette() {
  uint8_t hues = 1;

  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    uint8_t r = body[i];
    
    leds[i] = ColorFromPalette(palettes[currentPaletteIndex], beat8(speed) - (r * hues));
  }
}

void xPalette() {
  uint8_t hues = 1;

  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    uint8_t x = coordsX[i];

    leds[i] = ColorFromPalette(palettes[currentPaletteIndex], beat8(speed) - (x * hues));
  }
}

void yPalette() {
  uint8_t hues = 1;

  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    uint8_t y = coordsY[i];

    leds[i] = ColorFromPalette(palettes[currentPaletteIndex], beat8(speed) + (y * hues));
  }
}

void xyPalette() {
  uint8_t hues = 1;

  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    uint8_t x = coordsX[i];
    uint8_t y = coordsY[i];

    leds[i] = ColorFromPalette(palettes[currentPaletteIndex], beat8(speed) - ((x + y) * hues));
  }
}

void angleGradientPalette() {
  uint8_t hues = 1;

  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    uint8_t x = angles[i];

    leds[i] = ColorFromPalette(gCurrentPalette, beat8(speed) - (x * hues));
  }
}

void radiusGradientPalette() {
  uint8_t hues = 1;

  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    uint8_t r = body[i];
    
    leds[i] = ColorFromPalette(gCurrentPalette, beat8(speed) - (r * hues));
  }
}

void bodyGradientPalette() {
  uint8_t hues = 1;
  
  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    uint8_t x = body[i];

    leds[i] = ColorFromPalette(gCurrentPalette, beat8(speed) - (x * hues));
  }
}

void xGradientPalette() {
  uint8_t hues = 1;
  
  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    uint8_t x = coordsX[i];

    leds[i] = ColorFromPalette(gCurrentPalette, beat8(speed) - (x * hues));
  }
}

void yGradientPalette() {
  uint8_t hues = 1;
  
  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    uint8_t y = coordsY[i];

    leds[i] = ColorFromPalette(gCurrentPalette, beat8(speed) + (y * hues));
  }
}

void xyGradientPalette() {
  uint8_t hues = 1;
  
  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    uint8_t x = coordsX[i];
    uint8_t y = coordsY[i];

    leds[i] = ColorFromPalette(gCurrentPalette, beat8(speed) - ((x + y) * hues));
  }
}

void drawAnalogClock() {
  float second = timeClient.getSeconds();
  float minute = timeClient.getMinutes() + (second / 60.0);
  float hour = timeClient.getHours() + (minute / 60.0);

  static uint8_t hourAngle = 0;
  static uint8_t minuteAngle = 0;
  static uint8_t secondAngle = 0;

  const uint8_t hourRadius = 64;
  const uint8_t minuteRadius = 96;
  const uint8_t secondRadius = 255;

  const uint8_t handWidth = 64;

  const float degreesPerSecond = 255.0 / 60.0;
  const float degreesPerMinute = 255.0 / 60.0;
  const float degreesPerHour = 255.0 / 12.0;

  EVERY_N_MILLIS(100) {
    hourAngle = 255 - hour * degreesPerHour;
    minuteAngle = 255 - minute * degreesPerMinute;
    secondAngle = 255 - second * degreesPerSecond;
  }

  fadeToBlackBy(leds, NUM_LEDS, clockBackgroundFade);

  antialiasPixelAR(secondAngle, handWidth, 0, secondRadius, CRGB::Blue);
  antialiasPixelAR(minuteAngle, handWidth, 0, minuteRadius, CRGB::Green);
  antialiasPixelAR(hourAngle, handWidth, 0, hourRadius, CRGB::Red);
  leds[0] = CRGB::Red;
}
