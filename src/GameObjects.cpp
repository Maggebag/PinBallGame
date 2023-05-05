
#include "GameObjects.hpp"
#include "threepp/threepp.hpp"
#include "threepp/extras/physics/BulletPhysics.hpp"

using namespace threepp;

std::shared_ptr<Mesh>utils::createCylinder(float radius, float height)
{
    const auto cylinderGeometry = CylinderGeometry::create(radius,radius,height);
    const auto cylinderMaterial = MeshBasicMaterial::create();
    cylinderMaterial->color = Color::red;
    auto cylinderMesh = Mesh::create(cylinderGeometry,cylinderMaterial);

    return cylinderMesh;
}

std::shared_ptr<Mesh>utils::createBox(float width, float length, float height)
{
    const auto boxGeometry = BoxGeometry::create(width,height, length);
    const auto boxMaterial = MeshBasicMaterial::create();
    boxMaterial->color = Color::burlywood;
    auto boxMesh = Mesh::create(boxGeometry,boxMaterial);

    return boxMesh;
}

std::shared_ptr<Mesh>utils::createFlipper(float direction, float ballSize) //-1 for left flipper and 1 for right flipper
{
    const auto flipperMaterial = MeshBasicMaterial::create();
    flipperMaterial->color = Color::palegreen;
    const auto flipperAxisMaterial = MeshBasicMaterial::create();
    flipperAxisMaterial->color = Color::red;

    const auto flipperGeometry = BoxGeometry::create(3*ballSize, 22, 20);
    auto flipperMesh = Mesh::create(flipperGeometry, flipperMaterial);

    const auto flipperTipGeometry = CylinderGeometry::create(20/2 , 20/2 , 22);
    flipperTipGeometry->translate(direction * -flipperGeometry->width/2,0,0);
    auto flipperTipMesh = Mesh::create(flipperTipGeometry, flipperMaterial);
    flipperMesh->add(flipperTipMesh);

    const auto flipperAxisGeometry = CylinderGeometry::create(20/2-2, 20/2-2, 27);
    flipperAxisGeometry->translate(direction * flipperGeometry->width / 3, 0, 0);
    auto flipperAxisMesh = Mesh::create(flipperAxisGeometry, flipperAxisMaterial);
    flipperMesh->add(flipperAxisMesh);

    return flipperMesh;
}

std::shared_ptr<Mesh>utils::createBall(float radius)
{
    const auto ballGeometry = SphereGeometry::create(radius,32,32);
    const auto ballMaterial = MeshPhongMaterial::create();
    ballMaterial->color.setHex(0XC0C0C0);
    auto ballMesh = Mesh::create(ballGeometry,ballMaterial);

    return ballMesh;
}
std::shared_ptr<Mesh>utils::createPlane(float width, float height)
{
    const auto planeGeometry = PlaneGeometry::create(width,height);
    planeGeometry->rotateX(math::DEG2RAD*-90);
    const auto planeMaterial = MeshBasicMaterial::create();
    planeMaterial->color = Color::beige;
    auto plane = Mesh::create(planeGeometry, planeMaterial);

    return plane;
}

