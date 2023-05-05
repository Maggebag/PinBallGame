#ifndef PINBALLGAME_GAMEOBJECTS_HPP
#define PINBALLGAME_GAMEOBJECTS_HPP

<<<<<<< HEAD
#include "threepp/objects/Mesh.hpp"
#include "threepp/extras/physics/BulletPhysics.hpp"
#include "threepp/math/MathUtils.hpp"
=======
#include "threepp/threepp.hpp"
>>>>>>> parent of 0bf4d6f (ehe)

using namespace threepp;

namespace utils {
    std::shared_ptr<Mesh> createCylinder(float radius, float height);

    std::shared_ptr<Mesh> createBox(float width, float length, float height);

    std::shared_ptr<Mesh> createFlipper(float direction, float ballSize);

    std::shared_ptr<Mesh> createBall(float radius);

<<<<<<< HEAD
/*btHingeConstraint
createFlipperConstraint(std::shared_ptr<threepp::Mesh> Flipper, float direction, float ballSize, threepp::BulletPhysics &bullet) {

    bullet.addMesh(*Flipper, 100, true);

    auto btFlipper = bullet.get(*Flipper);
    btFlipper->body->setRestitution(0.2);
    btHingeConstraint flipperConstraint(*btFlipper->body, btVector3(ballSize, 0, 0), btVector3(0, 1, 0));
    flipperConstraint.enableAngularMotor(true, 0, 100000000000);

    if(direction>0){
        flipperConstraint.setLimit(-0.4, 0.5);
    }
    else if(direction<0) {
        flipperConstraint.setLimit(-0.5,0.5);
    }
    return flipperConstraint;
}; */

/*btSliderConstraint
createPlungerConstraint(std::shared_ptr<threepp::Mesh> baseBox, std::shared_ptr<threepp::Mesh> plungerBox, float plungerTravelLength, threepp::BulletPhysics &bullet) {

    bullet.addMesh(*baseBox);
    bullet.addMesh(*plungerBox, 10, true);

    auto btBaseBox = bullet.get(*baseBox);
    auto btPlungerBox = bullet.get(*plungerBox);

    btTransform localA;
    btTransform localB;

    localA.setIdentity();
    localB.setIdentity();
    localA.getBasis().setEulerZYX(0, threepp::math::PI / 2, 0);
    localA.setOrigin(btVector3(0.0, 0.0, plungerTravelLength));
    localB.getBasis().setEulerZYX(0, threepp::math::PI / 2, 0);
    localB.setOrigin(btVector3(0.0, 0.0, threepp::math::TWO_PI));

    btSliderConstraint plungerConstraint(*btPlungerBox->body, *btBaseBox->body, localA, localB, true);
    plungerConstraint.setLowerLinLimit(0);
    plungerConstraint.setLowerAngLimit(0);
    plungerConstraint.setUpperAngLimit(0);
    plungerConstraint.setPoweredLinMotor(true);
    plungerConstraint.setMaxLinMotorForce(100000);
    return plungerConstraint;

};
 */

class FlipperObject {
public:

    float flipperDir{};
    std::shared_ptr<threepp::Mesh> flipper;

    void setFlipperDirection(float direction) {
        flipperDir = direction;
    }

    void addFlipper(float ballSize, threepp::BulletPhysics &bullet, threepp::Object3D &scene) {
        flipper = createFlipper(flipperDir, ballSize);
        scene.add(flipper);
    }
    void addConstraint(float ballSize, threepp::BulletPhysics &bullet){
        bullet.addMesh(*flipper, 10, true);
        auto btFlipper = bullet.get(*flipper);
        btHingeConstraint btFlipperConstraint(*btFlipper->body,btVector3(ballSize, 0, 0), btVector3(0, 1, 0));

        if(flipperDir>0){
            btFlipperConstraint.setLimit(-0.4, 0.5);
        }
        else if(flipperDir<0) {
            btFlipperConstraint.setLimit(-0.5,0.5);
        }
        bullet.addConstraint(&btFlipperConstraint,true);
    }

    void setPosition(float x, float y, float z) const{
        flipper->position.set(x,y,z);
    }

    void activateFlipper() {
        btFlipperConstraint.setMotorTargetVelocity(-1000000000 * flipperDir);
    }

    void deactivateFlipper() {
        btFlipperConstraint.setMotorTargetVelocity(1000000000 * flipperDir);
    }
private:

};

/*class Plunger {

public:

    float plungerTravelLength;
    std::shared_ptr<threepp::Mesh> baseBox;
    std::shared_ptr<threepp::Mesh> plungerBox;

    btSliderConstraint btPlunger;

    void setPlungerTravelLength(float length){
        plungerTravelLength = length;
    }

    void addPlunger(float ballSize, threepp::BulletPhysics &bullet, threepp::Object3D &scene){
        baseBox = createBox(1.5*ballSize,20,ballSize);
        plungerBox = createBox(1.5*ballSize,20,ballSize);
        scene.add(baseBox);
        scene.add(plungerBox);
        auto yes = createPlungerConstraint(baseBox, plungerBox, plungerTravelLength,bullet);
        yes = btPlunger;
        bullet.addConstraint(&yes, true);
    }

    void setPosition(float x, float y, float z) const{
        baseBox->position.set(x,y,z+plungerTravelLength);
        plungerBox->position.set(x,y,z);
    }

};
*/
=======
    std::shared_ptr<Mesh> createPlane(float width, float height);

}
>>>>>>> parent of 0bf4d6f (ehe)
#endif //PINBALLGAME_GAMEOBJECTS_HPP
