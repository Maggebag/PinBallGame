
#include"GameObjects/BouncyCylinders.hpp"

#include <threepp/scenes/Scene.hpp>

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>

TEST_CASE("bouncyCylindersObject tests") {
    threepp::BulletPhysics bullet;
    auto scene = threepp::Scene::create();

    SECTION("createMeshes") {
        bouncyCylindersObject cylinders;

        cylinders.createMeshes(1.0f, 2.0f, threepp::Color::red);

        REQUIRE(cylinders.CylinderTop != nullptr);
        REQUIRE(cylinders.CylinderLeft != nullptr);
        REQUIRE(cylinders.CylinderRight != nullptr);
    }

    SECTION("setPosition") {
        bouncyCylindersObject cylinders;
        cylinders.createMeshes(1.0f, 2.0f, threepp::Color::red);

        cylinders.setPosition(threepp::Vector3(1.0f, 2.0f, 3.0f));

        REQUIRE(cylinders.CylinderTop->position == threepp::Vector3(1.0f, 2.0f, -3.f + 1.f));
        REQUIRE(cylinders.CylinderLeft->position == threepp::Vector3(-1 - 4.f, 2.0f, -3.f + 3.f));
        REQUIRE(cylinders.CylinderRight->position == threepp::Vector3(1 + 4.f, 2.0f, -3.f + 3.f));
    }

    SECTION("addToScene") {
        bouncyCylindersObject cylinders;
        cylinders.createMeshes(1.0f, 2.0f, threepp::Color::red);

        cylinders.addToScene(bullet, *scene);

        REQUIRE(scene->children.size() == 3);
        REQUIRE(bullet.get(*cylinders.CylinderTop)->body->getRestitution() == 3);
        REQUIRE(bullet.get(*cylinders.CylinderLeft)->body->getRestitution() == 3);
        REQUIRE(bullet.get(*cylinders.CylinderRight)->body->getRestitution() == 3);
    }
}