
#ifndef PINBALLGAME_POPULATEFIELD_HPP
#define PINBALLGAME_POPULATEFIELD_HPP

#include <memory>
#include <threepp/objects/Mesh.hpp>
#include <threepp/extras/physics/BulletPhysics.hpp>
#include <threepp/materials/MeshPhongMaterial.hpp>

#include "utils.hpp"

class bouncyCylindersObject {
public:

    std::shared_ptr<threepp::Mesh> CylinderTop;
    std::shared_ptr<threepp::Mesh> CylinderLeft;
    std::shared_ptr<threepp::Mesh> CylinderRight;


    void createMeshes(float radius, float height, threepp::Color::ColorName color) {
        radius_ = radius;
        CylinderTop = utils::createCylinder(radius, height, color);
        CylinderLeft = utils::createCylinder(radius, height, color);
        CylinderRight = utils::createCylinder(radius, height, color);
    }

    void setPosition(threepp::Vector3 pos) {
        CylinderTop->position.set(pos.x, pos.y, -pos.z + radius_);
        CylinderLeft->position.set(-pos.x - radius_ * 4, pos.y, -pos.z + 3 * radius_);
        CylinderRight->position.set(pos.x + radius_ * 4, pos.y, -pos.z + 3 * radius_);
    }

    void addToScene(threepp::BulletPhysics &bullet, threepp::Object3D &scene, float restitution = 3) {
        scene.add(CylinderTop);
        scene.add(CylinderLeft);
        scene.add(CylinderRight);

        bullet.addMesh(*CylinderTop);
        bullet.addMesh(*CylinderLeft);
        bullet.addMesh(*CylinderRight);

        bullet.get(*CylinderTop)->body->setRestitution(restitution);
        bullet.get(*CylinderLeft)->body->setRestitution(restitution);
        bullet.get(*CylinderRight)->body->setRestitution(restitution);
    }

private:
    float radius_;
};

#endif //PINBALLGAME_POPULATEFIELD_HPP
