//This file has been for myself to test new functions to understand them properly before implementing them
//I have tested things such has how to make hingeconstraints and how to properly employ and use the bullet physics-engine

#include "threepp/threepp.hpp"
#include "threepp/extras/physics/BulletPhysics.hpp"
#include "gameObjects.hpp"

using namespace threepp;

int main() {

    Canvas canvas(Canvas::Parameters().antialiasing(8));
    GLRenderer renderer(canvas);
    renderer.setClearColor(Color::aliceblue);

    auto camera = PerspectiveCamera::create(75, canvas.getAspect(), 0.1f, 1000);
    camera->position.set(0, 50, 10);

    OrbitControls controls{camera, canvas};

    auto scene = Scene::create();
    scene->add(HemisphereLight::create());

    auto ballMesh = createBall(3);
    scene->add(ballMesh);

    auto bouncyCylinder = createCylinder(4,6);
    bouncyCylinder->position.set(-10,2,-20);
    scene->add(bouncyCylinder);

    auto flipperMesh = createFlipper(1);
    flipperMesh->position.set(10,2,30);
    scene->add(flipperMesh);

    auto flipper2Mesh = createFlipper(-1);
    flipper2Mesh->position.set(-30,2,30);
    scene->add(flipper2Mesh);

    auto plane = createPlane(500,500);
    plane->position.set(0,-1,0);
    scene->add(plane);

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

    bullet.addMesh(*plane);
    bullet.get(*plane)->body->setRestitution(0.6);

    KeyAdapter keyListener( KeyAdapter::Mode::KEY_PRESSED | KeyAdapter::Mode::KEY_REPEAT, [&](KeyEvent evt){
        if(evt.key == 32){//space
            flippyBoi.setMotorTargetVelocity(-1000000);
            flippyBoi2.setMotorTargetVelocity(1000000);
        }
        if(evt.key == 82){//r
            bullet.setMeshPosition(*ballMesh,{0,0,0});
            flippyBoi.setMotorTargetVelocity(1000000);
            flippyBoi2.setMotorTargetVelocity(-1000000);
        }
    });

    canvas.addKeyListener(&keyListener);

    canvas.animate([&](float dt) {
        bullet.step(dt);

        renderer.render(scene, camera);

    });

}
