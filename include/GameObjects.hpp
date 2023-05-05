#ifndef PINBALLGAME_GAMEOBJECTS_HPP
#define PINBALLGAME_GAMEOBJECTS_HPP

#include "threepp/objects/Mesh.hpp"
#include "threepp/extras/physics/BulletPhysics.hpp"
#include "threepp/math/MathUtils.hpp"

std::shared_ptr<threepp::Mesh> createCylinder(float radius, float height);

std::shared_ptr<threepp::Mesh> createBox(float width, float length, float height);

std::shared_ptr<threepp::Mesh> createFlipper(float direction, float ballSize);

std::shared_ptr<threepp::Mesh> createBall(float radius);

std::shared_ptr<threepp::Mesh> createPlane(float width, float height);

class FlipperObject {
public:
    float flipperDir;
    std::shared_ptr<btHingeConstraint> btFlipper;
    std::shared_ptr<threepp::Mesh> flipper;

    void setFlipperDirection(float direction) {
        flipperDir = direction;
    }

    void addFlipper(float ballSize, threepp::BulletPhysics &bullet, threepp::Object3D &scene) {
        flipper = createFlipper(flipperDir, ballSize);
        scene.add(flipper);
        bullet.addMesh(*flipper, 100, true);

        auto bulletFlipper = bullet.get(*flipper);
        bulletFlipper->body->setRestitution(0.2);

        btFlipper = std::make_shared<btHingeConstraint>(*bulletFlipper->body, btVector3(ballSize, 0, 0), btVector3(0, 1, 0));
        if(flipperDir>0){
            btFlipper->setLimit(-0.4, 0.5);
        }
        else if(flipperDir<0) {
            btFlipper->setLimit(-0.5,0.5);
        }
        bullet.addConstraint(btFlipper.get(), true);
    }

    void setPosition(float x, float y, float z) const{
        flipper->position.set(x,y,z);
    }

    void activateFlipper() const {
        btFlipper->setMotorTargetVelocity(-1000000000 * flipperDir);
    }

    void deactivateFlipper() const {
        btFlipper->setMotorTargetVelocity(1000000000 * flipperDir);
    }
};

class PlungerObject {

public:

    float plungerTravelLength;
    std::shared_ptr<threepp::Mesh> baseBox;
    std::shared_ptr<threepp::Mesh> plungerBox;

    std::shared_ptr<btSliderConstraint> btPlunger;

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

        btPlunger = std::make_shared<btSliderConstraint>(*btPlungerBox->body, *btBaseBox->body, localA, localB, true);

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
    float lowLim_ = 0;

};

#endif //PINBALLGAME_GAMEOBJECTS_HPP
