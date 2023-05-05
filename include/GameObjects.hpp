#ifndef PINBALLGAME_GAMEOBJECTS_HPP
#define PINBALLGAME_GAMEOBJECTS_HPP

#include "threepp/objects/Mesh.hpp"
#include "threepp/extras/physics/BulletPhysics.hpp"

std::shared_ptr<threepp::Mesh> createCylinder(float radius, float height);

std::shared_ptr<threepp::Mesh> createBox(float width, float length, float height);

std::shared_ptr<threepp::Mesh> createFlipper(float direction, float ballSize);

std::shared_ptr<threepp::Mesh> createBall(float radius);

std::shared_ptr<threepp::Mesh> createPlane(float width, float height);

btHingeConstraint
createFlipperConstraint(std::shared_ptr<threepp::Mesh> Flipper, float direction, float ballSize, threepp::BulletPhysics &bullet) {

    bullet.addMesh(*Flipper, 100, true);

    auto btFlipper = bullet.get(*Flipper);
    btFlipper->body->setRestitution(0.2);
    btHingeConstraint flipperConstraint(*btFlipper->body, btVector3(ballSize, 0, 0), btVector3(0, 1, 0));
    flipperConstraint.enableAngularMotor(true, 0, 100000000000);

    if(direction>0){
        flipperConstraint.setLimit(-0.4, 0.5);
    }
    else if(direction<0) {
        flipperConstraint.setLimit(-0.5,0.5);
    }
    return flipperConstraint;
};

btSliderConstraint
createPlunger(std::shared_ptr<threepp::Mesh> baseBox, std::shared_ptr<threepp::Mesh> plungerBox, float plungerTravelLength, threepp::BulletPhysics &bullet) {

    bullet.addMesh(*baseBox);
    bullet.addMesh(*plungerBox, 10, true);

    auto btBaseBox = bullet.get(*baseBox);
    auto btPlungerBox = bullet.get(*plungerBox);

    btTransform localA;
    btTransform localB;

    localA.setIdentity();
    localB.setIdentity();
    localA.getBasis().setEulerZYX(0, math::PI / 2, 0);
    localA.setOrigin(btVector3(0.0, 0.0, plungerTravelLength));
    localB.getBasis().setEulerZYX(0, math::PI / 2, 0);
    localB.setOrigin(btVector3(0.0, 0.0, math::TWO_PI));

    btSliderConstraint plungerConstraint(*btPlungerBox->body, *btBaseBox->body, localA, localB, true);
    plungerConstraint.setLowerLinLimit(0);
    plungerConstraint.setLowerAngLimit(0);
    plungerConstraint.setUpperAngLimit(0);
    plungerConstraint.setPoweredLinMotor(true);
    plungerConstraint.setMaxLinMotorForce(100000);
    return plungerConstraint;
    //bullet.addConstraint(&plungerConstraint, true);

};
class FlipperObject {
public:
    float flipperDir;
    btHingeConstraint btFlipper;
    std::shared_ptr<threepp::Mesh> flipper;

    void setFlipperDirection(float direction) {
        flipperDir = direction;
    }

    void addFlipper(float ballSize, threepp::BulletPhysics &bullet, threepp::Object3D &scene) {
        flipper = createFlipper(flipperDir, ballSize);
        scene.add(flipper);
        btFlipper = createFlipperConstraint(flipper, flipperDir, ballSize, bullet);
        bullet.addConstraint(&btFlipper, true);
    }

    void setPosition(float x, float y, float z) const{
        flipper->position.set(x,y,z);
    }

    void activateFlipper() {
        btFlipper.setMotorTargetVelocity(-1000000000 * flipperDir);
    }

    void deactivateFlipper() {
        btFlipper.setMotorTargetVelocity(1000000000 * flipperDir);
    }

};

class Plunger {

public:

    float plungerTravelLength;
    std::shared_ptr<threepp::Mesh> baseBox;
    std::shared_ptr<threepp::Mesh> plungerBox;

    btSliderConstraint btPlunger;

    void setPlungerTravelLength(float length){
        plungerTravelLength = length;
    }

    void addPlunger(float ballSize, threepp::BulletPhysics &bullet, threepp::Object3D &scene){
        baseBox = createBox(1.5*ballSize,20,ballSize);
        plungerBox = createBox(1.5*ballSize,20,ballSize);
        scene.add(baseBox);
        scene.add(plungerBox);
        auto yes = createPlunger(baseBox, plungerBox, plungerTravelLength,bullet);
        yes = btPlunger;
        bullet.addConstraint(&btPlunger, true);
    }

    void setPosition(float x, float y, float z) const{
        baseBox->position.set(x,y,z+plungerTravelLength);
        plungerBox->position.set(x,y,z);
    }

};

#endif //PINBALLGAME_GAMEOBJECTS_HPP
