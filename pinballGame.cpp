
#include <threepp/extras/physics/BulletPhysics.hpp>
#include <threepp/Canvas.hpp>
#include <threepp/controls/OrbitControls.hpp>
#include <threepp/renderers/GLRenderer.hpp>
#include <threepp/scenes/Scene.hpp>
#include <threepp/cameras/PerspectiveCamera.hpp>
#include <threepp/lights/AmbientLight.hpp>
#include <threepp/core/Clock.hpp>

#include "keyInput.hpp"
#include "PlayingField.hpp"
#include "gameLogic.hpp"
#include "utils.hpp"

int main() {
    threepp::Canvas canvas(threepp::Canvas::Parameters().size(720, 960)
                                            .antialiasing(8)
                                            .vsync(false)
                                            .favicon("bin/doc/logo.png")
                                            .title("PinBallGame"));
    threepp::GLRenderer renderer(canvas);
    renderer.setClearColor(threepp::Color::blanchedalmond);
    renderer.shadowMap().type = threepp::PCFSoftShadowMap;
    renderer.shadowMap().enabled = true;

    auto camera = threepp::PerspectiveCamera::create(75, canvas.getAspect(), 0.1f, 10000);
    camera->position.set(0, 850, 10);

    threepp::OrbitControls controls{camera, canvas};

    auto scene = threepp::Scene::create();

    scene->add(threepp::AmbientLight::create(0xffffff, 0.1f));
    scene->add(utils::createLight(threepp::Vector3(0, 700, -400)));

    canvas.onWindowResize([&](threepp::WindowSize size) {
        camera->aspect = size.getAspect();
        camera->updateProjectionMatrix();
        renderer.setSize(size);
    });

    threepp::BulletPhysics bullet(getGravFromAngle(6.5));

    PlayingField playingField(*scene, bullet);

    auto keyInput = std::make_shared<KeyInput>();

    canvas.addKeyListener(keyInput.get());

    threepp::Clock clock;
    canvas.animate([&]() {
        float dt = clock.getDelta();
        bullet.step(dt);

        checkIfBallOut(playingField.PinBall, ballPosGet(playingField.PinBall, bullet), playingField.ballResetPos, 470,
                       bullet);

        keyInput->flippers(playingField.FlipperRight, playingField.FlipperLeft);
        keyInput->plunger(playingField.Plunger);
        keyInput->resetBall(playingField.PinBall, bullet);

        renderer.render(scene, camera);
    });
}
