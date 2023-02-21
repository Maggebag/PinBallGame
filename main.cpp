
#include "threepp/threepp.hpp"
#include "threepp/extras/imgui/imgui_context.hpp"
#include "threepp/extras/bullet/BulletWrapper.hpp"

using namespace threepp;

int main() {

    Canvas canvas;
    GLRenderer renderer(canvas);
    renderer.setClearColor(Color::aliceblue);

    auto camera = PerspectiveCamera::create();
    camera->position.z = 5;

    OrbitControls controls{camera, canvas};

    auto scene = Scene::create();

    const auto boxGeometry = BoxGeometry::create();
    const auto boxMaterial = MeshBasicMaterial::create();
    boxMaterial->color = Color::blue;
    auto boxMesh = Mesh::create(boxGeometry, boxMaterial);
    boxMesh->position.setY(10);
    scene->add(boxMesh);

    const auto planeGeometry = PlaneGeometry::create(50, 50);
    planeGeometry->rotateX(math::DEG2RAD*-90);
    const auto planeMaterial = MeshBasicMaterial::create();
    planeMaterial->color = Color::green;
    auto plane = Mesh::create(planeGeometry, planeMaterial);
    plane->position.y =-1;
    scene->add(plane);

    renderer.enableTextRendering();
    auto& textHandle = renderer.textHandle("This is a test");
    textHandle.setPosition(0, canvas.getSize().height-30);
    textHandle.scale = 2;

    canvas.onWindowResize([&](WindowSize size){
        camera->aspect = size.getAspect();
        camera->updateProjectionMatrix();
        renderer.setSize(size);
        textHandle.setPosition(0, size.height-30);
    });

    BulletWrapper bullet(Vector3(0,-9.81,0));

    auto box = RbWrapper::create(boxGeometry, 1);
    bullet.addRigidbody(box,boxMesh);

    KeyAdapter keyListener(KeyAdapter::Mode::KEY_PRESSED | threepp::KeyAdapter::KEY_REPEAT, [&](KeyEvent evt){
        if (evt.key == 32) { // space
            box->body->applyCentralImpulse({0,10,0});
        }
        if(evt.key == 87){//w
            box->body->applyCentralImpulse({0,0,-10});
        }
        if(evt.key == 65){//a
            box->body->applyCentralImpulse({-10,0,0});
        }
        if(evt.key == 83){//s
            box->body->applyCentralImpulse({0,0,10});
        }
        if(evt.key == 68){//d
            box->body->applyCentralImpulse({10,0,0});
        }
    });

    canvas.addKeyListener(&keyListener);

    // bullet.addRigidbody(RbWrapper::create(boxGeometry, 0.01), box);
    bullet.addRigidbody(RbWrapper::create(planeGeometry), plane);

    canvas.animate([&](float dt) {
        bullet.step(dt);

        renderer.render(scene, camera);

    });

}