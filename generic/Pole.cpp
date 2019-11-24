#include "Pole.hpp"

Pole::Pole() {
  for (int x = 0; x < grid_height; x++) {
    for (int y = 0; y < grid_width; y++) {
      grid_lights[x].push_back({0, 0, 0});
    }
  }
}

void Pole::SetGridLight(uint8_t x, uint8_t y, CRGB &rgb) {
  grid_lights[x][y] = rgb;
}

const std::vector<std::vector<CRGB>> Pole::get_grid_lights() {
  return grid_lights;
}
