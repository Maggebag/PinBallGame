//This file has been for myself to test new functions to understand them properly before implementing them
//I have tested things such has how to make hingeconstraints and how to properly employ and use the bullet physics-engine

#include "threepp/threepp.hpp"
#include "threepp/extras/physics/BulletPhysics.hpp"
#include "keyInput.hpp"
#include "PlayingField.hpp"
#include "gameLogic.hpp"
#include <sstream>

using namespace threepp;

int main() {

    Canvas canvas(Canvas::Parameters().antialiasing(8));
    GLRenderer renderer(canvas);
    renderer.setClearColor(Color::aliceblue);

    auto camera = PerspectiveCamera::create(75, canvas.getAspect(), 0.1f, 10000);
    camera->position.set(0, 500, 10);

    OrbitControls controls{camera, canvas};

    auto scene = Scene::create();

    canvas.onWindowResize([&](WindowSize size) {
        camera->aspect = size.getAspect();
        camera->updateProjectionMatrix();
        renderer.setSize(size);
    });

    BulletPhysics bullet(getGravFromAngle(6.5));

    PlayingField playingField(*scene, bullet);

    renderer.enableTextRendering();
    auto &handle = renderer.textHandle();

    auto keyInput = std::make_shared<KeyInput>();

    canvas.addKeyListener(keyInput.get());

    canvas.animate([&](float dt) {
        bullet.step(dt);

        ballPosCheck(playingField.PinBall, bullet, playingField.ballResetPos);

        keyInput->flippers(playingField.FlipperRight, playingField.FlipperLeft);
        keyInput->plunger(playingField.Plunger);
        keyInput->reset(playingField.PinBall, bullet);

        renderer.render(scene, camera);

        std::stringstream ss;
        ss << renderer.info();
        handle.setText(ss.str());

    });

}
