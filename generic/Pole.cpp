#include "Pole.hpp"
#include <cstdio>

Pole::Pole() {
  for (int x = 0; x < kGridWidth; x++) {
    std::vector<CRGB> row;
    for (int y = 0; y < kGridHeight; y++) {
      row.push_back({0, 0, 0});
    }
    grid_lights.push_back(row);
  }
}

void Pole::SetGridLight(uint8_t x, uint8_t y, const CRGB &rgb) {
  grid_lights[y][x] = rgb;
}

void Pole::SetGridLight(uint8_t x, uint8_t y, const CHSV &hsv) {
  SetGridLight(x, y, CRGB(hsv));
}

void Pole::ClearGridLights() {
  for (int x = 0; x < kGridWidth; x++) {
    for (int y = 0; y < kGridHeight; y++) {
      SetGridLight(x, y, CRGB(0, 0, 0));
    }
  }
}

const std::vector<std::vector<CRGB>> Pole::get_grid_lights() {
  return grid_lights;
}
