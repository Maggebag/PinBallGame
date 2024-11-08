
#ifndef PINBALLGAME_LIGHTSHIELDOBJECT_HPP
#define PINBALLGAME_LIGHTSHIELDOBJECT_HPP

#include <memory>
#include <threepp/objects/Mesh.hpp>
#include <threepp/extras/physics/BulletPhysics.hpp>
#include <threepp/materials/MeshPhongMaterial.hpp>
#include <threepp/geometries/ShapeGeometry.hpp>
#include <threepp/geometries/ExtrudeGeometry.hpp>
#include <threepp/objects/Group.hpp>

#include <iostream>

#include "utils.hpp"

class LightShieldObject {

public:

    threepp::Shape shieldShape;
    std::shared_ptr<threepp::Mesh> shieldMesh;

    std::shared_ptr<threepp::Mesh> longSideBox;

    void createShieldShape(float width, float length) {

        shieldShape = threepp::Shape();
        shieldShape.moveTo(0.f, length / 2.f);
        shieldShape.lineTo(0.f, length * 0.85f)
                .quadraticCurveTo(0.f, length, 0.1f * width, length * 0.9f);
        shieldShape.lineTo(width * 0.95f, length * 0.035f)
                .quadraticCurveTo(width, 0.f, width * 0.95f, length * 0.01f);
        shieldShape.lineTo(width * 0.05f, length * 0.25f)
                .quadraticCurveTo(0.f, length * 0.3f, 0.f, length * 0.35f);
    }

    void addBoxToLongestSide() {

        boxExist_ = true;

        auto points = shieldShape.getPoints(1);

        boxPos_.lerpVectors(points[2], points[3], 0.5f);

        auto boxLength = points[2].distanceTo(points[3]);

        auto relativeAngle = std::acos((points[2].x - points[3].x) / boxLength);
        angle_ = threepp::math::PI + relativeAngle;

        longSideBox = utils::createBox(boxLength, 5, height_ - 8.f, threepp::Color::orangered);
        longSideBox->position.set(boxPos_.x + 6.f, height_ / 2.f, -boxPos_.y - 6.f);
        longSideBox->rotateY(angle_);
    }

    void createShieldMesh(float height, threepp::Color::ColorName color) {

        threepp::ExtrudeGeometry::Options opts;
        height_ = height;
        opts.depth = height;
        opts.bevelEnabled = true;
        opts.bevelSize = 10.f;
        auto shieldGeometry = threepp::ExtrudeGeometry::create(shieldShape, opts);
        shieldGeometry->rotateX(-threepp::math::PI / 2);

        auto shieldMaterial = threepp::MeshPhongMaterial::create();
        shieldMaterial->color = color;

        shieldMesh = threepp::Mesh::create(shieldGeometry, shieldMaterial);
        shieldMesh->castShadow = true;
    }

    void flipShield() {
        shieldMesh->geometry()->rotateZ(threepp::math::PI);
        if (boxExist_) {
            longSideBox->rotateY(-2 * angle_);
            longSideBox->position.setX(position_.x - boxPos_.x - 6.f);
        }
        shieldMesh->position.setY(height_);
    }

    void rotateShield(float angle) { //not allowed to rotate shieldMesh if box exists
        if (!boxExist_) {
            auto angleInRad = threepp::math::degToRad(angle);
            shieldMesh->rotateY(angleInRad);
        }
    }

    void setShieldPosition(float x, float y, float z) {
        position_.x = x;
        position_.y = y;
        position_.z = z;

        shieldMesh->position.set(position_.x, position_.y, position_.z);
        if (boxExist_) {
            longSideBox->position.set(position_.x + boxPos_.x + 6.f, height_ / 2.f, position_.z - boxPos_.y - 6.f);
        }
    }

    void addToScene(threepp::BulletPhysics &bullet, threepp::Object3D &scene, float restitution = 3) {
        scene.add(shieldMesh);
        bullet.addMesh(*shieldMesh);
        bullet.get(*shieldMesh)->body->setRestitution(1);

        if (boxExist_) {
            scene.add(longSideBox);
            bullet.addMesh(*longSideBox);
            bullet.get(*longSideBox)->body->setRestitution(restitution);
        }
    }

private:
    float height_;
    float angle_;
    bool boxExist_ = false;

    threepp::Vector2 boxPos_;

    threepp::Vector3 position_;
};

#endif //PINBALLGAME_LIGHTSHIELDOBJECT_HPP
