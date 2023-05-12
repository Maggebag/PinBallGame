
#include "GameObjects/PlungerObject.hpp"
#include <threepp/scenes/Scene.hpp>

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>

TEST_CASE("PlungerObject tests") {

    PlungerObject plunger;

    SECTION("setPlungerTravelLength") {
        plunger.setPlungerTravelLength(10);
        REQUIRE(plunger.plungerTravelLength == 10);
    }

    SECTION("createPlunger") {
        plunger.createPlunger(1);
        REQUIRE(plunger.baseBox != nullptr);
        REQUIRE(plunger.plungerBox != nullptr);
    }

    SECTION("addPlunger") {
        threepp::BulletPhysics bullet;
        threepp::Object3D scene;
        plunger.createPlunger(1);
        plunger.addPlunger(bullet, scene);
        REQUIRE(scene.children.size() == 2);
    }

    SECTION("setPosition") {
        plunger.createPlunger(1);
        plunger.setPosition(1, 2, 3);
        REQUIRE(plunger.baseBox->position == threepp::Vector3(1, 2, 3));
        REQUIRE(plunger.plungerBox->position == threepp::Vector3(1, 2, -plunger.plungerTravelLength + 3));
    }

    SECTION("PlungerSetUpperLim") {
        threepp::BulletPhysics bullet;
        threepp::Object3D scene;
        plunger.createPlunger(1);
        plunger.addPlunger(bullet, scene);
        plunger.PlungerSetUpperLim(10);
        REQUIRE(plunger.btPlunger->getUpperLinLimit() == 10);
    }

    SECTION("releasePlunger") {
        threepp::BulletPhysics bullet;
        threepp::Object3D scene;
        plunger.createPlunger(1);
        plunger.addPlunger(bullet, scene);
        plunger.releasePlunger();
        REQUIRE(plunger.btPlunger->getTargetLinMotorVelocity() == -1000000);
    }

    SECTION("resetPlunger") {
        threepp::BulletPhysics bullet;
        threepp::Object3D scene;
        plunger.createPlunger(1);
        plunger.addPlunger(bullet, scene);
        plunger.resetPlunger();
        REQUIRE(plunger.btPlunger->getTargetLinMotorVelocity() == 1000000);
    }

    SECTION("createInsideShield") {
        plunger.createInsideShield(100, 10, 1);
        REQUIRE(plunger.insideShield != nullptr);
    }

    SECTION("addInsideShield") {
        threepp::BulletPhysics bullet;
        threepp::Object3D scene;
        plunger.createInsideShield(100, 10, 1);
        plunger.addInsideShield(bullet, scene);
        REQUIRE(scene.children.size() == 1);
    }
}