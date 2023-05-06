
#include <threepp/threepp.hpp>
#include "utils.hpp"

using namespace threepp;

std::shared_ptr<Mesh> utils::createCylinder(float radius, float height, threepp::Color::ColorName Color) {
    const auto cylinderGeometry = CylinderGeometry::create(radius, radius, height);
    const auto cylinderMaterial = MeshBasicMaterial::create();
    cylinderMaterial->color = Color;
    auto cylinderMesh = Mesh::create(cylinderGeometry, cylinderMaterial);

    return cylinderMesh;
}

std::shared_ptr<Mesh> utils::createBox(float width, float length, float height, Color::ColorName Color) {
    const auto boxGeometry = BoxGeometry::create(width, height, length);
    const auto boxMaterial = MeshBasicMaterial::create();
    boxMaterial->color = Color;
    auto boxMesh = Mesh::create(boxGeometry, boxMaterial);

    return boxMesh;
}
