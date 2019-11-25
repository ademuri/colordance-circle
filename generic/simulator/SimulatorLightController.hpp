#ifndef __SIMULATOR_LIGHT_CONTROLLER_HPP__
#define __SIMULATOR_LIGHT_CONTROLLER_HPP__

#include <OgreLight.h>
#include <OgreSceneManager.h>
#include <chrono>
#include <map>

/*
 * Interface class for controlling the output lights. Eventually, there will be
 * a subclass of this that uses DMX to control real lights.
 */
class SimulatorLightController {
 public:
  SimulatorLightController(Ogre::SceneManager *scnMgr);

  Ogre::Light *createLight(Ogre::Vector3 const position);

  /*
   * Converts inches to the x-y-z coordinates used by Ogre. This is all
   * relative to the height of the ninja mesh used, which is 192 coordinate
   * units tall. This assumes that the ninja is 5'4" (average human height).
   */
  static float inchesToCoords(float inches);
  static float feetToCoords(float inches);

 private:
  Ogre::SceneManager *const scnMgr;
};

#endif
