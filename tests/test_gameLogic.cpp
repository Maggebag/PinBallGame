
#include "gameLogic.hpp"
#include "utils.hpp"
#include <threepp/extras/physics/BulletPhysics.hpp>
#include <threepp/materials/materials.hpp>

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>

TEST_CASE("ballPosGet Test") {
    threepp::BulletPhysics bullet;

    auto ball = utils::createBall(20);
    ball->position.set(1.f, 2.f, 3.f);
    bullet.addMesh(*ball, 1);

    SECTION("Returns Vector3") {
        auto result = ballPosGet(ball, bullet);
        REQUIRE(result.x != 0.0f);
        REQUIRE(result.y != 0.0f);
        REQUIRE(result.z != 0.0f);
    }

    SECTION("Returns expected result") {
        auto result = ballPosGet(ball, bullet);
        threepp::Vector3 expectedPos(1.0f, 2.0f, 3.0f);
        REQUIRE(result == expectedPos);
    }
}

TEST_CASE("checkIfBallOut Test") {

    auto pinBall = utils::createBall(2);
    threepp::BulletPhysics bullet;
    bullet.addMesh(*pinBall);

    SECTION("Does not reset ball position if not out of bounds") {
        threepp::Vector3 ballPos(0, 0, 0);
        threepp::Vector3 resetPos(0, 0, 0);
        float heightLimit = 100.0f;
        checkIfBallOut(pinBall, ballPos, resetPos, heightLimit, bullet);

        auto btBallPos = bullet.get(*pinBall)->body->getCenterOfMassPosition();

        REQUIRE(reinterpret_cast<threepp::Vector3 &&>(btBallPos) == ballPos);
    }

    SECTION("Resets ball position if out of bounds") {
        threepp::Vector3 ballPos(0, 0, 101.0f);
        threepp::Vector3 resetPos(1, 2, 3);
        float heightLimit = 100.0f;
        checkIfBallOut(pinBall, ballPos, resetPos, heightLimit, bullet);

        auto btBallPos = bullet.get(*pinBall)->body->getCenterOfMassPosition();

        REQUIRE(reinterpret_cast<threepp::Vector3 &&>(btBallPos) == resetPos);
    }
}

TEST_CASE("getGravFromAngle Test") {
    SECTION("Returns Vector3") {
        float angle = 45.0f;
        auto result = getGravFromAngle(angle);
        REQUIRE(result.x == 0.0f);
        REQUIRE(result.y != 0.0f);
        REQUIRE(result.z != 0.0f);
    }

    SECTION("Returns expected result") {
        float angle = 25.f;
        threepp::Vector3 grav = getGravFromAngle(angle);
        REQUIRE(grav.x == 0);
        REQUIRE_THAT(grav.y, Catch::Matchers::WithinRel(-889.0879f, 0.001f));
        REQUIRE_THAT(grav.z, Catch::Matchers::WithinRel(414.5885f, 0.001f));

        float angle2 = 0.2f;
        threepp::Vector3 grav2 = getGravFromAngle(angle2);
        REQUIRE(grav2.x == 0);
        REQUIRE_THAT(grav2.y, Catch::Matchers::WithinRel(-980.994f, 0.001f));
        REQUIRE_THAT(grav2.z, Catch::Matchers::WithinRel(3.424f, 0.001f));
    }
}