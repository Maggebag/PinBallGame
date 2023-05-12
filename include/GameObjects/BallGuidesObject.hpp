
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

    void createGuides(float ballSize){
        BallSize = ballSize;
        BallGuideLeft = utils::createBox(4.25f*ballSize-5,22,20, color_);
        BallGuideLeft2= utils::createBox(22,3*ballSize,20, color_);
        BallGuideRight = utils::createBox(4.25f*ballSize-5,22,20, color_);
        BallGuideRight2= utils::createBox(22,3*ballSize,20, color_);
    }

    void getFlipperPos(threepp::Vector3 pos){
        FlipperLeftPos_.set(-pos.x,pos.y,pos.z);
        FlipperRightPos_.set(pos.x,pos.y,pos.z);
    }

    void addBallGuides(threepp::BulletPhysics &bullet, threepp::Object3D &scene) const{
        BallGuideLeft->rotateY(-threepp::math::PI/6);
        BallGuideLeft->position.set(FlipperLeftPos_.x-std::cos(threepp::math::PI/6)*4.25f*BallSize,FlipperLeftPos_.y,FlipperLeftPos_.z-std::sin(threepp::math::PI/6)*4.25f*BallSize+22);
        BallGuideLeft2->position.set(FlipperLeftPos_.x-std::cos(threepp::math::PI/6)*4*BallSize-(std::cos(threepp::math::PI/6)*4*BallSize)/2, FlipperLeftPos_.y, FlipperLeftPos_.z-3.5f*BallSize);

        BallGuideRight->rotateY(threepp::math::PI/6);
        BallGuideRight->position.set(FlipperRightPos_.x+std::cos(threepp::math::PI/6)*4.25f*BallSize,FlipperRightPos_.y,FlipperRightPos_.z-std::sin(threepp::math::PI/6)*4.25f*BallSize+22);
        BallGuideRight2->position.set(FlipperRightPos_.x+std::cos(threepp::math::PI/6)*4*BallSize+(std::cos(threepp::math::PI/6)*4*BallSize)/2, FlipperRightPos_.y, FlipperRightPos_.z-3.5f*BallSize);

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
    float BallSize;

    threepp::Color::ColorName color_ = threepp::Color::blueviolet;
    threepp::Vector3 FlipperLeftPos_;
    threepp::Vector3 FlipperRightPos_;
};

#endif //PINBALLGAME_BALLGUIDESOBJECT_HPP
