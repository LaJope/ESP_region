#include "defines.h"

#ifdef PRODUCER
#ifdef POTENTIOMETER

#include "Potentiometer.h"

void Potentiometer::setup_pins() {
  pinMode(POTENTIOMETER_PIN, INPUT);
}

void Potentiometer::check_and_send() {
  int read = analogRead(POTENTIOMETER_PIN);
  int new_percentage = map(read, 0, 4095, 0, MAX_PERCENTAGE / CHANGE_RATE) * CHANGE_RATE;
  if (std::abs(percentage - new_percentage) >= CHANGE_RATE) {
    if (millis() - last_update > delay_between_updates) {
      percentage = new_percentage;
      last_update = millis();
      send_reading(percentage);
    }
  }
}

#endif
#endif
