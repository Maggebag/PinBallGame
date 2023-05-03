#ifndef PINBALLGAME_GAMEOBJECTS_HPP
#define PINBALLGAME_GAMEOBJECTS_HPP

#include "threepp/threepp.hpp"

using namespace threepp;

namespace utils {
    std::shared_ptr<Mesh> createCylinder(float radius, float height);

    std::shared_ptr<Mesh> createBox(float width, float length, float height);

    std::shared_ptr<Mesh> createFlipper(float direction, float ballSize);

    std::shared_ptr<Mesh> createBall(float radius);

    std::shared_ptr<Mesh> createPlane(float width, float height);

}
#endif //PINBALLGAME_GAMEOBJECTS_HPP
