//This file has been for myself to test new functions to understand them properly before implementing them
//I have tested things such has how to make hingeconstraints and how to properly employ and use the bullet physics-engine

#include "threepp/threepp.hpp"
#include "threepp/extras/physics/BulletPhysics.hpp"
#include "GameObjects.hpp"
#include "keyInput.hpp"

using namespace threepp;

int main() {

    Canvas canvas(Canvas::Parameters().antialiasing(8));
    GLRenderer renderer(canvas);
    renderer.setClearColor(Color::aliceblue);

    auto camera = PerspectiveCamera::create(75, canvas.getAspect(), 0.1f, 1000);
    camera->position.set(0, 50, 10);

    OrbitControls controls{camera, canvas};

    auto scene = Scene::create();

    auto ballMesh = createBall(4);
    ballMesh->position.set(50,1,0);
    scene->add(ballMesh);

    auto bouncyCylinder = createCylinder(4,6,255,0,0);
    bouncyCylinder->position.set(-10,2,-20);
    scene->add(bouncyCylinder);

    auto flipperMesh = createFlipper(1);
    flipperMesh->position.set(25,2,30);
    scene->add(flipperMesh);

    auto flipper2Mesh = createFlipper(-1);
    flipper2Mesh->position.set(-25,2,30);
    scene->add(flipper2Mesh);

    auto plane = createPlane(500,500);
    plane->position.set(0,-1,0);
    scene->add(plane);

    auto box1 = createBox(10,5,5,255,255,255);
    auto box2 = createBox(10,5,5,255,0,255);
    box1->position.set(50,2,40);
    box2->position.set(50,2,60);
    scene->add(box1);
    scene->add(box2);

    renderer.enableTextRendering();
    auto& textHandle = renderer.textHandle("Test of physics");
    textHandle.setPosition(0, canvas.getSize().height-30);
    textHandle.scale = 2;

    canvas.onWindowResize([&](WindowSize size){
        camera->aspect = size.getAspect();
        camera->updateProjectionMatrix();
        renderer.setSize(size);
        textHandle.setPosition(0, size.height-30);
    });

    Vector3 grav = {0, -9.6892, 1.5346}; //Hehe instead of rotating all objects and the plane, get the components of gravity-acceleration on a 9 degree slope
    BulletPhysics bullet(grav);

    bullet.addMesh(*ballMesh, 10, true);
    auto bouncyBall = bullet.get(*ballMesh);
    bouncyBall->body->setRestitution(0.2);
    bouncyBall->body->setFriction(0.001);
    bouncyBall->body->setRollingFriction(0.001);

    bullet.addMesh(*bouncyCylinder);
    bullet.get(*bouncyCylinder)->body->setRestitution(10);

    bullet.addMesh(*flipperMesh, 10,  true);
    auto flippy = bullet.get(*flipperMesh);
    btHingeConstraint flippyBoi(*flippy->body,btVector3(10,0,0),btVector3(0,1,0));
    flippyBoi.enableAngularMotor(true,0,10000000);
    flippyBoi.setLimit(-0.7,0.4);
    bullet.addConstraint(&flippyBoi, true);

    bullet.addMesh(*flipper2Mesh,10,true);
    auto flippy2 = bullet.get(*flipper2Mesh);
    btHingeConstraint flippyBoi2(*flippy2->body,btVector3(-10,0,0), btVector3(0,1,0));
    flippyBoi2.enableAngularMotor(true,0,10000000);
    flippyBoi2.setLimit(-0.4,0.7);
    bullet.addConstraint(&flippyBoi2, true);

    bullet.addMesh(*box1,1,true);
    bullet.addMesh(*box2,0,true);

    auto topBox = bullet.get(*box1);
    auto bottomBox = bullet.get(*box2);

    btTransform localA;
    btTransform localB;

    localA.setIdentity();
    localB.setIdentity();
    localA.getBasis().setEulerZYX(0,math::PI/2,0);
    localA.setOrigin(btVector3(0.0,0.0,20.0));
    localB.getBasis().setEulerZYX(0,math::PI/2,0);
    localB.setOrigin(btVector3(0.0,0.0,math::TWO_PI));

    btSliderConstraint launchSlider(*topBox->body,*bottomBox->body,localA,localB,true);
    launchSlider.setLowerLinLimit(-0.1);
    launchSlider.setUpperLinLimit(10);
    launchSlider.setLowerAngLimit(0);
    launchSlider.setUpperAngLimit(0);
    bullet.addConstraint(&launchSlider, true);

    bullet.addMesh(*plane);
    bullet.get(*plane)->body->setRestitution(0.6);

    auto keyInput = std::make_shared<KeyInput>();

    canvas.addKeyListener(keyInput.get());

    canvas.animate([&](float dt) {
        bullet.step(dt);

        keyInput->flippers(flippyBoi, flippyBoi2);
        renderer.render(scene, camera);

    });

}
