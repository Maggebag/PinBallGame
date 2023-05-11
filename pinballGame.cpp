
#include <threepp/extras/physics/BulletPhysics.hpp>
#include <threepp/Canvas.hpp>
#include <threepp/controls/OrbitControls.hpp>
#include <threepp/renderers/GLRenderer.hpp>
#include <threepp/scenes/Scene.hpp>
#include <threepp/cameras/PerspectiveCamera.hpp>
#include <threepp/lights/AmbientLight.hpp>

#include "keyInput.hpp"
#include "PlayingField.hpp"
#include "gameLogic.hpp"
#include "utils.hpp"

using namespace threepp;

int main() {
    Canvas canvas(Canvas::Parameters().antialiasing(8));
    GLRenderer renderer(canvas);
    renderer.setClearColor(Color::blanchedalmond);
    renderer.shadowMap().type = PCFSoftShadowMap;
    renderer.shadowMap().enabled = true;

    auto camera = PerspectiveCamera::create(75, canvas.getAspect(), 0.1f, 10000);
    camera->position.set(0, 500, 10);

    OrbitControls controls{camera, canvas};

    auto scene = Scene::create();

    scene->add(AmbientLight::create(0xffffff, 0.1f));
    scene->add(utils::createLight(Vector3(0, 700, -400)));

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

        checkIfBallOut(playingField.PinBall, ballPosGet(playingField.PinBall, bullet), playingField.ballResetPos, 470,
                       bullet);

        keyInput->flippers(playingField.FlipperRight, playingField.FlipperLeft);
        keyInput->plunger(playingField.Plunger);
        keyInput->resetBall(playingField.PinBall, bullet);

        renderer.render(scene, camera);
    });
}
