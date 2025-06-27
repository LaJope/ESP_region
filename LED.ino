#include "defines.h"

#include "LED.h"

void LED::setup_pins() {
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
}

#ifdef CONSUMER
void LED::rotate_color(uint8_t time, bool isOn) {
  if (time < 0 || time > 47)
    return;

  color curr_color = isOn ? day_working[time] : day_broken[time];
  // dim_light(curr_color, 100);

  output_color(curr_color);
}
#endif
#ifdef PRODUCER
void LED::rotate_color(int percentage) {
  uint8_t col = map(percentage, 0, MAX_PERCENTAGE, 0, 255);
  output_color({col, col, col});
}
#endif

void LED::output_color(color col) {
  analogWrite(LED_RED, col.red);
  analogWrite(LED_GREEN, col.green);
  analogWrite(LED_BLUE, col.blue);
}

void LED::dim_light(color &col, int factor) {
  col.red = std::max(col.red - factor, 0);
  col.green = std::max(col.green - factor, 0);
  col.blue = std::max(col.blue - factor, 0);
}
