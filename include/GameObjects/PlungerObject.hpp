
#ifndef PINBALLGAME_PLUNGEROBJECT_HPP
#define PINBALLGAME_PLUNGEROBJECT_HPP

#include <memory>
#include <threepp/objects/Mesh.hpp>
#include <threepp/extras/physics/BulletPhysics.hpp>


class PlungerObject {

public:

    float plungerTravelLength;
    std::shared_ptr<threepp::Mesh> baseBox;
    std::shared_ptr<threepp::Mesh> plungerBox;

    std::shared_ptr<threepp::Mesh> insideShield;

    std::unique_ptr<btSliderConstraint> btPlunger;

    void setPlungerTravelLength(float length);

    void createPlunger(float ballSize);

    void addPlunger(threepp::BulletPhysics &bullet, threepp::Object3D &scene);

    void setPosition(float x, float y, float z);

    void PlungerSetUpperLim(float limit) const;

    void releasePlunger() const;

    void resetPlunger() const;

    void createInsideShield(float gameHeight, float borderHeight, float ballSize);

    void addInsideShield(threepp::BulletPhysics &bullet, threepp::Object3D &scene) const;

private:
    threepp::Vector3 position;
};


#endif //PINBALLGAME_PLUNGEROBJECT_HPP
