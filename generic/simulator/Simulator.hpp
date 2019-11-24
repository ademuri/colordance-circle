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
#include "SimulatorLightController.hpp"

class Simulator : public OgreBites::ApplicationContext,
                  public OgreBites::InputListener {
 public:
  Simulator();

  void setup() override;
  bool frameEnded(const Ogre::FrameEvent &evt) override;

 private:
  SimulatorLightController *controller;

  Ogre::SceneNode *ninjaNode;
  int ninjaClock = 0;

  SimulatorLightController *lightController;
  std::vector<Ogre::Light *> lights;
};

#endif
