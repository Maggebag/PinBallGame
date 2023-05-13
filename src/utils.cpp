
#include <threepp/objects/Mesh.hpp>
#include <threepp/geometries/geometries.hpp>
#include <threepp/materials/materials.hpp>
#include <threepp/lights/LightShadow.hpp>
#include <threepp/loaders/TextureLoader.hpp>
#include <threepp/lights/SpotLight.hpp>
#include <threepp/math/Color.hpp>

#include "utils.hpp"

std::shared_ptr<threepp::Mesh> utils::createCylinder(float radius, float height, threepp::Color::ColorName Color) {
    const auto cylinderGeometry = threepp::CylinderGeometry::create(radius, radius, height);
    const auto cylinderMaterial = threepp::MeshPhongMaterial::create();
    cylinderMaterial->color = Color;
    auto cylinderMesh = threepp::Mesh::create(cylinderGeometry, cylinderMaterial);
    cylinderMesh->castShadow = true;

    return cylinderMesh;
}

std::shared_ptr<threepp::Mesh> utils::createBox(float width, float length, float height, threepp::Color::ColorName Color) {
    const auto boxGeometry = threepp::BoxGeometry::create(width, height, length);
    const auto boxMaterial = threepp::MeshPhongMaterial::create();
    boxMaterial->color = Color;
    auto boxMesh = threepp::Mesh::create(boxGeometry, boxMaterial);
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

std::shared_ptr<threepp::Mesh> utils::createBall(float radius, threepp::TextureLoader &tl) {
    const auto ballGeometry = threepp::SphereGeometry::create(radius, 32, 32);
    const auto ballMaterial = threepp::MeshStandardMaterial::create();
    ballMaterial->map = tl.load("bin/data/textures/Metal007_1K_Color.jpg");
    ballMaterial->roughnessMap = tl.load("bin/data/textures/Metal007_1K_Roughness.jpg");
    ballMaterial->metalnessMap = tl.load("bin/data/textures/Metal007_1K_Metalness.jpg");
    ballMaterial->normalMap = tl.load("bin/data/textures/Metal007_1K_NormalGL.jpg");
    ballMaterial->metalness = 0.2f;
    ballMaterial->color = threepp::Color::silver;

    auto ballMesh = threepp::Mesh::create(ballGeometry, ballMaterial);
    ballMesh->castShadow = true;
    ballMesh->receiveShadow = true;

    return ballMesh;
}

std::shared_ptr<threepp::Mesh> utils::createBall(float radius) {
    const auto ballGeometry = threepp::SphereGeometry::create(radius, 32, 32);
    const auto ballMaterial = threepp::MeshPhongMaterial::create();
    ballMaterial->color = threepp::Color::silver;

    auto ballMesh = threepp::Mesh::create(ballGeometry, ballMaterial);
    ballMesh->castShadow = true;
    ballMesh->receiveShadow = true;

    return ballMesh;
}

std::shared_ptr<threepp::SpotLight> utils::createLight(threepp::Vector3 position) {
    auto light = threepp::SpotLight::create(threepp::Color::whitesmoke);
    light->castShadow = true;
    light->distance = 10000;
    light->intensity = 0.8f;
    light->angle = threepp::math::degToRad(60);
    light->position.set(position.x, position.y, position.z);
    light->shadow->mapSize.set(4096, 4096);

    return light;
}
