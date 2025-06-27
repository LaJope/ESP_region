#pragma once

#include "defines.h"

#ifdef PRODUCER
#ifdef POTENTIOMETER

#include <cstdint>

struct Potentiometer {
  int percentage = 100;

  uint64_t last_update = 0;
  const uint64_t delay_between_updates = 400;

  void setup_pins();

  void check_and_send();

  int get_percentage();
};

#endif
#endif
