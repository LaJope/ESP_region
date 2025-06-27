#pragma once

#include "defines.h"

#ifdef PRODUCER
#ifdef ROTARY_ENCODER

#include <cstdint>

struct RotaryEncoder {
  int current_state_CLK;
  int last_state_CLK;

  uint64_t last_press_update = 0;
  const uint64_t delay_between_presses = 400;

  int percentage = 100;

  void setup_pins();

  bool check_rotation();
  bool check_press();

  void check_and_send();
};

#endif
#endif
