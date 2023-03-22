
#include "gameObjects.hpp"
#include "threepp/threepp.hpp"

using namespace threepp;

std::shared_ptr<Mesh>createCylinder(float size, float height){

    const auto cylinderGeometry = CylinderGeometry::create(size,size,height);
    const auto cylinderMaterial = MeshBasicMaterial::create();
    cylinderMaterial->color = Color::red;
    auto cylinderMesh = Mesh::create(cylinderGeometry,cylinderMaterial);

}

