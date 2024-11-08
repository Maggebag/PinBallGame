
#ifndef PINBALLGAME_UTILS_HPP
#define PINBALLGAME_UTILS_HPP

#include <threepp/objects/Mesh.hpp>
#include <threepp/math/Vector3.hpp>
#include <threepp/loaders/TextureLoader.hpp>
#include <threepp/lights/SpotLight.hpp>
#include <threepp/math/Color.hpp>

namespace utils {

    std::shared_ptr<threepp::Mesh> createCylinder(float radius, float height, threepp::Color::ColorName Color);

    std::shared_ptr<threepp::Mesh> createBox(float width, float length, float height, threepp::Color::ColorName Color);

    std::shared_ptr<threepp::Mesh> createPlane(float width, float height, threepp::Color::ColorName Color);

    std::shared_ptr<threepp::Mesh> createBall(float radius, threepp::TextureLoader &tl);

    std::shared_ptr<threepp::Mesh> createBall(float radius);

    std::shared_ptr<threepp::SpotLight> createLight(threepp::Vector3 position);

}

#endif //PINBALLGAME_UTILS_HPP
