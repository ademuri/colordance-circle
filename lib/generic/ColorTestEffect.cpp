#include "ColorTestEffect.hpp"

#include "ColordanceTypes.hpp"

ColorTestEffect::ColorTestEffect(std::vector<Pole*> poles,
                                 ParamController* paramController)
    : Effect(poles, paramController) {}

void ColorTestEffect::DoRun() {
  uint8_t inverseSpeed = 15;
  uint8_t inverseColorSpeed = 10;

  for (int i = 0; i < 6; i++) {
    poles[i]->ClearGridLights();
  }

  uint32_t colorTimer = timer / inverseColorSpeed;

  CHSV color = CHSV(colorTimer, 255, 255);
  CHSV colorMid1 = CHSV(colorTimer + (128 / 3), 255, 255);
  CHSV colorMid2 = CHSV(colorTimer + (128 / 3) * 2, 255, 255);
  CHSV oppositeColor = CHSV(colorTimer + 128, 255, 255);

  uint8_t oppositePole = timer / inverseSpeed % 14;

  // if (timer/10 % 10 < 5) {
  //   oppositePole = (timer / 10) % 5 + 1;
  // } else {
  // 	oppositePole = 5 - (timer / 10) % 5;
  // }
  if (oppositePole > 6) {
    oppositePole = 13 - oppositePole;
  }

  if (oppositePole == 0) {
    for (int i = 1; i < 3; i++) {
      poles[0]->SetGridLight(0, i, color);
      poles[0]->SetGridLight(1, i, colorMid1);
      poles[0]->SetGridLight(2, i, colorMid2);
      poles[0]->SetGridLight(3, i, oppositeColor);
    }
  } else if (oppositePole == 6) {
    for (int i = 1; i < 3; i++) {
      poles[0]->SetGridLight(3, i, color);
      poles[0]->SetGridLight(2, i, colorMid1);
      poles[0]->SetGridLight(1, i, colorMid2);
      poles[0]->SetGridLight(0, i, oppositeColor);
    }
  } else {
    for (int i = 1; i < 3; i++) {
      for (int j = 1; j < 3; j++) {
        poles[0]->SetGridLight(i, j, color);
        poles[oppositePole % 6]->SetGridLight(i, j, oppositeColor);
      }
    }
  }

  // CRGB color = CHSV(timer, 255, 255);

  // uint8_t value = timer;
  // uint8_t red = 0;
  // uint8_t green = 0;
  // uint8_t blue = 0;
  // uint8_t yellow = 0;
  // uint8_t cyan = 0;
  // uint8_t magenta = 0;

  //  if(timer % (3*256) < 256) {
  //  	red = value;
  //  	blue = 255 - value;
  //  } else if(timer % (3*256) < 256*2) {
  //  	red = 255 - value;
  //  	green = value;
  //  } else {
  //  	green = 255 - value;
  //  	blue = value;
  //  }

  //  uint8_t altValue = timer - 128;
  //  if((timer-128) % (3*256) < 256) {
  //  	yellow = altValue;
  //  	magenta = 255 - altValue;
  //  } else if((timer-128) % (3*256) < 256*2) {
  //  	yellow = 255 - altValue;
  //  	cyan = altValue;
  //  } else {
  //  	cyan = 255 - altValue;
  //  	magenta = altValue;
  //  }

  // for(int i=0; i<3; i++) {

  // 	poles[0]->SetGridLight(0, i,
  //                          CRGB(red, 0, 0));
  // 	poles[0]->SetGridLight(1, i,
  //                          CRGB(0, green, 0));
  // 	poles[0]->SetGridLight(2, i,
  //                          CRGB(0, 0, blue));

  // 	poles[2]->SetGridLight(0, i,
  //                          CRGB(green, 0, 0));
  // 	poles[2]->SetGridLight(1, i,
  //                          CRGB(0, blue, 0));
  // 	poles[2]->SetGridLight(2, i,
  //                          CRGB(0, 0, red));

  // 	poles[4]->SetGridLight(0, i,
  //                          CRGB(blue, 0, 0));
  // 	poles[4]->SetGridLight(1, i,
  //                          CRGB(0, red, 0));
  // 	poles[4]->SetGridLight(2, i,
  //                          CRGB(0, 0, green));
  //	}

  // for(int i = 1; i < 3; i++) {
  // 	for(int j = 1; j < 3; j++) {
  // 		poles[0]->SetGridLight(i, j,
  //                          CRGB(red, 0, 0));
  // 		poles[2]->SetGridLight(i, j,
  //                          CRGB(0, green, 0));
  // 		poles[4]->SetGridLight(i, j,
  //                          CRGB(0, 0, blue));

  // 		poles[1]->SetGridLight(i, j,
  //                          CRGB(yellow/2, yellow/2, 0));

  // 		poles[3]->SetGridLight(i, j,
  //                          CRGB(0, cyan/2, cyan/2));

  // 		poles[5]->SetGridLight(i, j,
  //                          CRGB(magenta/2, 0, magenta/2));

  // poles[3]->SetGridLight(i, j,
  //                        CRGB(0, red/2, red/2));
  // poles[5]->SetGridLight(i, j,
  //                        CRGB(green/2, 0, green/2));
  // poles[1]->SetGridLight(i, j,
  //                        CRGB(blue/2, blue/2, 0));
  // 	}
  // }

  timer++;
  SleepMs(10);
}
