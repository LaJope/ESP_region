#include "defines.h"

#ifdef CONSUMER
#include "LED.h"

void LED::setup_pins() {
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
}

void LED::change_color(uint8_t time, bool isOn) {
  if (time < 0 || time > 47)
    return;

  color curr_color = (isOn ? working[time] : broken[time]);
  uint8_t red = (curr_color.red - 100 >= 0 ? curr_color.red - 100 : 0);
  uint8_t green = (curr_color.green - 100 >= 0 ? curr_color.green - 100 : 0);
  uint8_t blue = (curr_color.blue - 100 >= 0 ? curr_color.blue - 100 : 0);
  
  analogWrite(LED_RED, red);
  analogWrite(LED_GREEN, green);
  analogWrite(LED_BLUE, blue);
}
#endif
