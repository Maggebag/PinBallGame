
#include "GameObjects/LightShieldObject.hpp"

#include <threepp/scenes/Scene.hpp>

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>

TEST_CASE("LightShieldObject tests") {

    threepp::BulletPhysics bullet;
    auto scene = threepp::Scene::create();

    SECTION("createShieldShape") {
        LightShieldObject shield;
        shield.createShieldShape(10.f, 20.f);
        REQUIRE(shield.shieldShape.getPoints().size() >= 8);
    }

    SECTION("createShieldMesh") {
        LightShieldObject shield;
        shield.createShieldShape(10.f, 20.f);
        shield.createShieldMesh(5.f, threepp::Color::white);
        REQUIRE(shield.shieldMesh != nullptr);
    }

    SECTION("setShieldPosition") {
        LightShieldObject shield;
        shield.createShieldShape(10.f, 20.f);
        shield.createShieldMesh(5.f, threepp::Color::white);
        shield.setShieldPosition(1.f, 2.f, 3.f);
        REQUIRE(shield.shieldMesh->position.x == Approx(1.f));
        REQUIRE(shield.shieldMesh->position.y == Approx(2.f));
        REQUIRE(shield.shieldMesh->position.z == Approx(3.f));
    }

    SECTION("addToScene") {
        LightShieldObject shield;
        shield.createShieldShape(10.f, 20.f);
        shield.createShieldMesh(5.f, threepp::Color::white);
        shield.addToScene(bullet, *scene, 3.f);
        REQUIRE(scene->children.size() == 1);
    }
}
