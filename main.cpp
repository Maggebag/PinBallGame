
#include "threepp/threepp.hpp"
#include "threepp/extras/imgui/imgui_context.hpp"
#include "threepp/extras/bullet/BulletWrapper.hpp"
#include <threepp/loaders/AssimpLoader.hpp>

using namespace threepp;

int main() {

    Canvas canvas;
    GLRenderer renderer(canvas);
    renderer.setClearColor(Color::aliceblue);

    auto camera = PerspectiveCamera::create();
    camera->position.set(0,50,50);

    OrbitControls controls{camera, canvas};

    auto scene = Scene::create();

    const auto ballGeometry = SphereGeometry::create(5);
    const auto ballMaterial = MeshBasicMaterial::create();
    ballMaterial->color = Color::blue;
    ballMaterial->wireframe = true;
    auto ballMesh = Mesh::create(ballGeometry, ballMaterial);
    ballMesh->position.setY(10);
    scene->add(ballMesh);

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

    BulletWrapper bullet(Vector3(0,-9.81,0));

    auto ball = RbWrapper::create(ballGeometry, 1);
    bullet.addRigidbody(ball,*ballMesh);

    KeyAdapter keyListener(KeyAdapter::Mode::KEY_PRESSED | threepp::KeyAdapter::KEY_REPEAT, [&](KeyEvent evt){
        if (evt.key == 32) { // space
            ball->body->applyCentralImpulse({0,5,0});
        }
        if(evt.key == 87){//w
            ball->body->applyImpulse({0,0,-2},{0,2,0});
        }
        if(evt.key == 65){//a
            ball->body->applyCentralImpulse({-2,0,0});
        }
        if(evt.key == 83){//s
            ball->body->applyCentralImpulse({0,0,2});
        }
        if(evt.key == 68){//d
            ball->body->applyCentralImpulse({2,0,0});
        }
    });

    canvas.addKeyListener(&keyListener);

    bullet.addRigidbody(RbWrapper::create(planeGeometry), *plane);



    canvas.animate([&](float dt) {
        bullet.step(dt);

        renderer.render(scene, camera);

    });

}
