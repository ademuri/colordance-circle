#include "SimulatorLightController.hpp"
#include <OgreLight.h>
#include <OgreSceneNode.h>
#include <chrono>
#include <map>
#include <utility>
#include <cstdio>

SimulatorLightController::SimulatorLightController(Ogre::SceneManager *scnMgr)
    : scnMgr(scnMgr) {
}

Ogre::Light *SimulatorLightController::createLight(
    Ogre::Vector3 const position) {
  Ogre::Light *spotLight = scnMgr->createLight();
  spotLight->setType(Ogre::Light::LT_SPOTLIGHT);
  spotLight->setDirection(Ogre::Vector3::NEGATIVE_UNIT_Z);
  // Default lights to off
  spotLight->setDiffuseColour(0.15, 0.15, 0.15);
  spotLight->setSpecularColour(0.15, 0.15, 0.15);

  Ogre::SceneNode *spotLightNode =
      scnMgr->getRootSceneNode()->createChildSceneNode();
  spotLightNode->attachObject(spotLight);
  spotLightNode->setDirection(0, 0, -1);
  spotLightNode->setPosition(position);
  spotLightNode->lookAt(Ogre::Vector3(0, inchesToCoords(30), 0),
                        Ogre::Node::TransformSpace::TS_WORLD);

  spotLight->setSpotlightRange(Ogre::Degree(60), Ogre::Degree(60));

  // Not actually measured, just a wild guess
  // TODO: tune this?
  spotLight->setSpotlightFalloff(10);

  // Make light get less bright farther away from the light sources.
  // TODO: tune this?
  spotLight->setAttenuation(2000, /* constant */ 1.0, /* linear */ 0.0005,
                            /* quadratic */ 0.0);

  return spotLight;
}

int SimulatorLightController::inchesToCoords(int inches) {
  // 64" == 5'4". Model is 192 units tall.
  return (inches * 192) / 64;
}

int SimulatorLightController::feetToCoords(int feet) {
  return inchesToCoords(12 * feet);
}
