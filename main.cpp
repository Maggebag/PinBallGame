
#include "threepp/threepp.hpp"
#include "threepp/extras/imgui/imgui_context.hpp"
#include "threepp/extras/bullet/BulletWrapper.hpp"

using namespace threepp;

int main() {

    Canvas canvas;
    GLRenderer renderer(canvas);

    auto camera = PerspectiveCamera::create(75, canvas.getAspect(),0.1f,100);
    camera->position.z = 20;
    camera->position.y = 10;


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
    planeMaterial->color = Color::gray;
    planeMaterial->side = DoubleSide;
    auto plane = Mesh::create(planeGeometry, planeMaterial);
    plane->position.y =-1;
    scene->add(plane);

    renderer.enableTextRendering();
    auto& textHandle = renderer.textHandle("This is a test");
    textHandle.setPosition(0, canvas.getSize().height-30);
    textHandle.scale = 2;

    auto light = PointLight::create(0xffffff);
    light->distance=10;
    light->position.set(0,1,0);
    scene->add(light);

    auto helper = PointLightHelper::create(light, 0.25f);
    scene->add(helper);

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

        }
        if(evt.key == 87){//w

        }
        if(evt.key == 65){//a

        }
        if(evt.key == 83){//s

        }
        if(evt.key == 68){//d

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