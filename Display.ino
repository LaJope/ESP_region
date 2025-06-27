#include "defines.h"

#ifdef PRODUCER

void Display::setup() {
  Wire.begin();
  Wire.setClock(100000);
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
  }

  display.display();
  delay(2000);

  display.clearDisplay();
}

void Display::draw(int percentage, double value) {
  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.cp437(true);

  display.print(percentage);
  display.println('%');
  display.print(value);
  display.println(" GW");

  display.display();
}

#endif
