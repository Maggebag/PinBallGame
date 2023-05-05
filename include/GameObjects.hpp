#ifndef PINBALLGAME_GAMEOBJECTS_HPP
#define PINBALLGAME_GAMEOBJECTS_HPP

#include "threepp/objects/Mesh.hpp"
#include "threepp/extras/physics/BulletPhysics.hpp"
#include "threepp/math/MathUtils.hpp"
#include <iostream>

class FlipperObject {
public:
    std::shared_ptr<threepp::Mesh> flipper;
    std::unique_ptr<btHingeConstraint> btFlipper;

    void setFlipperDirection(int direction) {
        flipperDir = direction;
    }

    void addFlipper(float ballSize, threepp::BulletPhysics &bullet, threepp::Object3D &scene) {
        flipper = createFlipper(flipperDir, ballSize);
        flipper->position.set(position.x,position.y,position.z);
        scene.add(flipper);
        bullet.addMesh(*flipper, 100, true);

        auto bulletFlipper = bullet.get(*flipper);
        bulletFlipper->body->setRestitution(0.2);

        btFlipper = std::make_unique<btHingeConstraint>(*bulletFlipper->body, btVector3(flipperDir*ballSize, 0, 0), btVector3(0, 1, 0));
        btFlipper->enableAngularMotor(true, 0, 9999999999);
        if(flipperDir>0){
            btFlipper->setLimit(-0.4, 0.5);
        }
        else if(flipperDir<0) {
            btFlipper->setLimit(-0.5,0.5);
        }
        bullet.addConstraint(btFlipper.get(), true);
    }

    void setPosition(float x, float y, float z) {
       position.x = x;
       position.y = y;
       position.z = z;
    }

    void activateFlipper() const {
        btFlipper->setMotorTargetVelocity(-9999999999 * flipperDir);
    }

    void deactivateFlipper() const {
        btFlipper->setMotorTargetVelocity(9999999999 * flipperDir);
    }

private:
    threepp::Vector3 position;
    int flipperDir = 0;
    std::shared_ptr<threepp::Mesh> createFlipper(float direction, float ballSize){ //-1 for left flipper and 1 for right flipper
        const auto flipperMaterial = threepp::MeshBasicMaterial::create();
        flipperMaterial->color = threepp::Color::palegreen;
        const auto flipperAxisMaterial = threepp::MeshBasicMaterial::create();
        flipperAxisMaterial->color = threepp::Color::red;

        const auto flipperGeometry = threepp::BoxGeometry::create(3 * ballSize, 22, 20);
        auto flipperMesh = threepp::Mesh::create(flipperGeometry, flipperMaterial);

        const auto flipperTipGeometry = threepp::CylinderGeometry::create(20 / 2, 20 / 2, 22);
        flipperTipGeometry->translate(direction * -flipperGeometry->width / 2, 0, 0);
        auto flipperTipMesh = threepp::Mesh::create(flipperTipGeometry, flipperMaterial);
        flipperMesh->add(flipperTipMesh);

        const auto flipperAxisGeometry = threepp::CylinderGeometry::create(20 / 2 - 2, 20 / 2 - 2, 27);
        flipperAxisGeometry->translate(direction * flipperGeometry->width / 3, 0, 0);
        auto flipperAxisMesh = threepp::Mesh::create(flipperAxisGeometry, flipperAxisMaterial);
        flipperMesh->add(flipperAxisMesh);

        return flipperMesh;
    }
};


class PlungerObject {

public:

    float plungerTravelLength;
    std::shared_ptr<threepp::Mesh> baseBox;
    std::shared_ptr<threepp::Mesh> plungerBox;

    std::unique_ptr<btSliderConstraint> btPlunger;

    void setPlungerTravelLength(float length) {
        plungerTravelLength = length;
    }

    void addPlunger(float ballSize, threepp::BulletPhysics &bullet, threepp::Object3D &scene) {
        baseBox = createBox(1.5 * ballSize, 20, ballSize);
        plungerBox = createBox(1.5 * ballSize, 20, ballSize);
        scene.add(baseBox);
        scene.add(plungerBox);

        bullet.addMesh(*baseBox);
        bullet.addMesh(*plungerBox, 10, true);

        auto btBaseBox = bullet.get(*baseBox);
        auto btPlungerBox = bullet.get(*plungerBox);

        btTransform localA;
        btTransform localB;

        localA.setIdentity();
        localB.setIdentity();
        localA.getBasis().setEulerZYX(0, threepp::math::PI / 2, 0);
        localA.setOrigin(btVector3(0.0, 0.0, plungerTravelLength));
        localB.getBasis().setEulerZYX(0, threepp::math::PI / 2, 0);
        localB.setOrigin(btVector3(0.0, 0.0, threepp::math::TWO_PI));

        btPlunger = std::make_unique<btSliderConstraint>(*btPlungerBox->body, *btBaseBox->body, localA, localB, true);

        btPlunger->setLowerLinLimit(0);
        btPlunger->setLowerAngLimit(0);
        btPlunger->setUpperAngLimit(0);
        btPlunger->setPoweredLinMotor(true);
        btPlunger->setMaxLinMotorForce(100000);

        bullet.addConstraint(btPlunger.get(), true);
    }

    void setPosition(float x, float y, float z) const {
        baseBox->position.set(x, y, z);
        plungerBox->position.set(x, y, z - plungerTravelLength);
    }

    void PlungerSetLowLim(float limit) const {
        btPlunger->setLowerLinLimit(limit);
    }

    void releasePlunger() const {
        btPlunger->setTargetLinMotorVelocity(-1000000);
    }

    void resetPlunger(float limit) const{
        btPlunger->setTargetLinMotorVelocity(1000000);
        btPlunger->setLowerLinLimit(limit);
    }

private:
    std::shared_ptr<threepp::Mesh> createBox(float width, float length, float height) {
        const auto boxGeometry = threepp::BoxGeometry::create(width, height, length);
        const auto boxMaterial = threepp::MeshBasicMaterial::create();
        boxMaterial->color = threepp::Color::burlywood;
        auto boxMesh = threepp::Mesh::create(boxGeometry, boxMaterial);

        return boxMesh;
    }
};

#endif //PINBALLGAME_GAMEOBJECTS_HPP
