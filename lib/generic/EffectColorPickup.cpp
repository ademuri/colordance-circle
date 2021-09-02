#include "EffectColorPickup.hpp"

#include "ColordanceTypes.hpp"

EffectColorPickup::EffectColorPickup(std::vector<Pole*> poles,
                                     ParamController* paramController)
    : Effect(poles, paramController) {}

void EffectColorPickup::DoRun() {
  for (int i = 0; i < 6; i++) {
    poles[i]->ClearGridLights();
  }

  uint8_t inverseSpeed = 20;
  uint8_t inverseColorSpeed = 68;
  uint8_t polesOn = 3;
  uint8_t frame = 0;

  uint32_t colorTimer = timer / inverseColorSpeed;

  uint8_t hue = 0;

  frame = timer / 20 % 8;

  // uint8_t pole = frame < 4 ? frame + 1 : frame == 4 ? 3 : 2;
  uint8_t pole = frame % 4 + 1;

  setSquare(0, frame < 4 ? hue : hue + 128);
  setSquare(5, frame < 4 ? hue + 128 : hue);
  setSquare(pole, hue + (frame < 4 ? frame + 3 : frame - 4) * (128 / 3));

  timer++;
  SleepMs(20);

  return;

  // 	frame = timer/10 % 22;

  // if(frame >= 12) {
  // 	frame = 22 - frame;
  // }
  // setLine(frame/4, frame%4, 0);
  // setLine(2 - frame/4, 3-frame%4, 2*(255/6));
  // setLine(3 + frame/4, frame%4, 3*(255/6));
  // setLine(5 - frame/4, 3-frame%4, 5*(255/6));

  // timer++;
  //  	SleepMs(20);

  // return;

  // frame = timer/inverseSpeed % 10;

  // if (frame < 4) {
  // 	setLine(0, frame, 0);
  // 	setLine(2, 3-frame, 2*(255/6));
  // 	setLine(3, frame, 3*(255/6));
  // 	setLine(5, 3-frame, 5*(255/6));
  // } else if (frame < 7) {
  // 	setLine(1, frame%2, 0);
  // 	setLine(1, 3-frame%2, 2*(255/6));
  // 	setLine(4, frame%2, 3*(255/6));
  // 	setLine(4, 3-frame%2, 5*(255/6));
  // } else {
  // 	setLine(0, 10-frame, 0);
  // 	setLine(2, frame-7, 2*(255/6));
  // 	setLine(3, 10-frame, 3*(255/6));
  // 	setLine(5, frame-7, 5*(255/6));
  // }

  // timer++;
  //  	SleepMs(20);

  // return;

  if (polesOn == 2) {
    CHSV color = CHSV(colorTimer, 255, 255);
    CHSV colorMid1 = CHSV(colorTimer + (128 / 3), 255, 255);
    CHSV colorMid2 = CHSV(colorTimer + (128 / 3) * 2, 255, 255);
    CHSV oppositeColor = CHSV(colorTimer + 128, 255, 255);

    uint8_t frame = timer / inverseSpeed % 12;

    if (frame == 0) {
      for (int i = 1; i < 3; i++) {
        poles[0]->SetGridLight(0, i, color);
        poles[0]->SetGridLight(1, i, colorMid1);
        poles[0]->SetGridLight(2, i, colorMid2);
        poles[0]->SetGridLight(3, i, oppositeColor);
      }
    } else if (frame < 6) {
      for (int i = 1; i < 3; i++) {
        for (int j = 1; j < 3; j++) {
          poles[0]->SetGridLight(i, j, color);
          poles[frame]->SetGridLight(i, j, oppositeColor);
        }
      }
    } else if (frame == 6) {
      for (int i = 1; i < 3; i++) {
        poles[0]->SetGridLight(3, i, color);
        poles[0]->SetGridLight(2, i, colorMid1);
        poles[0]->SetGridLight(1, i, colorMid2);
        poles[0]->SetGridLight(0, i, oppositeColor);
      }
    } else {
      for (int i = 1; i < 3; i++) {
        for (int j = 1; j < 3; j++) {
          poles[frame % 6]->SetGridLight(i, j, color);
          poles[0]->SetGridLight(i, j, oppositeColor);
        }
      }
    }
  } else if (polesOn == 3) {
    uint8_t hueA = colorTimer;
    uint8_t hueB = colorTimer + (255 / 3);
    uint8_t hueC = colorTimer + 2 * (255 / 3);

    uint8_t frame = timer / inverseSpeed % 18;

    uint8_t poleWithA =
        frame < 7 ? 0 : frame < 10 ? frame - 6 : frame < 16 ? 3 : frame - 12;
    uint8_t poleWithB =
        frame < 4
            ? 3
            : frame < 6 ? frame : frame < 13 ? 0 : frame < 16 ? frame - 12 : 3;
    uint8_t poleWithC =
        frame < 4 ? frame : frame < 10 ? 3 : frame < 12 ? frame - 6 : 0;

    setSquare(poleWithA, hueA);
    setSquare(poleWithB, hueB);
    setSquare(poleWithC, hueC);

    if (poleWithA == poleWithB) {
      setMergedSquare(poleWithA, hueB, hueA);
    } else if (poleWithA == poleWithC) {
      setMergedSquare(poleWithA, hueA, hueC);
    } else if (poleWithB == poleWithC) {
      setMergedSquare(poleWithB, hueC, hueB);
    }

  } else {
    // frame = (timer/2) % 255;
    // if(frame < 64) {
    // } else if(frame < 128) {
    // 	frame = 128 - frame;
    // } else if(frame < 192) {
    // 	frame = frame - 128;
    // } else {
    // 	frame = 255 - frame;
    // }
    // for (int i=0; i<6; i+=2) {
    // 	poles[i]->SetGridLight(0, 1, colorTimer + CHSV(i*(255/6) - frame, 255,
    // 255)); 	poles[i]->SetGridLight(3, 1, colorTimer + CHSV(i*(255/6) +
    // frame, 255, 255));
    // }
    uint8_t maxDistance = 32;  // 32 or 64
    frame = (timer / 4) % (maxDistance * 4);
    if (frame < maxDistance) {
      // 0 -> 32
    } else if (frame < 3 * maxDistance) {
      frame = 2 * maxDistance - frame;  // 32 -> 0 -> -32
    } else {
      frame = frame - 4 * maxDistance;  // -32 -> 0
    }
    for (int i = 0; i < 6; i += 2) {
      poles[i]->SetGridLight(
          0, 1, CHSV(colorTimer + i * (255 / 6) - 3 * frame, 255, 255));
      poles[i]->SetGridLight(
          1, 1, CHSV(colorTimer + i * (255 / 6) - frame, 255, 255));
      poles[i]->SetGridLight(
          2, 1, CHSV(colorTimer + i * (255 / 6) + frame, 255, 255));
      poles[i]->SetGridLight(
          3, 1, CHSV(colorTimer + i * (255 / 6) + 3 * frame, 255, 255));
    }
  }

  timer++;
  SleepMs(20);
}

void EffectColorPickup::setMergedSquare(uint8_t pole, uint8_t hue1,
                                        uint8_t hue2) {
  for (int j = 1; j < 2; j++) {
    poles[pole]->SetGridLight(0, j, CHSV(hue1 + j * 20, 255, 255));
    poles[pole]->SetGridLight(1, j,
                              CHSV((2 * hue1 + hue2) / 3 + j * 20, 255, 255));
    poles[pole]->SetGridLight(2, j,
                              CHSV((hue1 + 2 * hue2) / 3 + j * 20, 255, 255));
    poles[pole]->SetGridLight(3, j, CHSV(hue2 + j * 20, 255, 255));
  }
}

void EffectColorPickup::setSquare(uint8_t pole, uint8_t hue) {
  for (int i = 1; i < 3; i++) {
    // uint8_t iOffset = i == 1 ? 255-20 : 20;
    uint8_t iOffset = 0;
    for (int j = 1; j < 2; j++) {
      poles[pole]->SetGridLight(i, j, CHSV(hue + iOffset, 255, 255));
    }
  }
}

void EffectColorPickup::setLine(uint8_t pole, uint8_t x, uint8_t hue) {
  for (int j = 0; j < 4; j++) {
    poles[pole]->SetGridLight(x, j, CHSV(hue, 255, 255));
  }
}
