
#ifndef PINBALLGAME_FLIPPEROBJECT_HPP
#define PINBALLGAME_FLIPPEROBJECT_HPP

#include <memory>
#include <threepp/objects/Mesh.hpp>
#include <threepp/extras/physics/BulletPhysics.hpp>
#include <threepp/materials/MeshPhongMaterial.hpp>

class FlipperObject {
public:

    void setFlipperDirection(float direction){
        flipperDir_ = direction;
    }

    void setPosition(float x, float y, float z){
        position_.x = x;
        position_.y = y;
        position_.z = z;
        flipper_->position.set(position_.x, position_.y, position_.z);
    }
    void createFlipper(float ballSize){
        flipper_ = createFlipperMesh(flipperDir_, ballSize);
    }

    void addFlipper(float ballSize, threepp::BulletPhysics &bullet, threepp::Object3D &scene){
        scene.add(flipper_);
        bullet.addMesh(*flipper_, 100, true);

        auto bulletFlipper = bullet.get(*flipper_);
        bulletFlipper->body->setRestitution(0.2);

        btFlipper_ = std::make_unique<btHingeConstraint>(*bulletFlipper->body, btVector3(flipperDir_ * ((3.5*ballSize)/2.5), 0, 0),
                                                         btVector3(0, 1, 0));
        btFlipper_->enableAngularMotor(true, 0, 9999999999.f);
        if (flipperDir_ > 0) {
            btFlipper_->setLimit(-0.4, 0.5);
        } else if (flipperDir_ < 0) {
            btFlipper_->setLimit(-0.5, 0.5);
        }
        bullet.addConstraint(btFlipper_.get(), true);
    }

    void activateFlipper() const{
        btFlipper_->setMotorTargetVelocity(-9999999999.f * flipperDir_);
    }
    void deactivateFlipper() const{
        btFlipper_->setMotorTargetVelocity(9999999999.f * flipperDir_);
    }
private:
    std::shared_ptr<threepp::Mesh> flipper_;
    std::unique_ptr<btHingeConstraint> btFlipper_;
    threepp::Vector3 position_;
    float flipperDir_ = 0;

    static std::shared_ptr<threepp::Mesh> createFlipperMesh(int direction, float ballSize){ //-1 for left flipper and 1 for right flipper
        const auto flipperMaterial = threepp::MeshPhongMaterial::create();
        flipperMaterial->color = threepp::Color::palegreen;
        const auto flipperAxisMaterial = threepp::MeshPhongMaterial::create();
        flipperAxisMaterial->color = threepp::Color::red;

        const auto flipperGeometry = threepp::BoxGeometry::create(3.5f * ballSize, 22, 20);
        auto flipperMesh = threepp::Mesh::create(flipperGeometry, flipperMaterial);

        const auto flipperAxisGeometry = threepp::CylinderGeometry::create(flipperGeometry->height / 2 - 2, flipperGeometry->height / 2 - 2, 27);
        flipperAxisGeometry->translate(direction * flipperGeometry->width / 2.5, 0, 0);
        auto flipperAxisMesh = threepp::Mesh::create(flipperAxisGeometry, flipperAxisMaterial);
        flipperMesh->add(flipperAxisMesh);
        flipperMesh->castShadow = true;

        return flipperMesh;
    }
};

#endif //PINBALLGAME_FLIPPEROBJECT_HPP
