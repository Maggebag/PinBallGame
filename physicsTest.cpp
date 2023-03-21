
#include "threepp/threepp.hpp"
#include "threepp/extras/physics/BulletPhysics.hpp"

using namespace threepp;

auto createFlipper(float direction){
    const auto flipperGeometry = BoxGeometry::create(30,5,5);
    const auto flipperMaterial = MeshBasicMaterial::create();
    flipperMaterial->color = Color::palegreen;
    auto flipperMesh = Mesh::create(flipperGeometry,flipperMaterial);

    const auto flipperAxisGeometry = CylinderGeometry::create(2,2,6);
    const auto flipperAxisMaterial = MeshBasicMaterial::create();
    flipperAxisMaterial->color = Color::red;
    flipperAxisGeometry->translate(direction*flipperGeometry->width/3,0,0);
    auto flipperAxisMesh = Mesh::create(flipperAxisGeometry,flipperAxisMaterial);
    flipperMesh->add(flipperAxisMesh);

    return flipperMesh;
}

auto createCylinder(float size, float height){
    const auto cylinderGeometry = CylinderGeometry::create(size,size,height);
    const auto cylinderMaterial = MeshBasicMaterial::create();
    cylinderMaterial->color = Color::red;
    auto cylinderMesh = Mesh::create(cylinderGeometry,cylinderMaterial);

    return cylinderMesh;
}
int main() {

    Canvas canvas(Canvas::Parameters().antialiasing(8));
    GLRenderer renderer(canvas);
    renderer.setClearColor(Color::aliceblue);

    auto camera = PerspectiveCamera::create(75, canvas.getAspect(), 0.1f, 1000);
    camera->position.set(0, 50, 10);

    OrbitControls controls{camera, canvas};

    auto scene = Scene::create();
    scene->add(HemisphereLight::create());

    const auto ballGeometry = SphereGeometry::create(3, 32, 32);
    const auto ballMaterial = MeshBasicMaterial::create();
    ballMaterial->color = Color::blue;
    ballMaterial->wireframe = true;
    auto ballMesh = Mesh::create(ballGeometry, ballMaterial);
    ballMesh->position.setY(5);
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

    const auto planeGeometry = PlaneGeometry::create(500, 500);
    planeGeometry->rotateX(math::DEG2RAD*-90);
    const auto planeMaterial = MeshBasicMaterial::create();
    planeMaterial->color = Color::green;
    auto plane = Mesh::create(planeGeometry, planeMaterial);
    plane->position.y =-1;
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

    bullet.addMesh(*ballMesh, 1.f, true);
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
