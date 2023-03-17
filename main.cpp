
#include "threepp/threepp.hpp"
#include "threepp/extras/imgui/imgui_context.hpp"
#include "threepp/extras/physics/BulletPhysics.hpp"
#include "threepp/loaders/AssimpLoader.hpp"

using namespace threepp;

int main() {

    Canvas canvas(Canvas::Parameters().antialiasing(8));
    GLRenderer renderer(canvas);
    renderer.setClearColor(Color::aliceblue);

    auto camera = PerspectiveCamera::create(75, canvas.getAspect(), 0.1f, 1000);
    camera->position.set(-10, 10, 10);

    OrbitControls controls{camera, canvas};

    auto scene = Scene::create();
    scene->add(HemisphereLight::create());

    const auto ballGeometry = SphereGeometry::create(1, 32, 32);
    const auto ballMaterial = MeshBasicMaterial::create();
    ballMaterial->color = Color::blue;
    ballMaterial->wireframe = true;
    auto ballMesh = Mesh::create(ballGeometry, ballMaterial);
    ballMesh->position.setY(10);
    scene->add(ballMesh);

    const auto collisionBoxGeometry= BoxGeometry::create(10,5,10);
    const auto boxMaterial = MeshBasicMaterial::create();
    boxMaterial->color = Color::slategrey;
    auto boxMesh = Mesh::create(collisionBoxGeometry, boxMaterial);
    boxMesh->position.set(20,-1,0);
    scene->add(boxMesh);

    const auto flipperGeometry = BoxGeometry::create(30,5,5);
    flipperGeometry->rotateY(math::DEG2RAD*-90);
    const auto flipperMaterial = MeshBasicMaterial::create();
    flipperMaterial->color = Color::palegreen;
    auto flipperMesh = Mesh::create(flipperGeometry,flipperMaterial);
    flipperMesh->position.set(-20,2,5);
    scene->add(flipperMesh);

    const auto flipperAxisGeometry = CylinderGeometry::create(3,3,6);
    const auto flipperAxisMaterial = MeshBasicMaterial::create();
    flipperAxisMaterial->color = Color::red;
    auto flipperAxisMesh = Mesh::create(flipperAxisGeometry,flipperAxisMaterial);
    flipperAxisMesh->position.set(-20,2,19);
    scene->add(flipperAxisMesh);

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

    BulletPhysics bullet;

    bullet.addMesh(*ballMesh, 10);
    bullet.get(*ballMesh)->body->setRestitution(0.8);
    bullet.get(*ballMesh)->body->setFriction(1.f);
    bullet.get(*ballMesh)->body->setRollingFriction(.1);
    bullet.get(*ballMesh)->body->setSpinningFriction(0.1);

    bullet.addMesh(*boxMesh);
    bullet.get(*boxMesh)->body->setRestitution(5);

    bullet.addMesh(*flipperMesh);
    bullet.get(*flipperMesh)->body->setRestitution(1);
    bullet.addMesh(*flipperAxisMesh);

    bullet.addMesh(*plane);
    bullet.get(*plane)->body->setRestitution(0.6);

    KeyAdapter keyListener(KeyAdapter::Mode::KEY_PRESSED | threepp::KeyAdapter::KEY_REPEAT, [&](KeyEvent evt){
        if (evt.key == 32) { // space
            bullet.get(*ballMesh)->body->applyCentralImpulse({0,20,0});
        }
        if(evt.key == 87){//w
            bullet.get(*ballMesh)->body->applyTorque({-40,0,0});
        }
        if(evt.key == 65){//a
            bullet.get(*ballMesh)->body->applyTorque({0,0,40});
        }
        if(evt.key == 83){//s
            bullet.get(*ballMesh)->body->applyTorque({40,0,0});
        }
        if(evt.key == 68){//d
            bullet.get(*ballMesh)->body->applyTorque({0,0,-40});
        }
        if(evt.key == 82){//r
            bullet.setMeshPosition(*ballMesh,{0,0,0});
        }
    });

    canvas.addKeyListener(&keyListener);

    canvas.animate([&](float dt) {
        bullet.step(dt);

        renderer.render(scene, camera);

    });

}
