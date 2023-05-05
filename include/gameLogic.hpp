
#ifndef PINBALLGAME_GAMELOGIC_HPP
#define PINBALLGAME_GAMELOGIC_HPP

#include "threepp/objects/Mesh.hpp"
#include "threepp/extras/physics/BulletPhysics.hpp"
#include "threepp/math/MathUtils.hpp"
#include <cmath>

void ballPosCheck(const std::shared_ptr<threepp::Mesh>& pinBall, threepp::BulletPhysics &bullet){
    auto btBallPos = bullet.get(*pinBall)->body->getCenterOfMassPosition();
    threepp::Vector3 ballPos = reinterpret_cast<threepp::Vector3 &&>(btBallPos);
    if(ballPos.z>470){
        bullet.setMeshPosition(*pinBall, {30, 13.5, 0});
    }
}

threepp::Vector3 getGravFromAngle(float angle) { //input in degrees
    auto angleInRad = threepp::math::degToRad(angle);
    threepp::Vector3 Gravity;
    Gravity.y = -9.81*std::cos(angleInRad);
    Gravity.z = 9.81*std::sin(angleInRad);
    Gravity.addScalar(100);
    return Gravity;
}
#endif //PINBALLGAME_GAMELOGIC_HPP
