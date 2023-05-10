
#include <threepp/objects/Mesh.hpp>
#include <threepp/geometries/geometries.hpp>
#include <threepp/materials/materials.hpp>
#include <threepp/lights/LightShadow.hpp>
#include <threepp/loaders/TextureLoader.hpp>
#include <threepp/lights/SpotLight.hpp>
#include <threepp/math/Color.hpp>

#include "utils.hpp"

using namespace threepp;

std::shared_ptr<Mesh> utils::createCylinder(float radius, float height, threepp::Color::ColorName Color) {
    const auto cylinderGeometry = CylinderGeometry::create(radius, radius, height);
    const auto cylinderMaterial = MeshPhongMaterial::create();
    cylinderMaterial->color = Color;
    auto cylinderMesh = Mesh::create(cylinderGeometry, cylinderMaterial);

    return cylinderMesh;
}

std::shared_ptr<Mesh> utils::createBox(float width, float length, float height, Color::ColorName Color) {
    const auto boxGeometry = BoxGeometry::create(width, height, length);
    const auto boxMaterial = MeshPhongMaterial::create();
    boxMaterial->color = Color;
    auto boxMesh = Mesh::create(boxGeometry, boxMaterial);
    boxMesh->castShadow = true;

    return boxMesh;
}

std::shared_ptr<threepp::Mesh> utils::createPlane(float width, float height, threepp::Color::ColorName Color) {
    const auto planeGeometry = threepp::PlaneGeometry::create(width, height);
    planeGeometry->rotateX(threepp::math::DEG2RAD * -90);
    const auto planeMaterial = threepp::MeshPhongMaterial::create();
    planeMaterial->color = Color;
    auto plane = threepp::Mesh::create(planeGeometry, planeMaterial);
    plane->receiveShadow = true;

    return plane;
}

std::shared_ptr<threepp::Mesh> utils::createBall(float radius, threepp::TextureLoader& tl) {
    const auto ballGeometry = threepp::SphereGeometry::create(radius, 32, 32);
    const auto ballMaterial = threepp::MeshStandardMaterial::create();
    ballMaterial->map = tl.load("bin/data/textures/Metal007_1K_Color.jpg");
    ballMaterial->roughnessMap = tl.load ("bin/data/textures/Metal007_1K_Roughness.jpg");
    ballMaterial->metalnessMap = tl.load ("bin/data/textures/Metal007_1K_Metalness.jpg");
    ballMaterial->normalMap = tl.load("bin/data/textures/Metal007_1K_NormalGL.jpg");
    ballMaterial->metalness = 0.2f;
    ballMaterial->color = threepp::Color::silver;

    auto ballMesh = threepp::Mesh::create(ballGeometry, ballMaterial);
    ballMesh->castShadow = true;

    return ballMesh;
}

std::shared_ptr<threepp::SpotLight> utils::createLight(threepp::Vector3 position) {
    auto light = SpotLight::create(threepp::Color::whitesmoke);
    light->castShadow = true;
    light->distance = 10000;
    light->intensity = 0.8f;
    light->angle = math::degToRad(60);
    light->position.set(position.x,position.y,position.z);
    light->shadow->mapSize.set(4096,4096);

    return light;
}
