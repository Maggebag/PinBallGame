
#ifndef PINBALLGAME_UTILS_HPP
#define PINBALLGAME_UTILS_HPP

#include <threepp/objects/Mesh.hpp>

namespace utils {
    std::shared_ptr<threepp::Mesh> createCylinder(float radius, float height, threepp::Color::ColorName Color);

    std::shared_ptr<threepp::Mesh> createBox(float width, float length, float height, threepp::Color::ColorName Color);
}

#endif //PINBALLGAME_UTILS_HPP
