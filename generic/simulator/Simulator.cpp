#define SIMULATOR

#include "Simulator.hpp"
#include <OgreAxisAlignedBox.h>
#include <OgreBitesConfigDialog.h>
#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreMeshManager.h>
#include <OgrePlane.h>
#include <OgreRenderWindow.h>
#include <OgreSceneNode.h>
#include <OgreViewport.h>
#include <cmath>
#include <iostream>
#include "ColorCycleEffect.hpp"
#include "ColordanceTypes.hpp"
#include "RotateThreeEffect.hpp"
#include "SimulatorLightController.hpp"

Simulator::Simulator()
    : OgreBites::ApplicationContext("ColorDance Circle Simulator") {}

void Simulator::setup() {
  // Note: use this line if you need to change the rendering config
  // OgreBites::getNativeConfigDialog()->display();
  OgreBites::ApplicationContext::setup();

  // register for input events
  addInputListener(this);

  // get a pointer to the already created root
  Ogre::Root *root = getRoot();
  Ogre::SceneManager *scnMgr = root->createSceneManager();
  // register our scene with the RTSS
  Ogre::RTShader::ShaderGenerator *shadergen =
      Ogre::RTShader::ShaderGenerator::getSingletonPtr();
  shadergen->addSceneManager(scnMgr);

  Ogre::SceneNode *camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
  camNode->setPosition(0, SimulatorLightController::inchesToCoords(69),
                       SimulatorLightController::feetToCoords(15));
  camNode->lookAt(
      Ogre::Vector3(0, SimulatorLightController::feetToCoords(0), 0),
      Ogre::Node::TransformSpace::TS_WORLD);

  Ogre::Camera *cam = scnMgr->createCamera("cam1");
  cam->setNearClipDistance(5);
  camNode->attachObject(cam);

  Ogre::Viewport *vp = getRenderWindow()->addViewport(cam);
  vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));
  cam->setAspectRatio(Ogre::Real(vp->getActualWidth()) /
                      Ogre::Real(vp->getActualHeight()));

  Ogre::Plane wall(Ogre::Vector3::UNIT_Y, 0);
  Ogre::MeshManager::getSingleton().createPlane(
      "wall", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, wall,
      /* width */ SimulatorLightController::feetToCoords(30),
      /* height */ SimulatorLightController::feetToCoords(30), 20, 20, true, 1,
      5, 5, Ogre::Vector3::UNIT_Z);
  Ogre::Entity *wallEntity = scnMgr->createEntity("wall");
  wallEntity->setCastShadows(false);
  wallEntity->setMaterialName("Template/White");
  Ogre::SceneNode *wallNode =
      scnMgr->getRootSceneNode()->createChildSceneNode();
  wallNode->setPosition(0, 0, 0);
  wallNode->attachObject(wallEntity);

  for (int i = 0; i < 6; i++) {
    Ogre::Entity *pole_entity = scnMgr->createEntity("column.mesh");
    // With very many lights, turning on shadows for the poles makes this too
    // slow.
    pole_entity->setCastShadows(false);
    pole_entity->setMaterialName("Template/White");
    Ogre::AxisAlignedBox bounding_box = pole_entity->getBoundingBox();
    Ogre::Vector3 size = bounding_box.getSize();

    Ogre::SceneNode *pole_node =
        scnMgr->getRootSceneNode()->createChildSceneNode();
    pole_node->setPosition(
        SimulatorLightController::feetToCoords(7.5) * cos(3.14 / 3.0 * i), 0,
        SimulatorLightController::feetToCoords(7.5) * sin(3.14 / 3.0 * i));
    pole_node->attachObject(pole_entity);
    pole_node->setScale(
        Ogre::Vector3(SimulatorLightController::inchesToCoords(2) / size.x,
                      SimulatorLightController::feetToCoords(10) / size.y,
                      SimulatorLightController::inchesToCoords(2) / size.z));
  }

  Ogre::Entity *ninja_entity = scnMgr->createEntity("ninja.mesh");
  ninja_entity->setCastShadows(true);
  ninja_entity->setMaterialName("Template/OffBlack");
  ninja_node = scnMgr->getRootSceneNode()->createChildSceneNode();
  ninja_node->setPosition(SimulatorLightController::feetToCoords(2), 0,
                          SimulatorLightController::feetToCoords(5));
  ninja_node->attachObject(ninja_entity);

  scnMgr->setAmbientLight(Ogre::ColourValue(0, 0, 0));
  scnMgr->setShadowTechnique(
      Ogre::ShadowTechnique::SHADOWTYPE_STENCIL_ADDITIVE);

  lightController = new SimulatorLightController(scnMgr);
  // effect = new ColorCycleEffect(lightController->get_poles());
  effect = new RotateThreeEffect(lightController->get_poles());
}

bool Simulator::frameEnded(const Ogre::FrameEvent &evt) {
  /*ninja_node->setPosition(
      SimulatorLightController::feetToCoords(2) * sin(ninjaClock / 20.0), 0,
      SimulatorLightController::feetToCoords(2) * cos(ninjaClock / 20.0));*/

  effect->Run();
  lightController->WriteOutLights();

  ninjaClock++;

  return true;
}

bool Simulator::keyPressed(const OgreBites::KeyboardEvent &evt) {
  if (evt.keysym.sym == SDLK_ESCAPE) {
    getRoot()->queueEndRendering();
  }

  return true;
}

bool Simulator::keyReleased(const OgreBites::KeyboardEvent &evt) {
  return true;
}

int main(int argc, char **argv) {
  Simulator app;
  app.initApp();
  app.getRoot()->startRendering();
  app.closeApp();
  return 0;
}
