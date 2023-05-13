
#include "utils.hpp"
#include <threepp/materials/MeshPhongMaterial.hpp>
#include <threepp/geometries/geometries.hpp>

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>

TEST_CASE("createCylinder Test") {

    auto cylinder = utils::createCylinder(5, 20, threepp::Color::black);

    auto geometry = dynamic_cast<threepp::CylinderGeometry *>(cylinder->geometry());
    auto material = dynamic_cast<threepp::MeshPhongMaterial *>(cylinder->material());

    CHECK(geometry->type() == "CylinderGeometry");
    CHECK(geometry->radiusTop == geometry->radiusTop);
    CHECK(geometry->radiusTop == 5);

    CHECK(material->color == threepp::Color::black);

    CHECK(cylinder->castShadow == true);
}

TEST_CASE("createBox Test") {

    auto box = utils::createBox(5, 10, 20, threepp::Color::yellow);

    auto geometry = dynamic_cast<threepp::BoxGeometry *>(box->geometry());
    auto material = dynamic_cast<threepp::MeshPhongMaterial *>(box->material());

    CHECK(geometry->type() == "BoxGeometry");
    CHECK(geometry->width == 5);
    CHECK(geometry->depth == 10);
    CHECK(geometry->height == 20);

    CHECK(material->color == threepp::Color::yellow);

    CHECK(box->castShadow == true);
}

TEST_CASE("createPlane Test") {

    auto plane = utils::createPlane(10, 20, threepp::Color::aqua);

    auto geometry = dynamic_cast<threepp::PlaneGeometry *>(plane->geometry());
    auto material = dynamic_cast<threepp::MeshPhongMaterial *>(plane->material());

    CHECK(geometry->type() == "PlaneGeometry");
    CHECK(geometry->width == 10);
    CHECK(geometry->height == 20);

    CHECK(material->color == threepp::Color::aqua);

    CHECK(plane->receiveShadow == true);
}

TEST_CASE("createBall Test") {

    auto ball = utils::createBall(20);

    auto geometry = dynamic_cast<threepp::SphereGeometry *>(ball->geometry());
    auto material = dynamic_cast<threepp::MeshPhongMaterial *>(ball->material());

    CHECK(geometry->radius == 20);
    CHECK(material->color == threepp::Color::silver);

    CHECK(ball->castShadow == true);
    CHECK(ball->receiveShadow == true);
}

TEST_CASE("createLight Test") {

    auto light = utils::createLight(threepp::Vector3(0, 1, 0));

    CHECK(light->castShadow == true);
    CHECK(light->position == threepp::Vector3(0, 1, 0));
}