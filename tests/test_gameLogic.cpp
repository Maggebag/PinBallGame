
#include "gameLogic.hpp"
#include "utils.hpp"
#include <threepp/extras/physics/BulletPhysics.hpp>

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

TEST_CASE("ballPosGet Test"){
    threepp::BulletPhysics bullet;

    auto ball = utils::createBall(20);
    ball->position.set(29,20,13);
    bullet.addMesh(*ball, 1);

    CHECK(ballPosGet(ball,bullet) ==  threepp::Vector3(29,20,13));
}

TEST_CASE("ballPosGet_bullet Test"){

    threepp::BulletPhysics bullet;

    auto ball = utils::createBall(20);
    bullet.addMesh(*ball, 1);

    threepp::Vector3 pos(0,-10,34);

    bullet.setMeshPosition(*ball, pos);

    CHECK(ballPosGet(ball,bullet) == pos);

}

TEST_CASE("checkIfBallOut Test"){

    threepp::BulletPhysics bullet;

    auto ball = utils::createBall(20);
    bullet.addMesh(*ball,1);
    threepp::Vector3 ballPos1(0,20,0);
    bullet.setMeshPosition(*ball,ballPos1);

    float heightLimit = 100;

    threepp::Vector3 resetPos(10,20,30);

    checkIfBallOut(ball, ballPos1, resetPos, heightLimit, bullet);

    CHECK(bullet.get(*ball)->body->getCenterOfMassPosition() == btVector3(0,20,0));

    threepp::Vector3 ballPos2(0,0,120);

    bullet.setMeshPosition(*ball, ballPos2);

    checkIfBallOut(ball, ballPos2, resetPos, heightLimit, bullet);

    CHECK(bullet.get(*ball)->body->getCenterOfMassPosition() == btVector3(10,20,30));

}

TEST_CASE("getGravFromAngle Test"){
    float angle = 25;
    threepp::Vector3 grav = getGravFromAngle(angle);
    REQUIRE(grav.x == 0);
    REQUIRE_THAT(grav.y, Catch::Matchers::WithinRel(-889.0879,0.001));
    REQUIRE_THAT(grav.z, Catch::Matchers::WithinRel(414.5885,0.001));

    float angle2 = 0.2f;
    threepp::Vector3 grav2 = getGravFromAngle(angle2);
    REQUIRE(grav2.x == 0);
    REQUIRE_THAT(grav2.y, Catch::Matchers::WithinRel(-980.994,0.001));
    REQUIRE_THAT(grav2.z, Catch::Matchers::WithinRel(3.424,0.001));
}