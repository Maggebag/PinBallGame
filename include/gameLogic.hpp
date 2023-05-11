
#ifndef PINBALLGAME_GAMELOGIC_HPP
#define PINBALLGAME_GAMELOGIC_HPP

#include <threepp/objects/Mesh.hpp>
#include <threepp/extras/physics/BulletPhysics.hpp>

threepp::Vector3
ballPosCheck(const std::shared_ptr<threepp::Mesh> &pinBall, threepp::BulletPhysics &bullet) {
    auto btBallPos = bullet.get(*pinBall)->body->getCenterOfMassPosition();
    threepp::Vector3 ballPos = reinterpret_cast<threepp::Vector3 &&>(btBallPos);
    return ballPos;
}

void checkIfBallOut(std::shared_ptr<threepp::Mesh> pinBall, threepp::Vector3 ballPos, threepp::Vector3 resetPos,
                    float heightLimit, threepp::BulletPhysics &bullet) {
    if (ballPos.z > heightLimit) {
        bullet.setMeshPosition(*pinBall, {resetPos.x, resetPos.y, resetPos.z});
    }
}

threepp::Vector3 getGravFromAngle(float angle) { //input in degrees
    auto angleInRad = threepp::math::degToRad(angle);
    threepp::Vector3 Gravity;
    Gravity.x = 0;
    Gravity.y = -9.81 * std::cos(angleInRad) * 100;
    Gravity.z = 9.81 * std::sin(angleInRad) * 100;
    return Gravity;
}

#endif //PINBALLGAME_GAMELOGIC_HPP
