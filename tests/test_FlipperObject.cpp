
#include "GameObjects/FlipperObject.hpp"

#include <threepp/scenes/Scene.hpp>

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>

TEST_CASE("FlipperObject tests", "[FlipperObject]") {
    const float ballSize = 1.0f;

    SECTION("FlipperObject createFlipper") {
        FlipperObject flipper;
        flipper.setFlipperDirection(1);
        flipper.createFlipper(ballSize);

        REQUIRE(flipper.flipper != nullptr);
    }

    SECTION("FlipperObject addFlipper") {
        threepp::BulletPhysics bullet;
        auto scene = threepp::Scene::create();
        FlipperObject flipper;
        flipper.createFlipper(ballSize);
        flipper.addFlipper(ballSize, bullet, *scene);

        REQUIRE(scene->children.size() == 1);
        //Would tests for children size in bullet aswell but no such function present in threepp implementation, well I haven't found it atleast
    }

    SECTION("FlipperObject activateFlipper") {
        threepp::BulletPhysics bullet;
        threepp::Object3D scene;
        FlipperObject flipper;
        flipper.setFlipperDirection(1);
        flipper.createFlipper(ballSize);
        flipper.addFlipper(ballSize, bullet, scene);
        flipper.activateFlipper();

        REQUIRE(flipper.btFlipper->getMotorTargetVelocity() == Approx(-9999999999.f));
    }

    SECTION("FlipperObject deactivateFlipper") {
        threepp::BulletPhysics bullet;
        threepp::Object3D scene;
        FlipperObject flipper;
        flipper.setFlipperDirection();
        flipper.createFlipper(ballSize);
        flipper.addFlipper(ballSize, bullet, scene);
        flipper.deactivateFlipper();

        REQUIRE(flipper.btFlipper->getMotorTargetVelocity() == Approx(9999999999.f));
    }

    SECTION("FlipperObject getPosition") {
        FlipperObject flipper;
        flipper.createFlipper(1.f);
        flipper.setPosition(1, 2, 3);

        REQUIRE(flipper.getPosition().x == Approx(1));
        REQUIRE(flipper.getPosition().y == Approx(2));
        REQUIRE(flipper.getPosition().z == Approx(3));
    }
}