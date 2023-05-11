
#ifndef PINBALLGAME_PLUNGEROBJECT_HPP
#define PINBALLGAME_PLUNGEROBJECT_HPP

#include <memory>
#include <threepp/objects/Mesh.hpp>
#include <threepp/extras/physics/BulletPhysics.hpp>

#include "utils.hpp"

class PlungerObject {

public:

    float plungerTravelLength;
    std::shared_ptr<threepp::Mesh> baseBox;
    std::shared_ptr<threepp::Mesh> plungerBox;

    std::shared_ptr<threepp::Mesh> insideShield;

    std::unique_ptr<btSliderConstraint> btPlunger;

    void setPlungerTravelLength(float length){
        plungerTravelLength = length;
    }

    void createPlunger(float ballSize){
        baseBox = utils::createBox(1.5f * ballSize, 20, ballSize, threepp::Color::gray);
        plungerBox = utils::createBox(1.5f * ballSize, 20, ballSize, threepp::Color::gray);
    }

    void addPlunger(threepp::BulletPhysics &bullet, threepp::Object3D &scene){
        scene.add(baseBox);
        scene.add(plungerBox);

        bullet.addMesh(*baseBox, 0, true);
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

    void setPosition(float x, float y, float z){
        position.x = x;
        position.y = y;
        position.z = z;
        baseBox->position.set(position.x, position.y, position.z);
        plungerBox->position.set(position.x, position.y, position.z - plungerTravelLength);
    }

    void PlungerSetUpperLim(float limit) const{
        btPlunger->setUpperLinLimit(limit);
    }

    void releasePlunger() const{
        btPlunger->setTargetLinMotorVelocity(-1000000);
    }

    void resetPlunger() const{
        btPlunger->setTargetLinMotorVelocity(1000000);
    }

    void createInsideShield(float gameHeight, float borderHeight, float ballSize){
        insideShield = utils::createBox(20, gameHeight / 4 * 3, borderHeight, threepp::Color::burlywood);
        insideShield->position.set(position.x - 1.5 * ballSize / 2 - 10, borderHeight / 2, gameHeight / 4 / 2);
    }

    void addInsideShield(threepp::BulletPhysics &bullet, threepp::Object3D &scene) const{
        scene.add(insideShield);
        bullet.addMesh(*insideShield);
        bullet.get(*insideShield)->body->setRestitution(1);
    }

private:
    threepp::Vector3 position;
};


#endif //PINBALLGAME_PLUNGEROBJECT_HPP
