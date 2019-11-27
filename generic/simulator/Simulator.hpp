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

 private:
  SimulatorLightController *controller;

  Ogre::SceneNode *ninja_node;
  int ninjaClock = 0;

  SimulatorLightController *lightController;
};

#endif
