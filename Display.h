#pragma once

#include "defines.h"

#ifdef PRODUCER

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <Wire.h>

struct Display {
  Adafruit_SSD1306 display;

  Display() : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET) {}

  void setup();

  void draw(int percentage, double value);
};

#endif
