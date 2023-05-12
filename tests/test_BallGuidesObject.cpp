

#include "GameObjects/BallGuidesObject.hpp"

#include <threepp/scenes/Scene.hpp>

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>

TEST_CASE("BallGuidesObject tests") {

    SECTION("createGuides function") {
        BallGuidesObject bgo;
        bgo.createGuides(1.0f, threepp::Color::red);
        REQUIRE(bgo.BallGuideLeft != nullptr);
        REQUIRE(bgo.BallGuideLeft2 != nullptr);
        REQUIRE(bgo.BallGuideRight != nullptr);
        REQUIRE(bgo.BallGuideRight2 != nullptr);
    }

    SECTION("getFlipperPos function") {
        BallGuidesObject bgo;
        threepp::Vector3 leftPos(1.0f, 2.0f, 3.0f);
        threepp::Vector3 rightPos(4.0f, 5.0f, 6.0f);
        bgo.getFlipperPos(leftPos, rightPos);
        REQUIRE(bgo.FlipperLeftPos == leftPos);
        REQUIRE(bgo.FlipperRightPos == rightPos);
    }

    SECTION("addBallGuides function") {
        BallGuidesObject bgo;
        threepp::BulletPhysics bullet;
        auto scene = threepp::Scene::create();
        bgo.createGuides(1.0f, threepp::Color::red);
        threepp::Vector3 leftPos(1.0f, 2.0f, 3.0f);
        threepp::Vector3 rightPos(4.0f, 5.0f, 6.0f);
        bgo.getFlipperPos(leftPos, rightPos);
        bgo.addBallGuides(bullet, *scene);
        REQUIRE(scene->children.size() == 4);
        //Would tests for children size in bullet aswell but no such function present in threepp implementation, well I haven't found it atleast
    }
}

