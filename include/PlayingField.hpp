

#ifndef PINBALLGAME_PLAYINGFIELD_HPP
#define PINBALLGAME_PLAYINGFIELD_HPP

#include <threepp/objects/Mesh.hpp>
#include <threepp/core/Object3D.hpp>
#include <threepp/extras/physics/BulletPhysics.hpp>
#include "utils.hpp"
#include "GameObjects.hpp"


struct Parameters {
    //One unit equals 1mm
    const float BallSize = 27;
    const float BorderHeight = BallSize + 5;
    const float BorderWidth = 50;
    const float HalfBorderWidth = BorderWidth / 2;
    const float Height = 980;
    const float Width = 520;
};

class PlayingField {
public:

    std::shared_ptr<threepp::Mesh> PinBall;

    threepp::Vector3 ballResetPos;

    FlipperObject FlipperLeft;
    FlipperObject FlipperRight;

    PlungerObject Plunger;

    PlayingField(threepp::Object3D &scene, threepp::BulletPhysics &bullet) {
        auto plane = createPlane(parameters_.Width, parameters_.Height);
        scene.add(plane);
        bullet.addMesh(*plane);
        bullet.get(*plane)->body->setRestitution(0.5);

        createBorder(scene, bullet);

        PinBall = createBall(parameters_.BallSize / 2);
        scene.add(PinBall);
        bullet.addMesh(*PinBall, 80.6, true);
        bullet.get(*PinBall)->body->setRestitution(0.75);

        ballResetPos.set(parameters_.Width / 2 - parameters_.HalfBorderWidth, 40, parameters_.Height / 2 - 220);

        FlipperLeft.setFlipperDirection(-1);
        FlipperLeft.setPosition(-2.5 * parameters_.BallSize, parameters_.BallSize / 2, parameters_.Height / 3);
        FlipperLeft.addFlipper(parameters_.BallSize, bullet, scene);

        FlipperRight.setFlipperDirection(1);
        FlipperRight.setPosition(2.5 * parameters_.BallSize, parameters_.BallSize / 2, parameters_.Height / 3);
        FlipperRight.addFlipper(parameters_.BallSize, bullet, scene);

        Plunger.setPlungerTravelLength(120.0);
        Plunger.setPosition(parameters_.Width / 2 - parameters_.HalfBorderWidth, 12, parameters_.Height / 2 - 20);
        Plunger.addPlunger(parameters_.BallSize, bullet, scene);
    }

private:
    Parameters parameters_;

    std::shared_ptr<threepp::Mesh> RightWall;
    std::shared_ptr<threepp::Mesh> LeftWall;
    std::shared_ptr<threepp::Mesh> TopWall;
    std::shared_ptr<threepp::Mesh> BottomWall;

    void createBorder(threepp::Object3D &scene, threepp::BulletPhysics &bullet) {
        RightWall = utils::createBox(parameters_.BorderWidth, parameters_.Height, parameters_.BorderHeight, threepp::Color::burlywood);
        RightWall->position.set(parameters_.Width / 2 + parameters_.HalfBorderWidth, parameters_.BorderHeight / 2, 0);

        LeftWall = utils::createBox(parameters_.BorderWidth, parameters_.Height, parameters_.BorderHeight, threepp::Color::burlywood);
        LeftWall->position.set(-(parameters_.Width / 2 + parameters_.HalfBorderWidth), parameters_.BorderHeight / 2, 0);

        TopWall = utils::createBox(parameters_.Width + parameters_.BorderWidth * 2, parameters_.BorderWidth,
                                   parameters_.BorderHeight, threepp::Color::burlywood);
        TopWall->position.set(0, parameters_.BorderHeight / 2, -(parameters_.Height / 2 + parameters_.HalfBorderWidth));

        BottomWall = utils::createBox(parameters_.Width + parameters_.BorderWidth * 2, parameters_.BorderWidth,
                                      parameters_.BorderHeight, threepp::Color::burlywood);
        BottomWall->position.set(0, parameters_.BorderHeight / 2, parameters_.Height / 2 + parameters_.HalfBorderWidth);

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

    std::shared_ptr<threepp::Mesh> createPlane(float width, float height) {
        const auto planeGeometry = threepp::PlaneGeometry::create(width, height);
        planeGeometry->rotateX(threepp::math::DEG2RAD * -90);
        const auto planeMaterial = threepp::MeshBasicMaterial::create();
        planeMaterial->color = threepp::Color::beige;
        auto plane = threepp::Mesh::create(planeGeometry, planeMaterial);

        return plane;
    }

    std::shared_ptr<threepp::Mesh> createBall(float radius) {
        const auto ballGeometry = threepp::SphereGeometry::create(radius, 32, 32);
        const auto ballMaterial = threepp::MeshPhongMaterial::create();
        ballMaterial->color.setHex(0XC0C0C0);
        auto ballMesh = threepp::Mesh::create(ballGeometry, ballMaterial);

        return ballMesh;
    }
};


#endif //PINBALLGAME_PLAYINGFIELD_HPP
