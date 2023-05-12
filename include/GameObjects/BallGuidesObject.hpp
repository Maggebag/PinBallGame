
#ifndef PINBALLGAME_BALLGUIDESOBJECT_HPP
#define PINBALLGAME_BALLGUIDESOBJECT_HPP

#include <memory>
#include <threepp/objects/Mesh.hpp>
#include <threepp/math/MathUtils.hpp>
#include <threepp/extras/physics/BulletPhysics.hpp>
#include <threepp/math/Color.hpp>

#include "utils.hpp"

class BallGuidesObject {

public:
    std::shared_ptr<threepp::Mesh> BallGuideLeft;
    std::shared_ptr<threepp::Mesh> BallGuideLeft2;
    std::shared_ptr<threepp::Mesh> BallGuideLeftBtm;

    std::shared_ptr<threepp::Mesh> BallGuideRight;
    std::shared_ptr<threepp::Mesh> BallGuideRight2;
    std::shared_ptr<threepp::Mesh> BallGuideRightBtm;

    threepp::Vector3 FlipperLeftPos;
    threepp::Vector3 FlipperRightPos;

    void createGuides(float ballSize, threepp::Color::ColorName color) {
        BallSize = ballSize;
        BallGuideLeft = utils::createBox(4.25f * ballSize - 5, 22, 20, color);
        BallGuideLeft2 = utils::createBox(22, 3 * ballSize, 20, color);
        BallGuideRight = utils::createBox(4.25f * ballSize - 5, 22, 20, color);
        BallGuideRight2 = utils::createBox(22, 3 * ballSize, 20, color);
    }

    void getFlipperPos(threepp::Vector3 flipperLeftpos, threepp::Vector3 flipperRightpos) {
        FlipperLeftPos = flipperLeftpos;
        FlipperRightPos = flipperRightpos;
    }

    void addBallGuides(threepp::BulletPhysics &bullet, threepp::Object3D &scene) const {
        BallGuideLeft->rotateY(-threepp::math::PI / 6);
        BallGuideLeft->position.set(FlipperLeftPos.x - std::cos(threepp::math::PI / 6) * 4.25f * BallSize,
                                    FlipperLeftPos.y,
                                    FlipperLeftPos.z - std::sin(threepp::math::PI / 6) * 4.25f * BallSize + 22);
        BallGuideLeft2->position.set(FlipperLeftPos.x - std::cos(threepp::math::PI / 6) * 4 * BallSize -
                                     (std::cos(threepp::math::PI / 6) * 4 * BallSize) / 2, FlipperLeftPos.y,
                                     FlipperLeftPos.z - 3.5f * BallSize);

        BallGuideRight->rotateY(threepp::math::PI / 6);
        BallGuideRight->position.set(FlipperRightPos.x + std::cos(threepp::math::PI / 6) * 4.25f * BallSize,
                                     FlipperRightPos.y,
                                     FlipperRightPos.z - std::sin(threepp::math::PI / 6) * 4.25f * BallSize + 22);
        BallGuideRight2->position.set(FlipperRightPos.x + std::cos(threepp::math::PI / 6) * 4 * BallSize +
                                      (std::cos(threepp::math::PI / 6) * 4 * BallSize) / 2, FlipperRightPos.y,
                                      FlipperRightPos.z - 3.5f * BallSize);

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
};

#endif //PINBALLGAME_BALLGUIDESOBJECT_HPP
