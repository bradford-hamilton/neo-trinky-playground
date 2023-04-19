#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "Adafruit_FreeTouch.h"
#include "Keyboard.h"

Adafruit_NeoPixel strip {
  NUM_NEOPIXEL,
  PIN_NEOPIXEL,
  NEO_GRB+NEO_KHZ800
};

Adafruit_FreeTouch touch_pad1 {
  1,
  OVERSAMPLE_4,
  RESISTOR_50K,
  FREQ_MODE_NONE
};

Adafruit_FreeTouch touch_pad2 {
  2,
  OVERSAMPLE_4,
  RESISTOR_50K,
  FREQ_MODE_NONE
};

bool previous_touch_state {false};
uint32_t pixel_blue {0x0000FF};
uint32_t pixel_off {0x0};

// Forward declaration
void setAllPixelsToColor(uint32_t color);

void setup()
{
  Serial.begin(9600);

  strip.begin();
  strip.setBrightness(20);
  strip.show(); // Nothing set, so all lights off

  touch_pad1.begin();
  touch_pad2.begin();

  Keyboard.begin();
}

void loop()
{
  uint16_t t1 {touch_pad1.measure()};
  uint16_t t2 {touch_pad2.measure()};

  bool touch_state {false};

  if (t1 > 500 || t2 > 500) {
    touch_state = true;
    setAllPixelsToColor(pixel_blue);
  } else {
    touch_state = false;
    setAllPixelsToColor(pixel_off);
  }

  strip.show();

  if (touch_state && !previous_touch_state) {
    Keyboard.print("secrets from the stick");
  }
  previous_touch_state = touch_state;
}

void setAllPixelsToColor(uint32_t color)
{
  for (uint8_t i {0}; i < 4; i++) {
    strip.setPixelColor(i, color);
  }
}
