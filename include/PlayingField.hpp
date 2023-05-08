

#ifndef PINBALLGAME_PLAYINGFIELD_HPP
#define PINBALLGAME_PLAYINGFIELD_HPP

#include <threepp/objects/Mesh.hpp>
#include <threepp/core/Object3D.hpp>
#include <threepp/extras/physics/BulletPhysics.hpp>
#include "utils.hpp"
#include "GameObjects.hpp"
#include <iostream>


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

    PlayingField(threepp::Object3D &scene, threepp::BulletPhysics &bullet) {

        ballResetPos.set(param_.Width / 2 - param_.BallSize*0.75f + param_.PlungerWidth, param_.BallSize/2, param_.Height / 2 - 220);

        Plane = utils::createPlane(param_.Width + param_.PlungerWidth, param_.Height, threepp::Color::beige);
        Plane->position.setX(param_.PlungerWidth/2);
        scene.add(Plane);
        bullet.addMesh(*Plane);
        bullet.get(*Plane)->body->setRestitution(0.5f);

        createBorder(scene, bullet);

        createTopCurve(scene, bullet);

        threepp::TextureLoader tl;
        PinBall = utils::createBall(param_.BallSize / 2, tl);
        PinBall->position.set(ballResetPos.x,ballResetPos.y,ballResetPos.z);
        scene.add(PinBall);
        bullet.addMesh(*PinBall, 80.6f, true);
        bullet.get(*PinBall)->body->setRestitution(0.75f);

        flipperPos_.set(2.5f * param_.BallSize, param_.BallSize / 2, param_.Height / 3);

        FlipperLeft.setFlipperDirection(-1);
        FlipperLeft.setPosition(-flipperPos_.x, flipperPos_.y, flipperPos_.z);
        FlipperLeft.addFlipper(param_.BallSize, bullet, scene);

        FlipperRight.setFlipperDirection(1);
        FlipperRight.setPosition(flipperPos_.x, flipperPos_.y, flipperPos_.z);
        FlipperRight.addFlipper(param_.BallSize, bullet, scene);

        BallGuides.createGuides(param_.BallSize);
        BallGuides.getFlipperPos(flipperPos_);
        BallGuides.addBallGuides(bullet, scene);

        Plunger.setPlungerTravelLength(120.0);
        Plunger.setPosition(param_.Width / 2 - param_.BallSize*0.75f + param_.PlungerWidth, 14, param_.Height / 2 - 20);
        Plunger.createPlunger(param_.BallSize);
        Plunger.addPlunger(bullet, scene);

        Plunger.createInsideShield(param_.Height, param_.BorderHeight, param_.BallSize, bullet, scene);
    }

private:
    Parameters param_;

    std::shared_ptr<threepp::Mesh> Plane;
    std::shared_ptr<threepp::Mesh> RightWall;
    std::shared_ptr<threepp::Mesh> LeftWall;
    std::shared_ptr<threepp::Mesh> TopWall;
    std::shared_ptr<threepp::Mesh> BottomWall;

    threepp::Vector3 flipperPos_;

    void createBorder(threepp::Object3D &scene, threepp::BulletPhysics &bullet) {
        RightWall = utils::createBox(param_.BorderWidth, param_.Height, param_.BorderHeight, threepp::Color::burlywood);
        RightWall->position.set(param_.Width / 2 + param_.HalfBorderWidth + param_.PlungerWidth, param_.BorderHeight / 2, 0);

        LeftWall = utils::createBox(param_.BorderWidth, param_.Height, param_.BorderHeight, threepp::Color::burlywood);
        LeftWall->position.set(-(param_.Width / 2 + param_.HalfBorderWidth), param_.BorderHeight / 2, 0);

        TopWall = utils::createBox(param_.Width + param_.BorderWidth * 2 + param_.PlungerWidth, param_.BorderWidth,
                                   param_.BorderHeight, threepp::Color::burlywood);
        TopWall->position.set(param_.PlungerWidth/2, param_.BorderHeight / 2, -(param_.Height / 2 + param_.HalfBorderWidth));

        BottomWall = utils::createBox(param_.Width + param_.BorderWidth * 2 + param_.PlungerWidth, param_.BorderWidth,
                                      param_.BorderHeight, threepp::Color::burlywood);
        BottomWall->position.set(param_.PlungerWidth/2, param_.BorderHeight / 2, param_.Height / 2 + param_.HalfBorderWidth);

        scene.add(RightWall);
        scene.add(LeftWall);
        scene.add(TopWall);
        scene.add(BottomWall);

        bullet.addMesh(*RightWall);
        bullet.addMesh(*LeftWall);
        bullet.addMesh(*TopWall);
        bullet.addMesh(*BottomWall);

        bullet.get(*RightWall)->body->setRestitution(1);
        bullet.get(*LeftWall)->body->setRestitution(1);
        bullet.get(*TopWall)->body->setRestitution(1);
        bullet.get(*BottomWall)->body->setRestitution(1);
    }
    void createTopCurve(threepp::Object3D &scene, threepp::BulletPhysics &bullet){

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
};


#endif //PINBALLGAME_PLAYINGFIELD_HPP
