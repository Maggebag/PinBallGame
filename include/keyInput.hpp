
#ifndef PINBALLGAME_KEYINPUT_HPP
#define PINBALLGAME_KEYINPUT_HPP

#include <threepp/input/KeyListener.hpp>
#include <threepp/extras/physics/BulletPhysics.hpp>

#include "GameObjects/FlipperObject.hpp"
#include "GameObjects/PlungerObject.hpp"

struct Keys {
    bool w = false;
    bool a = false;
    bool s = false;
    bool d = false;
    bool r = false;
    bool space = false;
};

struct KeyInput : public threepp::KeyListener {
public:
    void onKeyPressed(threepp::KeyEvent evt) override {
        if (evt.key == 87) {
            keys_.w = true;
        } else if (evt.key == 83) {
            keys_.s = true;
        } else if (evt.key == 68) {
            keys_.d = true;
        } else if (evt.key == 65) {
            keys_.a = true;
        } else if (evt.key == 82) {
            keys_.r = true;
        } else if (evt.key == 32) {
            keys_.space = true;
        }
    }

    void onKeyReleased(threepp::KeyEvent evt) override{
        if (evt.key == 87) {
            keys_.w = false;
        } else if (evt.key == 83) {
            keys_.s = false;
        } else if (evt.key == 68) {
            keys_.d = false;
        } else if (evt.key == 65) {
            keys_.a = false;
        } else if (evt.key == 82) {
            keys_.r = false;
        } else if (evt.key == 32) {
            keys_.space = false;
        }
    }

    void flippers(FlipperObject &Right, FlipperObject &Left) const{
        if (keys_.d) {
            Right.activateFlipper();
        } else {
            Right.deactivateFlipper();
        }
        if (keys_.a) {
            Left.activateFlipper();
        } else {
            Left.deactivateFlipper();
        }
    }

    void plunger(PlungerObject &Plunger){
        if (keys_.s && lowLim_ < Plunger.plungerTravelLength) {
            lowLim_ += 0.5;
        }
        if (keys_.w && lowLim_ > 0) {
            lowLim_ -= 0.5;
        }

        Plunger.PlungerSetUpperLim(lowLim_);

        if (keys_.space) {
            Plunger.releasePlunger();
            lowLim_ = 0;
        } else {
            Plunger.resetPlunger();
        }
    }

    void resetBall(const std::shared_ptr<threepp::Mesh>& pinBall, threepp::BulletPhysics &bullet) const{
        if (keys_.r) {
            bullet.setMeshPosition(*pinBall, {40, 13.5, 120});
        }
    }

private:
    Keys keys_;
    float lowLim_;
};

#endif //PINBALLGAME_KEYINPUT_HPP
