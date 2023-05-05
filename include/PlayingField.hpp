

#ifndef PINBALLGAME_PLAYINGFIELD_HPP
#define PINBALLGAME_PLAYINGFIELD_HPP

#include <threepp/objects/Mesh.hpp>
#include <threepp/core/Object3D.hpp>
#include <threepp/extras/physics/BulletPhysics.hpp>
#include "GameObjects.hpp"


struct Parameters {
    //One unit equals 1mm
    const float BallSize = 27;
    const float BorderHeight = BallSize + 5;
    const float BorderWidth = 50;
    const float HalfBorderWidth = BorderWidth /2;
    const float Height = 980;
    const float Width = 520;
};

class PlayingField {
public:

    std::shared_ptr<threepp::Mesh> PinBall;

    FlipperObject FlipperLeft;
    FlipperObject FlipperRight;

    PlungerObject Plunger;

    PlayingField(threepp::Object3D &scene, threepp::BulletPhysics &bullet) {
        auto plane = createPlane(parameters_.Width, parameters_.Height);
        scene.add(plane);
        bullet.addMesh(*plane);
        bullet.get(*plane)->body->setRestitution(0.5);

        createBorder(scene,bullet);

        PinBall = createBall(parameters_.BallSize / 2);
        scene.add(PinBall);
        bullet.addMesh(*PinBall, 80.6, true);

        FlipperLeft.setFlipperDirection(-1);
        FlipperLeft.setPosition(-2.5 * parameters_.BallSize, parameters_.BallSize / 2, parameters_.Height / 3);
        FlipperLeft.addFlipper(parameters_.BallSize, bullet, scene);

        FlipperRight.setFlipperDirection(1);
        FlipperRight.setPosition(2.5 * parameters_.BallSize, parameters_.BallSize / 2, parameters_.Height / 3);
        FlipperRight.addFlipper(parameters_.BallSize, bullet, scene);
    }

private:
    Parameters parameters_;

    std::shared_ptr<threepp::Mesh> RightWall;
    std::shared_ptr<threepp::Mesh> LeftWall;
    std::shared_ptr<threepp::Mesh> TopWall;
    std::shared_ptr<threepp::Mesh> BottomWall;

    void createBorder(threepp::Object3D &scene, threepp::BulletPhysics &bullet){
        RightWall = createBox(parameters_.BorderWidth, parameters_.Height, parameters_.BorderHeight);
        RightWall->position.set(parameters_.Width / 2 + parameters_.HalfBorderWidth, parameters_.BorderHeight / 2, 0);

        LeftWall = createBox(parameters_.BorderWidth, parameters_.Height, parameters_.BorderHeight);
        LeftWall->position.set(-(parameters_.Width / 2 + parameters_.HalfBorderWidth), parameters_.BorderHeight / 2, 0);

        TopWall = createBox(parameters_.Width + parameters_.BorderWidth * 2, parameters_.BorderWidth,
                                   parameters_.BorderHeight);
        TopWall->position.set(0, parameters_.BorderHeight / 2, -(parameters_.Height / 2 + parameters_.HalfBorderWidth));

        BottomWall = createBox(parameters_.Width + parameters_.BorderWidth * 2, parameters_.BorderWidth,
                                      parameters_.BorderHeight);
        BottomWall->position.set(0, parameters_.BorderHeight / 2, parameters_.Height / 2 + parameters_.HalfBorderWidth);

        scene.add(RightWall);
        scene.add(LeftWall);
        scene.add(TopWall);
        scene.add(BottomWall);

        bullet.addMesh(*RightWall);
        bullet.addMesh(*LeftWall);
        bullet.addMesh(*TopWall);
        bullet.addMesh(*BottomWall);

        bullet.get(*RightWall)->body->setRestitution(0.5);
        bullet.get(*LeftWall)->body->setRestitution(0.5);
        bullet.get(*TopWall)->body->setRestitution(0.5);
        bullet.get(*BottomWall)->body->setRestitution(0.5);
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
    std::shared_ptr<threepp::Mesh> createBox(float width, float length, float height) {
        const auto boxGeometry = threepp::BoxGeometry::create(width, height, length);
        const auto boxMaterial = threepp::MeshBasicMaterial::create();
        boxMaterial->color = threepp::Color::burlywood;
        auto boxMesh = threepp::Mesh::create(boxGeometry, boxMaterial);

        return boxMesh;
    }
};


#endif //PINBALLGAME_PLAYINGFIELD_HPP
