#ifndef PINBALLGAME_GAMEOBJECTS_HPP
#define PINBALLGAME_GAMEOBJECTS_HPP

#include <threepp/objects/Mesh.hpp>
#include <threepp/extras/physics/BulletPhysics.hpp>
#include <threepp/math/MathUtils.hpp>
#include "utils.hpp"

class FlipperObject {
public:
    std::shared_ptr<threepp::Mesh> flipper;
    std::unique_ptr<btHingeConstraint> btFlipper;

    void setFlipperDirection(float direction) {
        flipperDir = direction;
    }

    void addFlipper(float ballSize, threepp::BulletPhysics &bullet, threepp::Object3D &scene) {
        flipper = createFlipper(flipperDir, ballSize);
        flipper->position.set(position.x, position.y, position.z);
        scene.add(flipper);
        bullet.addMesh(*flipper, 100, true);

        auto bulletFlipper = bullet.get(*flipper);
        bulletFlipper->body->setRestitution(0.2);

        btFlipper = std::make_unique<btHingeConstraint>(*bulletFlipper->body, btVector3(flipperDir * ((3.5*ballSize)/2.5), 0, 0),
                                                        btVector3(0, 1, 0));
        btFlipper->enableAngularMotor(true, 0, 9999999999.f);
        if (flipperDir > 0) {
            btFlipper->setLimit(-0.4, 0.5);
        } else if (flipperDir < 0) {
            btFlipper->setLimit(-0.5, 0.5);
        }
        bullet.addConstraint(btFlipper.get(), true);
    }

    void setPosition(float x, float y, float z) {
        position.x = x;
        position.y = y;
        position.z = z;
    }

    void activateFlipper() const {
        btFlipper->setMotorTargetVelocity(-9999999999.f * flipperDir);
    }

    void deactivateFlipper() const {
        btFlipper->setMotorTargetVelocity(9999999999.f * flipperDir);
    }

private:
    threepp::Vector3 position;
    float flipperDir = 0;

    std::shared_ptr<threepp::Mesh>
    createFlipper(float direction, float ballSize) { //-1 for left flipper and 1 for right flipper
        const auto flipperMaterial = threepp::MeshPhongMaterial::create();
        flipperMaterial->color = threepp::Color::palegreen;
        const auto flipperAxisMaterial = threepp::MeshPhongMaterial::create();
        flipperAxisMaterial->color = threepp::Color::red;

        const auto flipperGeometry = threepp::BoxGeometry::create(3.5f * ballSize, 22, 20);
        auto flipperMesh = threepp::Mesh::create(flipperGeometry, flipperMaterial);

        const auto flipperAxisGeometry = threepp::CylinderGeometry::create(flipperGeometry->height / 2 - 2, flipperGeometry->height / 2 - 2, 27);
        flipperAxisGeometry->translate(direction * flipperGeometry->width / 2.5, 0, 0);
        auto flipperAxisMesh = threepp::Mesh::create(flipperAxisGeometry, flipperAxisMaterial);
        flipperMesh->add(flipperAxisMesh);
        flipperMesh->castShadow = true;

        return flipperMesh;
    }
};


class PlungerObject {

public:

    float plungerTravelLength;
    std::shared_ptr<threepp::Mesh> baseBox;
    std::shared_ptr<threepp::Mesh> plungerBox;

    std::shared_ptr<threepp::Mesh> insideShield;

    std::unique_ptr<btSliderConstraint> btPlunger;

    void setPlungerTravelLength(float length) {
        plungerTravelLength = length;
    }

    void createPlunger(float ballSize){
        baseBox = utils::createBox(1.5f * ballSize, 20, ballSize, threepp::Color::gray);
        plungerBox = utils::createBox(1.5f * ballSize, 20, ballSize, threepp::Color::gray);

        baseBox->position.set(position.x, position.y, position.z);
        plungerBox->position.set(position.x, position.y, position.z - plungerTravelLength);

    }

    void addPlunger(threepp::BulletPhysics &bullet, threepp::Object3D &scene) {
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

    void setPosition(float x, float y, float z) {
        position.x = x;
        position.y = y;
        position.z = z;
    }

    void PlungerSetUpperLim(float limit) const {
        btPlunger->setUpperLinLimit(limit);
    }

    void releasePlunger() const {
        btPlunger->setTargetLinMotorVelocity(-1000000);
    }

    void resetPlunger() const {
        btPlunger->setTargetLinMotorVelocity(1000000);

    }

    void createInsideShield(float gameHeight, float borderHeight, float ballSize, threepp::BulletPhysics &bullet, threepp::Object3D &scene){
        insideShield = utils::createBox(20, gameHeight/4 * 3 , borderHeight, threepp::Color::burlywood);
        insideShield->position.set(position.x - 1.5*ballSize/2 -10,borderHeight/2,gameHeight/4/2);
        scene.add(insideShield);
        bullet.addMesh(*insideShield);
        bullet.get(*insideShield)->body->setRestitution(1);
    }

private:
    threepp::Vector3 position;
};

class BallGuidesObject{

public:
    std::shared_ptr<threepp::Mesh> BallGuideLeft;
    std::shared_ptr<threepp::Mesh> BallGuideLeft2;
    std::shared_ptr<threepp::Mesh> BallGuideRight;
    std::shared_ptr<threepp::Mesh> BallGuideRight2;

    float BallSize;

    void createGuides(float ballSize){
        BallSize = ballSize;
        BallGuideLeft = utils::createBox(4*ballSize-5,22,20, color_);
        BallGuideLeft2= utils::createBox(22,4*ballSize,20, color_);
        BallGuideRight = utils::createBox(4*ballSize-5,22,20, color_);
        BallGuideRight2= utils::createBox(22,4*ballSize,20, color_);
    }

    void getFlipperPos(threepp::Vector3 pos){
        FlipperLeftPos_.set(-pos.x,pos.y,pos.z);
        FlipperRightPos_.set(pos.x,pos.y,pos.z);
    }

    void addBallGuides(threepp::BulletPhysics &bullet, threepp::Object3D &scene) const{

        BallGuideLeft->rotateY(-threepp::math::PI/6);
        BallGuideLeft->position.set(FlipperLeftPos_.x-std::cos(threepp::math::PI/6)*4*BallSize,FlipperLeftPos_.y,FlipperLeftPos_.z-std::sin(threepp::math::PI/6)*4*BallSize+22);
        BallGuideLeft2->position.set(FlipperLeftPos_.x-std::cos(threepp::math::PI/6)*4*BallSize-(std::cos(threepp::math::PI/6)*4*BallSize)/2, FlipperLeftPos_.y, FlipperLeftPos_.z-4*BallSize);

        BallGuideRight->rotateY(threepp::math::PI/6);
        BallGuideRight->position.set(FlipperRightPos_.x+std::cos(threepp::math::PI/6)*4*BallSize,FlipperRightPos_.y,FlipperRightPos_.z-std::sin(threepp::math::PI/6)*4*BallSize+22);
        BallGuideRight2->position.set(FlipperRightPos_.x+std::cos(threepp::math::PI/6)*4*BallSize+(std::cos(threepp::math::PI/6)*4*BallSize)/2, FlipperRightPos_.y, FlipperRightPos_.z-4*BallSize);

        scene.add(BallGuideLeft);
        scene.add(BallGuideLeft2);

        scene.add(BallGuideRight);
        scene.add(BallGuideRight2);

        bullet.addMesh(*BallGuideLeft);
        bullet.addMesh(*BallGuideLeft2);
        bullet.addMesh(*BallGuideRight);
        bullet.addMesh(*BallGuideRight2);
    }

private:
    threepp::Color::ColorName color_ = threepp::Color::blueviolet;
    threepp::Vector3 FlipperLeftPos_;
    threepp::Vector3 FlipperRightPos_;
};



#endif //PINBALLGAME_GAMEOBJECTS_HPP
