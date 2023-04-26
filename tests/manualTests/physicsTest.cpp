//This file has been for myself to test new functions to understand them properly before implementing them
//I have tested things such has how to make hingeconstraints and how to properly employ and use the bullet physics-engine

#include "threepp/threepp.hpp"
#include "threepp/extras/physics/BulletPhysics.hpp"
#include "GameObjects.hpp"
#include "keyInput.hpp"
#include "bordGen.hpp"
#include <sstream>

using namespace threepp;

int main() {

    Canvas canvas(Canvas::Parameters().antialiasing(8));
    GLRenderer renderer(canvas);
    renderer.setClearColor(Color::aliceblue);

    auto camera = PerspectiveCamera::create(75, canvas.getAspect(), 0.1f, 10000);
    camera->position.set(0, 500, 10);

    OrbitControls controls{camera, canvas};

    auto scene = Scene::create();

    auto box1 = utils::createBox(30,15,20);
    auto box2 = utils::createBox(30,15,20);
    box1->position.set(150,13.5,40);
    box2->position.set(150,13.5,120);
    scene->add(box1);
    scene->add(box2);

    canvas.onWindowResize([&](WindowSize size){
        camera->aspect = size.getAspect();
        camera->updateProjectionMatrix();
        renderer.setSize(size);
    });

    Vector3 grav = {0, -974.694, 111.052}; //todo:: make function to get components of gravity
    BulletPhysics bullet(grav);

    PlayingField playingField;
    scene->add(playingField.plane);
    scene->add(playingField.TopWall);
    scene->add(playingField.BottomWall);
    scene->add(playingField.RightWall);
    scene->add(playingField.LeftWall);

    scene->add(playingField.PinBall);
    playingField.PinBall->position.set(40,13.5,140);

    scene->add(playingField.FlipperLeft);
    scene->add(playingField.FlipperRight);

    bullet.addMesh(*playingField.plane);
    bullet.get(*playingField.plane)->body->setRestitution(0.6);

    bullet.addMesh(*playingField.TopWall);
    bullet.get(*playingField.TopWall)->body->setRestitution(0.5);
    bullet.addMesh(*playingField.BottomWall);
    bullet.get(*playingField.BottomWall)->body->setRestitution(0.5);
    bullet.addMesh(*playingField.RightWall);
    bullet.get(*playingField.RightWall)->body->setRestitution(0.5);
    bullet.addMesh(*playingField.LeftWall);
    bullet.get(*playingField.LeftWall)->body->setRestitution(0.5);

    bullet.addMesh(*playingField.PinBall, 80.6, true);
    bullet.get(*playingField.PinBall)->body->setRestitution(1);

    bullet.addMesh(*playingField.FlipperRight, 100,  true);
    auto flippy = bullet.get(*playingField.FlipperRight);
    btHingeConstraint flippyBoi(*flippy->body,btVector3(27,0,0),btVector3(0,1,0));
    flippyBoi.enableAngularMotor(true,0,1000000);
    flippyBoi.setLimit(-0.4,0.5);
    bullet.addConstraint(&flippyBoi, true);

    bullet.addMesh(*playingField.FlipperLeft,100,true);
    auto flippy2 = bullet.get(*playingField.FlipperLeft);
    btHingeConstraint flippyBoi2(*flippy2->body,btVector3(-27,0,0), btVector3(0,1,0));
    flippyBoi2.enableAngularMotor(true,0,1000000);
    flippyBoi2.setLimit(-0.5,0.4);
    bullet.addConstraint(&flippyBoi2, true);

    bullet.addMesh(*box1,10,true);
    bullet.addMesh(*box2,0,true);

    auto topBox = bullet.get(*box1);
    auto bottomBox = bullet.get(*box2);

    btTransform localA;
    btTransform localB;

    localA.setIdentity();
    localB.setIdentity();
    localA.getBasis().setEulerZYX(0,math::PI/2,0);
    localA.setOrigin(btVector3(0.0,0.0,80.0));
    localB.getBasis().setEulerZYX(0,math::PI/2,0);
    localB.setOrigin(btVector3(0.0,0.0,math::TWO_PI));

    btSliderConstraint launchSlider(*topBox->body,*bottomBox->body,localA,localB,true);
    launchSlider.setLowerLinLimit(0);
    launchSlider.setLowerAngLimit(0);
    launchSlider.setUpperAngLimit(0);
    launchSlider.setPoweredLinMotor(true);
    launchSlider.setMaxLinMotorForce(10000);
    bullet.addConstraint(&launchSlider, true);

    bullet.get(*box1)->body->setLinearVelocity({0,0,100});

    renderer.enableTextRendering();
    auto& handle = renderer.textHandle();

    auto keyInput = std::make_shared<KeyInput>();

    canvas.addKeyListener(keyInput.get());

    canvas.animate([&](float dt) {
        bullet.step(dt);

        keyInput->flippers(flippyBoi, flippyBoi2);
        keyInput->launcher(launchSlider);
        keyInput->reset(playingField.PinBall, bullet);

        renderer.render(scene, camera);

        std::stringstream ss;
        ss << renderer.info();
        handle.setText(ss.str());

    });

}
