

#ifndef PINBALLGAME_PLAYINGFIELD_HPP
#define PINBALLGAME_PLAYINGFIELD_HPP

#include "threepp/threepp.hpp"
#include "GameObjects.hpp"

using namespace threepp;

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

    std::shared_ptr<Mesh> PinBall;

    std::shared_ptr<FlipperObject> FlipperLeft;
    std::shared_ptr<FlipperObject> FlipperRight;

    PlayingField(threepp::Object3D &scene,BulletPhysics &bullet) {
        plane = createPlane(parameters_.Width, parameters_.Height);
        scene.add(plane);
        bullet.addMesh(*plane);
        bullet.get(*plane)->body->setRestitution(0.5);

        createBorder(scene,bullet);

        PinBall = createBall(parameters_.BallSize / 2);
        scene.add(PinBall);
        bullet.addMesh(*PinBall, 80.6, true);

        FlipperLeft->setFlipperDirection(-1);
        FlipperLeft->addFlipper(parameters_.BallSize, bullet, scene);
        FlipperLeft->setPosition(-2.5 * parameters_.BallSize, parameters_.BallSize / 2, parameters_.Height / 3);

        FlipperRight->setFlipperDirection(1);
        FlipperRight->addFlipper(parameters_.BallSize, bullet, scene);
        FlipperRight->setPosition(2.5 * parameters_.BallSize, parameters_.BallSize / 2, parameters_.Height / 3);

    }

private:
    Parameters parameters_;

    std::shared_ptr<Mesh> plane;
    std::shared_ptr<Mesh> RightWall;
    std::shared_ptr<Mesh> LeftWall;
    std::shared_ptr<Mesh> TopWall;
    std::shared_ptr<Mesh> BottomWall;

    void createBorder(threepp::Object3D &scene,BulletPhysics &bullet){
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
};


#endif //PINBALLGAME_PLAYINGFIELD_HPP
