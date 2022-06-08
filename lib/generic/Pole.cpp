#include "Pole.hpp"

#include <cstdio>

Pole::Pole() {
  for (int x = 0; x < kGridWidth; x++) {
    std::vector<CRGB> row;
    for (int y = 0; y < kGridHeight; y++) {
      row.push_back({0, 0, 0});
    }
    grid_lights.push_back(std::move(row));
  }
}

void Pole::SetGridLight(uint8_t x, uint8_t y, const CRGB &rgb) {
  grid_lights[y][x] = rgb;
}

void Pole::SetGridLight(uint8_t x, uint8_t y, const CHSV &hsv) {
  SetGridLight(x, y, CRGB(hsv));
}

void Pole::SetGridLights(std::vector<std::vector<CHSV>> const &grid_lights) {
  for (int x = 0; x < kGridWidth; x++) {
    for (int y = 0; y < kGridHeight; y++) {
      SetGridLight(x, y, grid_lights[x][y]);
    }
  }
}

void Pole::MultiplyGridLight(uint8_t x, uint8_t y, const CRGB &rgb) {
  uint16_t red = (uint16_t)rgb.r + grid_lights[y][x].r;
  uint16_t remainder = 0;
  if (red > 255) {
    remainder += red - 255;
    red = 255;
  }
  uint16_t green = (uint16_t)rgb.g + grid_lights[y][x].g;
  uint8_t greenR = 0;
  if (green > 255) {
    remainder += green - 255;
    green = 255;
  }
  uint16_t blue = (uint16_t)rgb.b + grid_lights[y][x].b;
  uint8_t blueR = 0;
  if (blue > 255) {
    remainder += blue - 255;
    blue = 255;
  }

  while (remainder > 0 && !(red == 255 && blue == 255 && green == 255)) {
    if (red < 255) {
      red++;
      remainder--;
    }
    if (green < 255) {
      green++;
      remainder--;
    }
    if (blue < 255) {
      blue++;
      remainder--;
    }
  }

  grid_lights[y][x] = CRGB(red, green, blue);
}

void Pole::MultiplyGridLight(uint8_t x, uint8_t y, const CHSV &hsv) {
  MultiplyGridLight(x, y, CRGB(hsv));
}

void Pole::MultiplyGridLights(
    std::vector<std::vector<CHSV>> const &grid_lights) {
  for (int x = 0; x < kGridWidth; x++) {
    for (int y = 0; y < kGridHeight; y++) {
      MultiplyGridLight(x, y, grid_lights[x][y]);
    }
  }
}

void Pole::ClearGridLights() {
  for (int x = 0; x < kGridWidth; x++) {
    for (int y = 0; y < kGridHeight; y++) {
      SetGridLight(x, y, CRGB(0, 0, 0));
    }
  }
}
