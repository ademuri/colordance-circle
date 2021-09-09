#include "ControlPoleEffectLine.hpp"

ControlPoleEffectLine::ControlPoleEffectLine(uint16_t framesPerLoop)
    : ControlPoleEffect(framesPerLoop) {
  lightCount = 4;
}

uint8_t ControlPoleEffectLine::GetShiftsPerLoop() {
  uint8_t shiftsPerLoop = 4;
  if (rotation % 2 == 1 && lightCount == 2) {
    shiftsPerLoop = 3;
  } else if (rotation % 2 == 1 && lightCount == 4) {
    shiftsPerLoop = 7;
  }
  return shiftsPerLoop;
}

void ControlPoleEffectLine::DoSetGrid(uint8_t shiftIndex) {
  // For still animation, make diagonal in the middle
  if (isStill && lightCount >= 3 && rotation % 2 == 1) {
    shiftIndex = lightCount == 4 ? 3 : 1;
  }

  bool xReverse = rotation >= 2;

  if (rotation % 2 == 0) {
    bool isLeftRight = rotation % 4 == 0;
    for (uint8_t trailIndex = 0; trailIndex < lightCount; trailIndex++) {
      int xIndex = isLeftRight ? shiftIndex : trailIndex;
      int yIndex = isLeftRight ? trailIndex : shiftIndex;
      grid_lights[xReverse ? 3 - xIndex : xIndex][yIndex] =
          CHSV(currentHue + GetHueDistance(hueDistance, trailIndex, lightCount),
               baseSat, baseVal);
    }
  } else if (lightCount != 4) {
    int xIndex = xReverse ? 3 - shiftIndex : shiftIndex;
    int yIndex = shiftIndex;
    if (lightCount == 2) {
      grid_lights[xIndex + 1 * (xReverse ? -1 : 1)][yIndex] = CHSV(
          currentHue + GetHueDistance(hueDistance, 0, 2), baseSat, baseVal);
      grid_lights[xIndex][yIndex + 1] = CHSV(
          currentHue + GetHueDistance(hueDistance, 1, 2), baseSat, baseVal);
    } else {
      // 1 or 3 lights
      uint8_t brightness =
          isStill ? baseVal : AdjustedBrightness(baseVal, 1, 1 /* minLights */);
      if (lightCount == 3 && (shiftIndex == 1 || shiftIndex == 2)) {
        if (!isStill) {
          brightness = AdjustedBrightness(baseVal, 3, 1 /* minLights */);
        }
        if (xReverse) {
          grid_lights[xIndex - 1][yIndex - 1] =
              CHSV(currentHue + GetHueDistance(hueDistance, 0, 3), baseSat,
                   brightness);
          grid_lights[xIndex + 1][yIndex + 1] =
              CHSV(currentHue + GetHueDistance(hueDistance, 2, 3), baseSat,
                   brightness);
        } else {
          grid_lights[xIndex - 1][yIndex + 1] =
              CHSV(currentHue + GetHueDistance(hueDistance, 2, 3), baseSat,
                   brightness);
          grid_lights[xIndex + 1][yIndex - 1] =
              CHSV(currentHue + GetHueDistance(hueDistance, 0, 3), baseSat,
                   brightness);
        }
      }
      grid_lights[xIndex][yIndex] =
          CHSV(currentHue + GetHueDistance(hueDistance, 1, lightCount), baseSat,
               brightness);
    }
  } else {
    // 4 lights
    uint8_t shiftLightCount = shiftIndex < 4 ? shiftIndex + 1 : 7 - shiftIndex;
    uint8_t brightness = isStill ? baseVal
                                 : AdjustedBrightness(baseVal, shiftLightCount,
                                                      1 /* minLights */);
    if (shiftIndex < 4) {
      for (int diagonalAxis = 0; diagonalAxis <= shiftIndex; diagonalAxis++) {
        int xIndex = xReverse ? 3 - (shiftIndex - diagonalAxis)
                              : shiftIndex - diagonalAxis;
        int yIndex = diagonalAxis;
        uint8_t hue = currentHue + GetHueDistance(hueDistance, diagonalAxis,
                                                  shiftLightCount);
        grid_lights[xIndex][yIndex] = CHSV(hue, baseSat, brightness);
      }
    } else {
      for (int diagonalAxis = 3; diagonalAxis >= shiftIndex - 3;
           diagonalAxis--) {
        int xIndex = xReverse ? 3 - diagonalAxis : diagonalAxis;
        int yIndex = shiftIndex - diagonalAxis;
        uint8_t hue = currentHue + GetHueDistance(hueDistance, 3 - diagonalAxis,
                                                  shiftLightCount);
        grid_lights[xIndex][yIndex] = CHSV(hue, baseSat, brightness);
      }
    }
  }
}
