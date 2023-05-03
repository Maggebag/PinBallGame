

#ifndef PINBALLGAME_BORDGEN_HPP
#define PINBALLGAME_BORDGEN_HPP

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
    std::shared_ptr<Mesh> plane;
    std::shared_ptr<Mesh> RightWall;
    std::shared_ptr<Mesh> LeftWall;
    std::shared_ptr<Mesh> TopWall;
    std::shared_ptr<Mesh> BottomWall;

    std::shared_ptr<Mesh> PinBall;

    std::shared_ptr<Mesh> FlipperLeft;
    std::shared_ptr<Mesh> FlipperRight;

    PlayingField() {
        plane = utils::createPlane(parameters_.Width, parameters_.Height);

        RightWall = utils::createBox(parameters_.BorderWidth, parameters_.Height, parameters_.BorderHeight);
        RightWall->position.set(parameters_.Width / 2 + parameters_.HalfBorderWidth, parameters_.BorderHeight / 2, 0);

        LeftWall = utils::createBox(parameters_.BorderWidth, parameters_.Height, parameters_.BorderHeight);
        LeftWall->position.set(-(parameters_.Width / 2 + parameters_.HalfBorderWidth), parameters_.BorderHeight / 2, 0);

        TopWall = utils::createBox(parameters_.Width + parameters_.BorderWidth * 2, parameters_.BorderWidth,
                                   parameters_.BorderHeight);
        TopWall->position.set(0, parameters_.BorderHeight / 2, -(parameters_.Height / 2 + parameters_.HalfBorderWidth));

        BottomWall = utils::createBox(parameters_.Width + parameters_.BorderWidth * 2, parameters_.BorderWidth,
                                      parameters_.BorderHeight);
        BottomWall->position.set(0, parameters_.BorderHeight / 2, parameters_.Height / 2 + parameters_.HalfBorderWidth);

        PinBall = utils::createBall(parameters_.BallSize / 2);

        FlipperLeft = utils::createFlipper(-1, parameters_.BallSize);
        FlipperLeft->position.set(-2.5 * parameters_.BallSize, parameters_.BallSize / 2, parameters_.Height / 3);
        FlipperRight = utils::createFlipper(1, parameters_.BallSize);
        FlipperRight->position.set(2.5 * parameters_.BallSize, parameters_.BallSize / 2, parameters_.Height / 3);
    }

private:
    Parameters parameters_;
};


#endif //PINBALLGAME_BORDGEN_HPP
