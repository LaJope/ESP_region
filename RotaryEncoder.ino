#include "defines.h"

#ifdef PRODUCER
#ifdef ROTARY_ENCODER
#include "RotaryEncoder.h"

void RotaryEncoder::setup_pins() {
  pinMode(ROTARY_ENCODER_CLK, INPUT);
  pinMode(ROTARY_ENCODER_DT, INPUT);
  pinMode(ROTARY_ENCODER_SW, INPUT_PULLUP);
  last_state_CLK = digitalRead(ROTARY_ENCODER_CLK);
}

bool RotaryEncoder::check_rotation() {
  current_state_CLK = digitalRead(ROTARY_ENCODER_CLK);
  if (current_state_CLK != last_state_CLK) {
    if (digitalRead(ROTARY_ENCODER_DT) != current_state_CLK)
      percentage = std::min(percentage + CHANGE_RATE, MAX_PERCENTAGE);
    else
      percentage = std::max(percentage - CHANGE_RATE, 0);
    last_state_CLK = current_state_CLK;
    return true;
  }
  last_state_CLK = current_state_CLK;
  return false;
}

bool RotaryEncoder::check_press() {
  if ((millis() - last_press_update > delay_between_presses)
      && (digitalRead(ROTARY_ENCODER_SW) == LOW)) {
    last_press_update = millis();
    percentage = 0;
    return true;
  }
  return false;
}

void RotaryEncoder::check_and_send() {
  if (check_rotation() || check_press())
    send_reading(percentage);
}
#endif
#endif
