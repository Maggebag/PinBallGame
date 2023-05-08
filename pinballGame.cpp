
#include <threepp/threepp.hpp>
#include <threepp/extras/physics/BulletPhysics.hpp>
#include "keyInput.hpp"
#include "PlayingField.hpp"
#include "gameLogic.hpp"
#include "utils.hpp"

using namespace threepp;

int main()
{

    Canvas canvas(Canvas::Parameters().antialiasing(8));
    GLRenderer renderer(canvas);
    renderer.setClearColor(Color::aliceblue);
    renderer.shadowMap().type = PCFSoftShadowMap;
    renderer.shadowMap().enabled = true;

    auto camera = PerspectiveCamera::create(75, canvas.getAspect(), 0.1f, 10000);
    camera->position.set(0, 500, 10);

    OrbitControls controls{camera, canvas};

    auto scene = Scene::create();

    scene->add(AmbientLight::create(0xffffff, 0.1f));
    auto light = utils::createLight(Vector3(0,700,-400));
    scene->add(light);


    canvas.onWindowResize([&](WindowSize size) {
        camera->aspect = size.getAspect();
        camera->updateProjectionMatrix();
        renderer.setSize(size);
    });

    BulletPhysics bullet(getGravFromAngle(6.5));

    PlayingField playingField(*scene, bullet);

    auto keyInput = std::make_shared<KeyInput>();

    canvas.addKeyListener(keyInput.get());

    canvas.animate([&](float dt) {
        bullet.step(dt);

        ballPosCheck(playingField.PinBall, bullet, playingField.ballResetPos);

        keyInput->flippers(playingField.FlipperRight, playingField.FlipperLeft);
        keyInput->plunger(playingField.Plunger);

        renderer.render(scene, camera);
    });

}