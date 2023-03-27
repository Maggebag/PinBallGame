
#include "gameObjects.hpp"
#include "threepp/threepp.hpp"

using namespace threepp;

std::shared_ptr<Mesh>createCylinder(float size, float height){

    const auto cylinderGeometry = CylinderGeometry::create(size,size,height);
    const auto cylinderMaterial = MeshBasicMaterial::create();
    cylinderMaterial->color = Color::red;
    auto cylinderMesh = Mesh::create(cylinderGeometry,cylinderMaterial);
}

std::shared_ptr<Mesh>createFlipper(float direction) {
    const auto flipperGeometry = BoxGeometry::create(30, 5, 5);
    const auto flipperMaterial = MeshBasicMaterial::create();
    flipperMaterial->color = Color::palegreen;
    auto flipperMesh = Mesh::create(flipperGeometry, flipperMaterial);

    const auto flipperAxisGeometry = CylinderGeometry::create(2, 2, 6);
    const auto flipperAxisMaterial = MeshBasicMaterial::create();
    flipperAxisMaterial->color = Color::red;
    flipperAxisGeometry->translate(direction * flipperGeometry->width / 3, 0, 0);
    auto flipperAxisMesh = Mesh::create(flipperAxisGeometry, flipperAxisMaterial);
    flipperMesh->add(flipperAxisMesh);

    return flipperMesh;
}
