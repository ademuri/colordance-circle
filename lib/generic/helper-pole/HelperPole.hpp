#ifndef HELPER_POLE_HPP_
#define HELPER_POLE_HPP_

#include <vector>

#include "ColordanceTypes.hpp"

// enum class Mode {
//   kCircle,
//   kCross,
//   kDiverge,
//   kLine,
//   kPinwheel
// };

class HelperPole {
 public:
  HelperPole(uint16_t framesPerLoop);

 private:
  const uint16_t FRAMES_PER_LOOP;
};

#endif
