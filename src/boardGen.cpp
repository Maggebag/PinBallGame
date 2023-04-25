
#include "threepp/threepp.hpp"
#include "GameObjects.hpp"
#include "bordGen.hpp"

using namespace threepp;

std::shared_ptr<Mesh> PlayingField::createBorder(float width, float height) {
    auto sideBorder = utils::createBox(width,height, 50,125,125,125);
    auto RightWall = sideBorder;
    auto LeftWall = sideBorder;
    RightWall->
    return std::shared_ptr<Mesh>();
}