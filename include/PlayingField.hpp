
#ifndef PINBALLGAME_PLAYINGFIELD_HPP
#define PINBALLGAME_PLAYINGFIELD_HPP

#include <threepp/objects/Mesh.hpp>
#include <threepp/core/Object3D.hpp>
#include <threepp/extras/physics/BulletPhysics.hpp>

#include "utils.hpp"
#include "GameObjects/GameObjects.hpp"

struct Parameters {
    //One unit equals 1mm
    const float BallSize = 27;
    const float BorderHeight = BallSize + 5;
    const float BorderWidth = 50;
    const float HalfBorderWidth = BorderWidth / 2;
    const float Height = 980;
    const float Width = 520;
    const float PlungerWidth = 20.f + 1.5f*BallSize;
};

class PlayingField {
public:

    std::shared_ptr<threepp::Mesh> PinBall;

    threepp::Vector3 ballResetPos;

    FlipperObject FlipperLeft;
    FlipperObject FlipperRight;

    BallGuidesObject BallGuides;

    PlungerObject Plunger;

    LightShieldObject shield;

    PlayingField(threepp::Object3D &scene, threepp::BulletPhysics &bullet) {

        ballResetPos.set(param_.Width / 2 - param_.BallSize*0.75f + param_.PlungerWidth, param_.BallSize/2, param_.Height / 2 - 220);

        auto Plane = utils::createPlane(param_.Width + param_.PlungerWidth, param_.Height, threepp::Color::beige);
        Plane->position.setX(param_.PlungerWidth/2);
        scene.add(Plane);
        bullet.addMesh(*Plane);
        bullet.get(*Plane)->body->setRestitution(0.5f);

        createBorder();
        addBorder(scene, bullet);

        createBtmBallGuides(scene, bullet);

        createTopCurve(scene, bullet);

        threepp::TextureLoader tl;
        PinBall = utils::createBall(param_.BallSize / 2, tl);
        PinBall->position.set(ballResetPos.x,ballResetPos.y,ballResetPos.z);
        scene.add(PinBall);
        bullet.addMesh(*PinBall, 80.6f, true);
        bullet.get(*PinBall)->body->setRestitution(0.75f);

        flipperPos_.set(2.5f * param_.BallSize, param_.BallSize / 2, param_.Height / 3);

        FlipperLeft.setFlipperDirection(-1);
        FlipperLeft.createFlipper(param_.BallSize);
        FlipperLeft.setPosition(-flipperPos_.x, flipperPos_.y, flipperPos_.z);
        FlipperLeft.addFlipper(param_.BallSize, bullet, scene);

        FlipperRight.setFlipperDirection(1);
        FlipperRight.createFlipper(param_.BallSize);
        FlipperRight.setPosition(flipperPos_.x, flipperPos_.y, flipperPos_.z);
        FlipperRight.addFlipper(param_.BallSize, bullet, scene);

        BallGuides.createGuides(param_.BallSize);
        BallGuides.getFlipperPos(flipperPos_);
        BallGuides.addBallGuides(bullet, scene);

        Plunger.setPlungerTravelLength(120.0);
        Plunger.createPlunger(param_.BallSize);
        Plunger.setPosition(param_.Width / 2 - param_.BallSize*0.75f + param_.PlungerWidth, 14, param_.Height / 2 - 20);
        Plunger.addPlunger(bullet, scene);
        Plunger.createInsideShield(param_.Height, param_.BorderHeight, param_.BallSize);
        Plunger.addInsideShield(bullet, scene);

        shield.defineLightShieldDimensions(100,200,25,threepp::Color::yellow);
        shield.addToScene(scene);
    }

private:
    Parameters param_;

    std::shared_ptr<threepp::Mesh> RightWall_;
    std::shared_ptr<threepp::Mesh> LeftWall_;
    std::shared_ptr<threepp::Mesh> TopWall_;
    std::shared_ptr<threepp::Mesh> BottomWall_;

    threepp::Vector3 flipperPos_;

    void createBorder() {

        RightWall_ = utils::createBox(param_.BorderWidth, param_.Height, param_.BorderHeight,
                                      threepp::Color::burlywood);
        RightWall_->position.set(param_.Width / 2 + param_.HalfBorderWidth + param_.PlungerWidth,
                                 param_.BorderHeight / 2, 0);

        LeftWall_ = utils::createBox(param_.BorderWidth, param_.Height, param_.BorderHeight, threepp::Color::burlywood);
        LeftWall_->position.set(-(param_.Width / 2 + param_.HalfBorderWidth), param_.BorderHeight / 2, 0);

        TopWall_ = utils::createBox(param_.Width + param_.BorderWidth * 2 + param_.PlungerWidth, param_.BorderWidth,
                                    param_.BorderHeight, threepp::Color::burlywood);
        TopWall_->position.set(param_.PlungerWidth / 2, param_.BorderHeight / 2,
                               -(param_.Height / 2 + param_.HalfBorderWidth));

        BottomWall_ = utils::createBox(param_.Width + param_.BorderWidth * 2 + param_.PlungerWidth, param_.BorderWidth,
                                       param_.BorderHeight, threepp::Color::burlywood);
        BottomWall_->position.set(param_.PlungerWidth / 2, param_.BorderHeight / 2,
                                  param_.Height / 2 + param_.HalfBorderWidth);
    }

    void addBorder(threepp::Object3D &scene, threepp::BulletPhysics &bullet){
        scene.add(RightWall_);
        scene.add(LeftWall_);
        scene.add(TopWall_);
        scene.add(BottomWall_);

        bullet.addMesh(*RightWall_);
        bullet.addMesh(*LeftWall_);
        bullet.addMesh(*TopWall_);
        bullet.addMesh(*BottomWall_);

        bullet.get(*RightWall_)->body->setRestitution(1);
        bullet.get(*LeftWall_)->body->setRestitution(1);
        bullet.get(*TopWall_)->body->setRestitution(1);
        bullet.get(*BottomWall_)->body->setRestitution(1);
    }

    void createTopCurve(threepp::Object3D &scene, threepp::BulletPhysics &bullet) const{

        float curveRadius = (param_.Width+param_.PlungerWidth)/2;
        auto curve = std::make_shared<threepp::Path>();
        curve->arc(param_.PlungerWidth/2,-param_.Height/5,curveRadius,0,-threepp::math::PI,true);

        auto points = curve->getPoints(12);

        for (int i = 0; i < points.size()/2; ++i) {

            auto boxWidth = points[i].distanceTo(points[i + 1]);
            auto box1 = utils::createBox(boxWidth+10, 25, param_.BorderHeight, threepp::Color::burlywood);
            auto box2 = utils::createBox(boxWidth+10, 25, param_.BorderHeight, threepp::Color::burlywood);

            auto relativeAngle = std::acos((points[i].x - points[i + 1].x) / boxWidth);
            auto angle = threepp::math::PI + relativeAngle;

            threepp::Vector2 boxPos;
            boxPos.lerpVectors(points[i], points[i + 1], 0.5f);

            box1->position.set(-boxPos.x -12.5f*std::sin(relativeAngle) + param_.PlungerWidth , param_.BorderHeight/2, boxPos.y - 12.5f*std::cos(relativeAngle));
            box1->rotateY(angle);

            box2->position.set(boxPos.x +12.5f*std::sin(relativeAngle), param_.BorderHeight/2, boxPos.y -12.5f*std::cos(relativeAngle));
            box2->rotateY(-angle);

            scene.add(box1);
            bullet.addMesh(*box1);
            bullet.get(*box1)->body->setRestitution(0.5f);
            scene.add(box2);
            bullet.addMesh(*box2);
            bullet.get(*box2)->body->setRestitution(0.5f);
        }
    }

    void createBtmBallGuides(threepp::Object3D &scene, threepp::BulletPhysics &bullet) const{
        auto leftGuide = utils::createBox(10*param_.BallSize,20,param_.BorderHeight,threepp::Color::burlywood);
        auto leftGuideEnd = utils::createBox(20,60,param_.BorderHeight,threepp::Color::burlywood);
        auto rightGuide = utils::createBox(10*param_.BallSize,20,param_.BorderHeight,threepp::Color::burlywood);
        auto rightGuideEnd = utils::createBox(20,60,param_.BorderHeight,threepp::Color::burlywood);

        leftGuide->rotateY(-threepp::math::PI/6);
        leftGuide->position.set(-param_.Width/3.5f,param_.BorderHeight/2, param_.Height/2.5f);
        scene.add(leftGuide);
        bullet.addMesh(*leftGuide);

        leftGuideEnd->position.set(-1.3575f*param_.BallSize,param_.BorderHeight/2,param_.Height/2.0375f);
        scene.add(leftGuideEnd);
        bullet.addMesh(*leftGuideEnd);

        rightGuide->rotateY(threepp::math::PI/6);
        rightGuide->position.set(param_.Width/3.5f,param_.BorderHeight/2, param_.Height/2.5f);
        scene.add(rightGuide);
        bullet.addMesh(*rightGuide);

        rightGuideEnd->position.set(1.3575f*param_.BallSize,param_.BorderHeight/2,param_.Height/2.0375f);
        scene.add(rightGuideEnd);
        bullet.addMesh(*rightGuideEnd);
    }
};

#endif //PINBALLGAME_PLAYINGFIELD_HPP
