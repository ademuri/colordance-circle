#ifndef SLIDERS_HPP_
#define SLIDERS_HPP_

#include <vector>

#include "ColordanceTypes.hpp"
#include "Pole.hpp"
#include "interface/InterfaceEffect.hpp"

class Sliders : public InterfaceEffect {
 public:
  Sliders(std::vector<HelperPole*> helperPoles);

 protected:
  bool ContinuousShift() override;
  void DoSetGrid(std::vector<Pole*> poles, uint16_t frame) override;
  void UpdateOption1() override;
  void UpdateOption2() override;
  void UpdateSlider1(uint8_t val) override;
  void UpdateSlider2(uint8_t val) override;
  void DoShift(uint8_t shiftPosition) override;
  void Reset() override;

 private:
  // void SetMode0(std::vector<Pole *> poles, uint8_t position);
  // void SetMode1(std::vector<Pole *> poles);
  // void UpdateGrid(std::vector<std::vector<CHSV>> &pole, uint8_t position,
  //                 uint8_t hue, uint8_t sat);
  // void TurnOffAll(std::vector<std::vector<CHSV>> &pole);

  HelperPole* pole_left;
  HelperPole* pole_right;

  uint32_t lastFrame = 0;

  uint8_t count = 0;

  uint8_t leftIndex = 0;
  uint8_t rightIndex = 5;
  bool swap = false;

  uint8_t hueLeft = 0;
  uint8_t hueRight = 127;

  uint8_t mode = 0;
  bool smoothHue = false;

  uint8_t numOfPolesOn = 1;
  bool backAndForth = false;
  bool smoothPoleShift = false;
};

#endif
