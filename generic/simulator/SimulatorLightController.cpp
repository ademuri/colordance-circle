#include "SimulatorLightController.hpp"
#include <OgreLight.h>
#include <OgreSceneNode.h>
#include <chrono>
#include <cstdio>
#include <map>
#include <utility>

SimulatorLightController::SimulatorLightController(Ogre::SceneManager *scnMgr)
    : scnMgr(scnMgr) {}

Ogre::Light *SimulatorLightController::createLight(
    Ogre::Vector3 const position) {
  Ogre::Light *spotLight = scnMgr->createLight();
  spotLight->setType(Ogre::Light::LT_SPOTLIGHT);
  spotLight->setDirection(Ogre::Vector3::NEGATIVE_UNIT_Z);
  // Default lights to off
  spotLight->setDiffuseColour(0, 0, 0);
  spotLight->setSpecularColour(0, 0, 0);

  Ogre::SceneNode *spotLightNode =
      scnMgr->getRootSceneNode()->createChildSceneNode();
  spotLightNode->attachObject(spotLight);
  spotLightNode->setDirection(0, 0, -1);
  spotLightNode->setPosition(position);
  spotLightNode->lookAt(Ogre::Vector3(0, inchesToCoords(30), 0),
                        Ogre::Node::TransformSpace::TS_WORLD);

  spotLight->setSpotlightRange(Ogre::Degree(60), Ogre::Degree(75));

  // Not actually measured, just a wild guess
  spotLight->setSpotlightFalloff(0.5);

  // Make light get less bright farther away from the light sources.
  spotLight->setAttenuation(2000, /* constant */ 1.0, /* linear */ 0.0007,
                            /* quadratic */ 0.0);

  return spotLight;
}

float SimulatorLightController::inchesToCoords(float inches) {
  // 64" == 5'4". Model is 192 units tall.
  return inches * 192.0 / 64.0;
}

float SimulatorLightController::feetToCoords(float feet) {
  return inchesToCoords(12.0 * feet);
}
