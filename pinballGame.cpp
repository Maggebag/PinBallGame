
#include "threepp/threepp.hpp"
#include "threepp/extras/physics/BulletPhysics.hpp"
#include "gameScene.hpp"
#include "gameObjects.hpp"

using namespace threepp;

auto bouncyCylinder1 = createCylinder(5,10);

auto flipperRight = createFlipper(1);

auto flipperLeft = createFlipper(-1);
