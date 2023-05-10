
#ifndef PINBALLGAME_BALLGUIDESOBJECT_HPP
#define PINBALLGAME_BALLGUIDESOBJECT_HPP

#include <memory>
#include <threepp/objects/Mesh.hpp>
#include <threepp/math/MathUtils.hpp>
#include <threepp/extras/physics/BulletPhysics.hpp>
#include <threepp/math/Color.hpp>

#include "utils.hpp"

class BallGuidesObject{

public:
    std::shared_ptr<threepp::Mesh> BallGuideLeft;
    std::shared_ptr<threepp::Mesh> BallGuideLeft2;
    std::shared_ptr<threepp::Mesh> BallGuideLeftBtm;

    std::shared_ptr<threepp::Mesh> BallGuideRight;
    std::shared_ptr<threepp::Mesh> BallGuideRight2;
    std::shared_ptr<threepp::Mesh> BallGuideRightBtm;

    void createGuides(float ballSize);

    void getFlipperPos(threepp::Vector3 pos);

    void addBallGuides(threepp::BulletPhysics &bullet, threepp::Object3D &scene) const;

private:
    float BallSize;

    threepp::Color::ColorName color_ = threepp::Color::blueviolet;
    threepp::Vector3 FlipperLeftPos_;
    threepp::Vector3 FlipperRightPos_;
};

#endif //PINBALLGAME_BALLGUIDESOBJECT_HPP
