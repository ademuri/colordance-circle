#include "SimulatorLightController.hpp"
#include <OgreLight.h>
#include <OgreSceneNode.h>
#include <chrono>
#include <cstdio>
#include <map>
#include <utility>

SimulatorLightController::SimulatorLightController(Ogre::SceneManager *scnMgr)
    : LightController(), scnMgr(scnMgr) {
  for (int pole_index = 0; pole_index < 6; pole_index++) {
    Pole *pole = new Pole();
    const unsigned long grid_num_rows = pole->get_grid_lights().size();
    const unsigned long grid_num_cols = pole->get_grid_lights().front().size();

    std::vector<std::vector<Ogre::Light *>> light_pole;
    for (unsigned long row = 0; row < grid_num_rows; row++) {
      std::vector<Ogre::Light *> light_row;
      for (unsigned long col = 0; col < grid_num_cols; col++) {
        Ogre::Vector3 vector = Ogre::Vector3(
            SimulatorLightController::inchesToCoords(90) *
                    cos(3.14 / 3.0 * pole_index) +
                SimulatorLightController::inchesToCoords(col * 3) *
                    sin(3.14 / 3.0 * pole_index),
            SimulatorLightController::inchesToCoords(120 - row * 9),
            SimulatorLightController::inchesToCoords(90) *
                    sin(3.14 / 3.0 * pole_index) +
                SimulatorLightController::inchesToCoords(col * 3) *
                    cos(3.14 / 3.0 * pole_index));
        light_row.push_back(createLight(vector));
      }
      light_pole.push_back(light_row);
    }
    poles.push_back(pole);
    lights.push_back(light_pole);
  }
}

void SimulatorLightController::WriteOutLights() {
  for (int pole_index = 0; pole_index < 6; pole_index++) {
    Pole *pole = poles[pole_index];
    CRGB rgb = {255, 255, 255};
    const uint8_t grid_num_rows = pole->get_grid_lights().size();
    const uint8_t grid_num_cols = pole->get_grid_lights().front().size();

    for (unsigned long x = 0; x < grid_num_rows; x++) {
      for (unsigned long y = 0; y < grid_num_cols; y++) {
        lights[pole_index][x][y]->setSpecularColour(
            pole->get_grid_lights()[x][y].r / 255.0,
            pole->get_grid_lights()[x][y].g / 255.0,
            pole->get_grid_lights()[x][y].b / 255.0);
        lights[pole_index][x][y]->setDiffuseColour(
            pole->get_grid_lights()[x][y].r / 255.0,
            pole->get_grid_lights()[x][y].g / 255.0,
            pole->get_grid_lights()[x][y].b / 255.0);
      }
    }
  }
}

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
