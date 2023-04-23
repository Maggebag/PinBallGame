
#include "GameObjects.hpp"
#include "threepp/threepp.hpp"

using namespace threepp;

std::shared_ptr<Mesh>createCylinder(float radius, float height, float red, float green, float blue)
{
    const auto cylinderGeometry = CylinderGeometry::create(radius,radius,height);
    const auto cylinderMaterial = MeshBasicMaterial::create();
    cylinderMaterial->color.setRGB(red, green, blue);
    auto cylinderMesh = Mesh::create(cylinderGeometry,cylinderMaterial);

    return cylinderMesh;
}

std::shared_ptr<Mesh>createBox(float width, float length, float height, float red, float green, float blue)
{
    const auto boxGeometry = BoxGeometry::create(width,height, length);
    const auto boxMaterial = MeshBasicMaterial::create();
    boxMaterial->color.setRGB(red, green, blue);
    auto boxMesh = Mesh::create(boxGeometry,boxMaterial);

    return boxMesh;
}

std::shared_ptr<Mesh>createFlipper(float direction)
{
    const auto flipperGeometry = BoxGeometry::create(30, 5, 6);
    const auto flipperMaterial = MeshBasicMaterial::create();
    flipperMaterial->color = Color::palegreen;
    auto flipperMesh = Mesh::create(flipperGeometry, flipperMaterial);

    const auto flipperTipGeometry = CylinderGeometry::create(2.5 , 2.5 , 6);
    flipperTipGeometry->translate(direction * -flipperGeometry->width/2,0,0);
    auto flipendMesh = Mesh::create(flipperTipGeometry, flipperMaterial);
    flipperMesh->add(flipendMesh);

    const auto flipperAxisGeometry = CylinderGeometry::create(2, 2, 6);
    const auto flipperAxisMaterial = MeshBasicMaterial::create();
    flipperAxisMaterial->color = Color::red;
    flipperAxisGeometry->translate(direction * flipperGeometry->width / 3, 0, 0);
    auto flipperAxisMesh = Mesh::create(flipperAxisGeometry, flipperAxisMaterial);
    flipperMesh->add(flipperAxisMesh);

    return flipperMesh;
}

std::shared_ptr<Mesh>createBall(float radius)
{
    const auto ballGeometry = SphereGeometry::create(radius,32,32);
    const auto ballMaterial = MeshBasicMaterial::create();
    ballMaterial->color = Color::gray;
    auto ballMesh = Mesh::create(ballGeometry,ballMaterial);

    return ballMesh;
}
std::shared_ptr<Mesh>createPlane(float width, float height)
{
    const auto planeGeometry = PlaneGeometry::create(width,height);
    planeGeometry->rotateX(math::DEG2RAD*-90);
    const auto planeMaterial = MeshBasicMaterial::create();
    planeMaterial->color = Color::beige;
    auto plane = Mesh::create(planeGeometry, planeMaterial);

    return plane;
}