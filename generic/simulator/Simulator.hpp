#ifndef __SIMULATOR_HPP__
#define __SIMULATOR_HPP__

#include <OgreApplicationContext.h>
#include <OgreInput.h>
#include <OgreLight.h>
#include <OgreRoot.h>
#include <algorithm>
#include <map>
#include <set>
#include <string>
#include <vector>
#include "Effect.hpp"
#include "SimulatorLightController.hpp"

class Simulator : public OgreBites::ApplicationContext,
                  public OgreBites::InputListener {
 public:
  Simulator();

  void setup() override;
  bool frameEnded(const Ogre::FrameEvent &evt) override;
  bool keyPressed(const OgreBites::KeyboardEvent &evt) override;
  bool keyReleased(const OgreBites::KeyboardEvent &evt) override;
  bool mouseMoved(const OgreBites::MouseMotionEvent &evt) override;

 private:
  SimulatorLightController *controller;

  // Ninja follows the mouse. Press spacebar to toggle moving in a circle
  // automatically.
  Ogre::SceneNode *ninja_node;
  Ogre::Vector3 ninja_pos = {300, 0, 300};
  int ninja_clock = 0;
  bool ninja_follow_mouse = true;

  SimulatorLightController *lightController;
  Effect *effect;
};

#endif
