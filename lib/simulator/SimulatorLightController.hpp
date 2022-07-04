#pragma once

#include <OgreLight.h>
#include <OgreSceneManager.h>

#include <chrono>
#include <map>
#include <vector>

#include "Pole.hpp"

/*
 * Interface class for controlling the output lights.
 */
class SimulatorLightController {
 public:
  SimulatorLightController(Ogre::SceneManager *scnMgr);

  void WriteOutLights();

  /*
   * Converts inches to the x-y-z coordinates used by Ogre. This is all
   * relative to the height of the ninja mesh used, which is 192 coordinate
   * units tall. This assumes that the ninja is 5'4" (average human height).
   */
  static float inchesToCoords(float inches);
  static float feetToCoords(float inches);

 private:
  Poles poles;

  Ogre::Light *createLight(Ogre::Vector3 const position);

  Ogre::SceneManager *const scnMgr;

  std::vector<std::vector<std::vector<Ogre::Light *>>> lights;

  // Tuning constants
  // Physical
  static constexpr float kPixelPitchInches = 3;
  static constexpr float kCircleRadiusInches = 7.5 * 12;
  static constexpr float kPoleHeightInches = 10 * 12;

  // Dims the lights by this factor, to avoid clipping.
  static constexpr float kLightScale = 0.3;
};
