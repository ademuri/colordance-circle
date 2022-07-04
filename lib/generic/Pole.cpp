#include "Pole.hpp"

#include <cstdio>

Pole::Pole() { ClearGridLights(); }

void Pole::SetGridLight(uint8_t x, uint8_t y, const CRGB &rgb) {
  grid_lights[y][x] = rgb;
}

void Pole::SetGridLight(uint8_t x, uint8_t y, const CHSV &hsv) {
  SetGridLight(x, y, CRGB(hsv));
}

void Pole::SetGridLights(Grid<CHSV> const &grid_lights) {
  for (int x = 0; x < gridWidth; x++) {
    for (int y = 0; y < gridHeight; y++) {
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
  if (green > 255) {
    remainder += green - 255;
    green = 255;
  }
  uint16_t blue = (uint16_t)rgb.b + grid_lights[y][x].b;
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

void Pole::MultiplyGridLights(Grid<CHSV> const &grid_lights) {
  for (int x = 0; x < gridWidth; x++) {
    for (int y = 0; y < gridHeight; y++) {
      MultiplyGridLight(x, y, grid_lights[x][y]);
    }
  }
}

void Pole::ClearGridLights() {
  for (int y = 0; y < gridHeight; y++) {
    for (int x = 0; x < gridWidth; x++) {
      SetGridLight(x, y, CRGB(0, 0, 0));
    }
  }
}
