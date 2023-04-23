#ifndef PINBALLGAME_GAMEOBJECTS_HPP
#define PINBALLGAME_GAMEOBJECTS_HPP

#include "threepp/threepp.hpp"

using namespace threepp;

std::shared_ptr<Mesh>createCylinder(float radius, float height, float red, float green, float blue);

std::shared_ptr<Mesh>createBox(float width, float length, float height, float red, float green, float blue);

std::shared_ptr<Mesh>createFlipper(float direction);

std::shared_ptr<Mesh>createBall(float radius);

std::shared_ptr<Mesh>createPlane(float width, float height);

#endif //PINBALLGAME_GAMEOBJECTS_HPP
