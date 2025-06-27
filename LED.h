#pragma once

#include "defines.h"
#include <array>

#include <cstdint>
#include <unordered_map>

struct LED {
  struct color {
    uint8_t red = 0;
    uint8_t green = 0;
    uint8_t blue = 0;
  };
  const std::array<color, 48> day_working{
      color{25, 25, 112},   color{32, 47, 129},   color{38, 65, 147},
      color{41, 86, 165},   color{42, 108, 183},  color{41, 129, 201},
      color{36, 149, 220},  color{25, 171, 239},  color{45, 193, 251},
      color{117, 193, 226}, color{153, 197, 201}, color{180, 199, 175},
      color{200, 203, 149}, color{218, 205, 122}, color{233, 209, 92},
      color{247, 212, 55},  color{255, 216, 20},  color{253, 215, 48},
      color{252, 218, 66},  color{250, 222, 82},  color{248, 223, 96},
      color{246, 225, 109}, color{244, 228, 122}, color{241, 229, 134},
      color{233, 227, 148}, color{218, 222, 164}, color{202, 217, 179},
      color{184, 212, 194}, color{163, 207, 208}, color{139, 203, 222},
      color{107, 197, 236}, color{54, 194, 250},  color{25, 175, 244},
      color{38, 151, 227},  color{42, 126, 211},  color{43, 103, 194},
      color{39, 81, 178},   color{33, 59, 162},   color{23, 35, 146},
      color{4, 4, 131},     color{3, 3, 126},     color{9, 7, 124},
      color{13, 11, 122},   color{18, 14, 120},   color{19, 17, 118},
      color{22, 20, 116},   color{23, 23, 114},   color{25, 25, 112}};
  const std::array<color, 48> day_broken{
      color{139, 0, 0},   color{146, 0, 0},   color{153, 0, 0},
      color{160, 0, 3},   color{167, 0, 3},   color{175, 0, 3},
      color{182, 0, 3},   color{189, 0, 3},   color{197, 0, 3},
      color{204, 0, 3},   color{212, 0, 4},   color{219, 0, 0},
      color{227, 0, 0},   color{234, 0, 0},   color{242, 0, 0},
      color{250, 0, 0},   color{255, 4, 0},   color{255, 17, 0},
      color{255, 21, 0},  color{255, 30, 0},  color{255, 34, 0},
      color{255, 38, 0},  color{255, 42, 0},  color{255, 47, 0},
      color{255, 51, 0},  color{255, 51, 0},  color{255, 55, 0},
      color{255, 60, 0},  color{255, 60, 0},  color{255, 64, 0},
      color{255, 68, 0},  color{255, 68, 0},  color{254, 68, 6},
      color{251, 66, 14}, color{249, 62, 20}, color{247, 58, 25},
      color{245, 58, 29}, color{243, 54, 33}, color{240, 53, 36},
      color{238, 49, 39}, color{236, 45, 42}, color{234, 43, 46},
      color{231, 40, 49}, color{229, 36, 49}, color{227, 33, 52},
      color{225, 29, 55}, color{222, 25, 58}, color{220, 20, 60}};

  void setup_pins();
#ifdef CONSUMER
  void rotate_color(uint8_t time, bool isOn);
#endif
#ifdef PRODUCER
  void rotate_color(int percentage);
#endif
  void output_color(color col);
  void dim_light(color &col, int factor);
};
