#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "Adafruit_FreeTouch.h"
#include "Keyboard.h"

Adafruit_NeoPixel strip = Adafruit_NeoPixel{
  NUM_NEOPIXEL,
  PIN_NEOPIXEL,
  NEO_GRB+NEO_KHZ800
};

Adafruit_FreeTouch touch_pad1 = Adafruit_FreeTouch{
  1,
  OVERSAMPLE_4,
  RESISTOR_50K,
  FREQ_MODE_NONE
};

Adafruit_FreeTouch touch_pad2 = Adafruit_FreeTouch{
  2,
  OVERSAMPLE_4,
  RESISTOR_50K,
  FREQ_MODE_NONE
};

bool previous_touch1_state {false};
bool previous_touch2_state {false};
int touch_counter {0};

void setup()
{
  Serial.begin(9600);

  strip.begin();
  strip.setBrightness(20);
  strip.show(); // Nothing set, so all lights off

  if (!touch_pad1.begin()) {
    Serial.println("Failed to begin touch1");
  }
  if (!touch_pad2.begin()) {
    Serial.println("Failed to begin touch2");
  }

  // void begin(const uint8_t *layout = KeyboardLayout_en_US);
  Keyboard.begin();
}

void loop()
{
  uint16_t t1 {touch_pad1.measure()};
  uint16_t t2 {touch_pad2.measure()};

  bool touch1_state = false;
  bool touch2_state = false;

  if (t1 > 500) {
    touch1_state = true;
    Serial.println("touchpad_1 touched");
    strip.setPixelColor(2, 0xFF0000);
    strip.setPixelColor(3, 0xFF0000);
    Keyboard.print(1);
  } else {
    touch1_state = false;
    strip.setPixelColor(2, 0x0);
    strip.setPixelColor(3, 0x0);
  }

if (t2 > 500) {
    touch2_state = true;
    Serial.println("touchpad_2 touched");
    strip.setPixelColor(0, 0xFF0000);
    strip.setPixelColor(1, 0xFF0000);
    Keyboard.print(2);
  } else {
    touch2_state = false;
    strip.setPixelColor(0, 0x0);
    strip.setPixelColor(1, 0x0);
  }

  strip.show();

  int touch1_counter {0};
  int touch2_counter {0};

  // If we're touching 1 and weren't before
  if (touch1_state && !previous_touch1_state) {
    touch1_counter++;
    Serial.print("Touched #1");
    Serial.print(touch1_counter);
    Serial.println(" times.");
  }

  // Save current touch state for comparison
  previous_touch1_state = touch1_state;

  // If we're touching 2 and weren't before
  if (touch2_state && !previous_touch2_state) {
    touch2_counter++;
    Serial.print("Touched #1");
    Serial.print(touch2_counter);
    Serial.println(" times.");
  }

  // Save current touch state for comparison
  previous_touch2_state = touch2_state;
}
