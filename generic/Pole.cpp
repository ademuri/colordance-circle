#include "Pole.hpp"
#include <cstdio>

Pole::Pole() {
  for (int x = 0; x < grid_height; x++) {
    std::vector<CRGB> row;
    for (int y = 0; y < grid_width; y++) {
      row.push_back({0, 0, 0});
    }
    grid_lights.push_back(row);
  }
}

void Pole::SetGridLight(uint8_t x, uint8_t y, const CRGB &rgb) {
  grid_lights[x][y] = rgb;
}

void Pole::SetGridLight(uint8_t x, uint8_t y, const CHSV &hsv) {
  grid_lights[x][y] = hsv;
}

const std::vector<std::vector<CRGB>> Pole::get_grid_lights() {
  return grid_lights;
}
