
#include "gameLogic.hpp"
#include "utils.hpp"

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

TEST_CASE("ballPosCheck Test"){
    threepp::BulletPhysics bullet(threepp::Vector3(0,0,0));

    auto ball = utils::createBall(20);
    ball->position.set(29,20,13);
    bullet.addMesh(*ball, 1);

    CHECK(ballPosCheck(ball,bullet) ==  threepp::Vector3(29,20,13));
}
