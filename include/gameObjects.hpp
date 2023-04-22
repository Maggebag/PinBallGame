#ifndef PINBALLGAME_GAMEOBJECTS_HPP
#define PINBALLGAME_GAMEOBJECTS_HPP

#include "threepp/threepp.hpp"

using namespace threepp;

std::shared_ptr<Mesh>createCylinder(float size, float height);

std::shared_ptr<Mesh>createFlipper(float direction);

std::shared_ptr<Mesh>createBall(float radius);

std::shared_ptr<Mesh>createPlane(float width, float height);

#endif //PINBALLGAME_GAMEOBJECTS_HPP
